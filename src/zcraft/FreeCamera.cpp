/*
FreeCamera.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include "zcraft/FreeCamera.hpp"
#include "engine/opengl/glutils.hpp"

using namespace engine;

namespace zcraft
{
	FreeCamera::FreeCamera()
	{
		m_pitch = 0;
		m_yaw = 0;
		m_camera.setVertical(Vector3f(0, 0, 1));
		m_camera.setForward(Vector3f(0, 1, 0));
		m_camera.setNearAndFar(0.1f, 512);
		m_lastMouseX = -1;
		m_lastMouseY = -1;
		m_sensitivity = 0.25f;
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
		Vector3f camLeft = Vector3f(camFw.x, camFw.y, 0);
		camLeft.normalize();
		camLeft.rotateXYBy(-90);

		f32 yaw = m_yaw;
		f32 pitch = m_pitch;

		f32 a = 8.f * delta.s(); // Linear speed
		f32 aa = 90.f * delta.s(); // Angular speed

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			camPos -= camLeft * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			camPos += camLeft * a;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
			yaw += aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			yaw -= aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			pitch -= aa;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pitch += aa;
		}

		if(m_yaw != yaw || m_pitch != pitch)
		{
			setAngles(yaw, pitch);
		}

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

		// Yaw normalization
		if(m_yaw > 180)
			m_yaw -= 360;
		else if(m_yaw < -180)
			m_yaw += 360;

		// Pitch clamping
		m_pitch = math::clamp(m_pitch, -89.f, 89.f);
	}

	void FreeCamera::setSensitivity(f32 degreesPerPixel)
	{
		m_sensitivity = degreesPerPixel;
	}

	inline float f(const float x)
	{
		if(x > 0)
			return x + 0.025f * x*x;
		else if(x < 0)
			return x - 0.025f * x*x;
		else
			return 0;
	}

	void FreeCamera::mouseMoved(s32 newX, s32 newY)
	{
		if(m_lastMouseX >= 0 || m_lastMouseY >= 0)
		{
			s32 deltaX = newX - m_lastMouseX;
			s32 deltaY = newY - m_lastMouseY;

			f32 dtx = -f(deltaX * m_sensitivity);
			f32 dty = -f(deltaY * m_sensitivity);

			setAngles(m_yaw + dtx, m_pitch + dty);
		}

		m_lastMouseX = newX;
		m_lastMouseY = newY;
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


