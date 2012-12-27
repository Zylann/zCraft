/*
FreeCamera.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "zcraft/FreeCamera.hpp"
#include "engine/opengl/glutils.hpp"

namespace zcraft
{
	FreeCamera::FreeCamera()
	{
		m_pitch = 0;
		m_yaw = 0;
		m_camera.setVertical(Vector3f(0, 0, 1));
		m_camera.setForward(Vector3f(0, 1, 0));
	}

	void FreeCamera::look()
	{
		m_camera.look();
	}

	void FreeCamera::update(const engine::Time & delta)
	{
		Vector3f camPos = m_camera.getPosition();
		Vector3f camFw = m_camera.getForward();
		Vector3f camVert = m_camera.getVertical();
		Vector3f camLeft = camFw;
		camLeft.rotateXYBy(-90);

		f32 a = 8.f * delta.s(); // Linear speed
		f32 aa = 90.f * delta.s(); // Angular speed

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			camPos -= camLeft * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			camPos += camLeft * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			camPos += camFw * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			camPos -= camFw * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			camPos += camVert * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			camPos -= camVert * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_yaw += aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_yaw -= aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_pitch -= aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_pitch += aa;
		}

		// Yaw normalization
		if(m_yaw > 180)
			m_yaw -= 360;
		else if(m_yaw < -180)
			m_yaw += 360;

		// Pitch clamping
		if(m_pitch > 90)
			m_pitch = 89;
		else if(m_pitch < -90)
			m_pitch = -89;

		// Update position
		m_camera.setPosition(camPos);

		// Update forward vector
		camFw = Vector3f(0, 1, 0);
		camFw.rotateYZBy(m_pitch);
		camFw.rotateXYBy(m_yaw);
		m_camera.setForward(camFw);
	}

	void FreeCamera::setAngles(f32 yawDegrees, f32 pitchDegrees)
	{
		m_yaw = yawDegrees;
		m_pitch = pitchDegrees;
	}

	void FreeCamera::mouseMoved(s32 oldX, s32 oldY, s32 newX, s32 newY)
	{
		s32 deltaX = newX - oldX;
		s32 deltaY = newY - oldY;

		m_pitch += deltaX;
		m_yaw += deltaY;
	}

	void FreeCamera::mouseWheelMoved(s32 delta)
	{
		float fov = m_camera.getFov();
		fov += 2 * delta;
		if(fov < 50)
			fov = 50;
		else if(fov > 140)
			fov = 140;
		m_camera.setFov(fov);
	}

} // namespace zcraft


