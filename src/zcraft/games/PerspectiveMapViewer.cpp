/*
PerspectiveMapViewer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/opengl/glutils.hpp"
#include "zcraft/games/PerspectiveMapViewer.hpp"
#include "zcraft/face.hpp"

using namespace engine;

namespace zcraft
{
	PerspectiveMapViewer::PerspectiveMapViewer(u32 width, u32 height)
	: 	ABasicGame(width, height, "zCraft :: 3D map viewer - indev")
	{}

	PerspectiveMapViewer::~PerspectiveMapViewer()
	{}

	bool PerspectiveMapViewer::init()
	{
		if(!gl::initOpenglExtensions(true, true))
			return false;

		//zcraft::init();

		// Load a font
		if(!m_font.loadFromFile("assets/fonts/arial32.fnt"))
			return false;

		// Init camera
		m_camera.setPosition(Vector3f(0, -5, 160));
		m_camera.updateViewport(Vector2f(
			m_window.getSize().x, m_window.getSize().y));

		// Init map stream
		m_map.addListener(&m_meshMap);
		m_mapStreamer = new MapStreamer(m_map, 8);
		m_mapStreamer->update(Vector3i(0, 0, 0), true); // first update
		m_mapStreamer->setSave(false); // Save turned off atm.

		return true;
	}

	void PerspectiveMapViewer::update(const engine::Time & delta)
	{
		// Update camera
		m_camera.update(delta, m_window);

		updatePointedVoxel();

		// Update map stream
		Vector3f camPos = m_camera.getPosition();
		Vector3i pos(camPos.x, camPos.y, camPos.z);
		Vector3i bpos(pos.x >> 4, pos.y >> 4, pos.z >> 4);
		m_mapStreamer->update(bpos);
	}

	void PerspectiveMapViewer::renderScene(const engine::Time & delta)
	{
		//glClearColor(0.1f, 0.5f, 0.9f, 1);
		glClearColor(0.0f, 0.0f, 0.0f, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_CULL_FACE);
		glHint(GL_LINE_SMOOTH, GL_FASTEST);

		//f32 fogColor[4] = {0.4f, 0.7f, 1.0f, 1.f};
		f32 fogColor[4] = {0, 0, 0, 1};
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.019f);
		glHint(GL_FOG_HINT, GL_NICEST);

		/* Scene */

		glPushMatrix();

		m_camera.look();

		glDisable(GL_BLEND);

		// Draw the map
		m_meshMap.drawAll();

		// Pointed voxel
		if(m_raycast.collision)
		{
			glPushMatrix();
			glTranslatef(
				0.5f + m_raycast.hit.pos.x,
				0.5f + m_raycast.hit.pos.y,
				0.5f + m_raycast.hit.pos.z);
			glColor3ub(255,255,255);
			glLineWidth(2.f);
			gl::drawCubeLines(0.501f);
			glPopMatrix();
		}

		// Axes
		glDisable(GL_TEXTURE_2D);
		glLineWidth(4);
		gl::drawAxes(1);
		glLineWidth(1);

		// Transparent objects
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Grid
		glColor3f(0.f,0.f,0.f);
		glPushMatrix();
		glScalef(16, 16, 16);
		gl::drawGrid(0, 0, 16);
		glPopMatrix();

		glPopMatrix();

		glDisable(GL_FOG);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	void PerspectiveMapViewer::renderGUI(const Time & delta)
	{
		/* HUD */

		glColor4ub(255,255,255,255);

		// Target
		glLineWidth(2);
		gl::drawCross(m_window.getSize().x / 2, m_window.getSize().y / 2, 16);

		std::stringstream ss;

		// Tips
		ss << "WASD/ZQSD to move, arrows to rotate, +/- to go up and down, "
			<< "ESC to disable camera\n";

		// FPS
		ss << "FPS=" << (int)delta.hz();

		// MapStreamThread
		MapStreamThread::RunningInfo threadInfo = m_mapStreamer->getThreadInfo();
		ss << "\nRem:" << threadInfo.remainingRequests
			<< ", L:" << threadInfo.loadedCount
			<< ", G:" << threadInfo.generatedCount
			<< ", S:" << threadInfo.savedCount
			<< ", D:" << threadInfo.droppedCount;

		// MeshMap
		ss << "\nBlocks: " << m_map.getBlockCount()
			<< " Meshs: " << m_meshMap.getCount();

		// Position
		Vector3f fpos = m_camera.getPosition();
		ss << "\nPos: " << Vector3i(floor(fpos.x), floor(fpos.y), floor(fpos.y));

		m_font.draw(ss.str(), 0, 0);
	}

	void PerspectiveMapViewer::dispose()
	{
		m_meshMap.clear();
	}

	void PerspectiveMapViewer::resized(const Vector2i & newSize)
	{
		m_camera.updateViewport(Vector2f(newSize.x, newSize.y));
	}

	void PerspectiveMapViewer::processEvent(const sf::Event & event)
	{
		if(event.type == sf::Event::MouseWheelMoved)
		{
			m_camera.mouseWheelMoved(event.mouseWheel.delta);
		}
		else if(event.type == sf::Event::MouseButtonPressed)
		{
			if(m_raycast.collision)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					m_map.setNode(m_raycast.hit.pos, Node(node::AIR));
				}
				else if(event.mouseButton.button == sf::Mouse::Right)
				{
					m_map.setNode(m_raycast.hitPrevious.pos, Node(node::STONE));
				}
			}
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Key::Escape)
				m_camera.setEnabled(!m_camera.isEnabled());
		}
	}

	void PerspectiveMapViewer::updatePointedVoxel()
	{
		m_raycast =
			m_map.raycastToSolidNode(
				m_camera.getPosition(),
				m_camera.getForward(), 16);
	}

} // namespace zcraft




