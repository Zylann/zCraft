#include <iostream>
#include <fstream>
#include "zcraft/games/FlatMapViewer.hpp"
#include "zcraft/cartographer/Cartographer.hpp"
#include "zcraft/NodeProperties.hpp"

using namespace engine;
using namespace bmfont;

namespace zcraft
{
	FlatMapViewer::FlatMapViewer(u32 width, u32 height)
	: 	ABasicGame(width, height, "zCraft :: flat map viewer - indev")
	{
	}

	FlatMapViewer::~FlatMapViewer()
	{
	}

	bool FlatMapViewer::init()
	{
		if(!gl::initOpenglExtensions(true, true))
			return false;

		//zcraft::init();

		if(!m_font.loadFromFile("assets/fonts/arial32.fnt"))
			return false;

		m_map.addListener(this);
		m_mapStreamer = new MapStreamer(m_map, 5);
		m_mapStreamer->update(Vector3i(0, 0, 0), true); // first update

		return true;
	}

	void FlatMapViewer::update(const Time & delta)
	{
		f32 a = 32.f * delta.s();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			m_camera.move(-a, 0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_camera.move(a, 0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			m_camera.move(0, a);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_camera.move(0, -a);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			m_camera.zoom(1.02f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			m_camera.zoom(0.98f);

		const Vector2f camPos = m_camera.getCenter();
		Vector3i pos(camPos.x, camPos.y, 0);
		Vector3i bpos(pos.x >> 4, pos.y >> 4, pos.z >> 4);
		m_mapStreamer->update(bpos);
	}

	void FlatMapViewer::renderScene(const Time & delta)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);

		/* Scene */

		glPushMatrix();
		m_camera.look();

		// Render cartography
		m_cartography.render(16, sf::Keyboard::isKeyPressed(sf::Keyboard::G));

		// Axes
		glDisable(GL_TEXTURE_2D);
		glLineWidth(2);
		gl::drawAxes(16);
		glLineWidth(1);

		glColor3ub(255, 255, 0);
		gl::drawCross(m_camera.getCenter().x, m_camera.getCenter().y, 16);

		glPopMatrix();

	}

	void FlatMapViewer::renderGUI(const Time & delta)
	{
		MapStreamThread::RunningInfo threadInfo = m_mapStreamer->getThreadInfo();
		std::stringstream ss;
		ss << "Rem:" << threadInfo.remainingRequests
			<< ", L:" << threadInfo.loadedCount
			<< ", G:" << threadInfo.generatedCount
			<< ", S:" << threadInfo.savedCount
			<< ", D:" << threadInfo.droppedCount;
		glColor3ub(255,255,255);
		m_font.draw(ss.str(), 0, 0);
	}

	void FlatMapViewer::dispose()
	{
		delete m_mapStreamer;

		//zcraft::free();
	}

	void FlatMapViewer::resized(const Vector2i & newSize)
	{
		m_camera.updateViewport(Vector2f(newSize.x, newSize.y));
	}

	void FlatMapViewer::processEvent(const sf::Event & event)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::C)
				std::cout << m_camera << std::endl;
		}
	}

	void FlatMapViewer::blockAdded(const Vector3i pos, BlockMap & map)
	{
		sf::Image img = Cartographer::renderChunkTopDown(m_map, pos.x, pos.y, -64, 64);
		m_cartography.setPictureFromImage(Vector2i(pos.x, pos.y), img);
	}

	void FlatMapViewer::blockChanged(const Vector3i pos, BlockMap & map)
	{
		sf::Image img = Cartographer::renderChunkTopDown(m_map, pos.x, pos.y, -64, 64);
		m_cartography.setPictureFromImage(Vector2i(pos.x, pos.y), img);
	}

	void FlatMapViewer::blockRemoved(const Vector3i pos, BlockMap & map)
	{
		m_cartography.erasePicture(Vector2i(pos.x, pos.y));
	}


} // namespace zcraft



