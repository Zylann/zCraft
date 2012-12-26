/*
PerspectiveMapViewer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/opengl/glutils.hpp"
#include "zcraft/games/PerspectiveMapViewer.hpp"

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

		if(!m_font.loadFromFile("assets/fonts/arial32.fnt"))
			return false;

		m_camera.setPosition(Vector3f(0, -5, 64));

		m_map.addListener(this);
		m_mapStreamer = new MapStreamer(m_map, 3);
		m_mapStreamer->update(Vector3i(0, 0, 0), true); // first update

		return true;
	}

	void PerspectiveMapViewer::update(const engine::Time & delta)
	{
		Vector3f camPos = m_camera.getPosition();
		Vector3f camFw = m_camera.getForward();
		f32 a = 8.f * delta.s();
		f32 aa = 90.f * delta.s();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			camPos.x -= a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			camPos.x += a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			camPos.y += a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			camPos.y -= a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			camPos.z += a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			camPos.z -= a;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			camFw.rotateXYBy(aa);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			camFw.rotateXYBy(-aa);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			camFw.rotateYZBy(aa);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			camFw.rotateYZBy(-aa);

		m_camera.setPosition(camPos);
		m_camera.setForward(camFw);
		m_camera.updateViewport(Vector2f(
			m_window.getSize().x, m_window.getSize().y));

		Vector3i pos(camPos.x, camPos.y, camPos.z);
		Vector3i bpos(pos.x >> 4, pos.y >> 4, pos.z >> 4);
		m_mapStreamer->update(bpos);
	}

	void PerspectiveMapViewer::render(const engine::Time & delta)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_CULL_FACE);
		glHint(GL_LINE_SMOOTH, GL_FASTEST);

		/* Scene */

		glPushMatrix();

		m_camera.look();
		glDisable(GL_BLEND);

		//gl::drawCube(0.5f);

		// Test VBO
		m_meshMap.drawAll();

		// Axes
		glDisable(GL_TEXTURE_2D);
		glLineWidth(4);
		gl::drawAxes(1);
		glLineWidth(1);

		// Transparent objects
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Grid
		glColor3f(0.5f,0.5f,0.5f);
		gl::drawGrid(0,0,8);

		glPopMatrix();

		/* HUD */

		// Pixel-match view

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, m_window.getSize().x, m_window.getSize().y, 0);

		glColor4ub(255,255,255,255);

		// FPS
		std::stringstream ss;
		ss << "FPS=" << (int)delta.hz();

		// MapStreamThread
		MapStreamThread::RunningInfo threadInfo = m_mapStreamer->getThreadInfo();
		ss << "\nRem:" << threadInfo.remainingRequests
			<< ", L:" << threadInfo.loadedCount
			<< ", G:" << threadInfo.generatedCount
			<< ", S:" << threadInfo.savedCount
			<< ", D:" << threadInfo.droppedCount;

		ss << "\nBlocks: " << m_map.getBlockCount()
			<< " Meshs: " << m_meshMap.getCount();

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
			//std::cout << event.mouseWheel.delta << std::endl;
			float fov = m_camera.getFov();
			fov += 2 * event.mouseWheel.delta;
			if(fov < 50)
				fov = 50;
			else if(fov > 140)
				fov = 140;
			m_camera.setFov(fov);
		}
	}

	void PerspectiveMapViewer::blockAdded(const Vector3i pos)
	{
		// start block position
		Vector3i startPos = pos * Block::SIZE;

		// voxels area including neighbors
		Vector3i minEdge = startPos - Vector3i(1,1,1);
		Vector3i maxEdge = startPos + Vector3i(1,1,1) * Block::SIZE;
		Area3D area;
		area.setBounds(minEdge, maxEdge);

		VoxelBuffer voxels;
		voxels.create(area);

		// copy voxels

		Block * block = m_map.getBlock(pos);
		if(block != nullptr)
		{
			block->copyTo(voxels);
		}

		// copy first neighbors voxels
		/*
		for(u8 dir = 0; dir < 6; dir++)
		{
			const Vector3i& dirVect = directionToVector3(dir);
			Vector3i dirVect16(dirVect.x, dirVect.y, dirVect.z);

			cdiv = map.getChunkDivision_const(pos + dirVect16);
			if(cdiv != NULL)
			{
				cdiv->copyBorderTo(voxels, util::directionOpposite6(dir));
			}
		}
		*/

		gl::VertexColorArray * vbo = m_meshMaker.makeMesh(pos, voxels);
		m_meshMap.setMesh(pos, vbo);
	}

	void PerspectiveMapViewer::blockChanged(const Vector3i pos)
	{
	}

	void PerspectiveMapViewer::blockRemoved(const Vector3i pos)
	{
		m_meshMap.eraseMesh(pos);
	}

} // namespace zcraft

