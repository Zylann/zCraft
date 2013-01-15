/*
FreeCamera.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef FREECAMERA_HPP_INCLUDED
#define FREECAMERA_HPP_INCLUDED

#include "zcraft/common.hpp"
#include "engine/system/Time.hpp"
#include "engine/opengl/Camera3D.hpp"

namespace zcraft
{
	/*
		High-level free flight camera wrapped around a basic 3D camera.
		The vertical axis is Z+.
	*/

	class FreeCamera
	{
	private :

		engine::Camera3D m_camera;
		f32 m_yaw;
		f32 m_pitch;
		s32 m_lastMouseX;
		s32 m_lastMouseY;
		f32 m_sensitivity;

	public :

		FreeCamera();

		void look();

		inline void updateViewport(const Vector2f s) { m_camera.updateViewport(s); }

		inline void setPosition(const Vector3f pos) { m_camera.setPosition(pos); }

		inline Vector3f getPosition() const { return m_camera.getPosition(); }

		// Set both spherical look angles of the camera.
		// The vertical axis is Z+.
		void setAngles(f32 yawDegrees, f32 pitchDegrees);

		void setSensitivity(f32 degreesPerPixel);

		// Real-time update
		void update(const engine::Time & delta);

		// Must be called on mouse move events
		void mouseMoved(s32 newX, s32 newY);

		// Must be called on mouse wheel events
		void mouseWheelMoved(s32 delta);

	};

} // namespace zcraft

#endif // FREECAMERA_HPP_INCLUDED
