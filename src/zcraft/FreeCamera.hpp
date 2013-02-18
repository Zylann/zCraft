/*
FreeCamera.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef FREECAMERA_HPP_INCLUDED
#define FREECAMERA_HPP_INCLUDED

#include <SFML/Window.hpp>
#include "engine/system/Time.hpp"
#include "engine/opengl/Camera3D.hpp"
#include "zcraft/common.hpp"

namespace zcraft
{
	/*
		High-level free flight camera wrapped around a basic 3D camera.
		The vertical axis is Z+.
	*/

	class FreeCamera
	{
	private :

		zn::Camera3D m_camera;
		f32 m_yaw;
		f32 m_pitch;
		s32 m_lastMouseX;
		s32 m_lastMouseY;
		f32 m_sensitivity;
		bool m_enabled;

	public :

		FreeCamera();

		void look();

		inline void updateViewport(const Vector2f s) { m_camera.updateViewport(s); }

		inline void setPosition(const Vector3f pos) { m_camera.setPosition(pos); }

		inline Vector3f getForward() const { return m_camera.getForward(); }

		inline Vector3f getPosition() const { return m_camera.getPosition(); }

		inline void setEnabled(bool e) { m_enabled = e; }

		inline bool isEnabled() const { return m_enabled; }

		// Set both spherical look angles of the camera.
		// The vertical axis is Z+.
		void setAngles(f32 yawDegrees, f32 pitchDegrees);

		void setSensitivity(f32 degreesPerPixel);

		// Real-time update.
		// The window reference is needed because it involves mouse grabbing.
		void update(const zn::Time & delta, const sf::Window & window);

		// Must be called on mouse wheel events
		void mouseWheelMoved(s32 delta);

	};

} // namespace zcraft

#endif // FREECAMERA_HPP_INCLUDED
