/*
Camera3D.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/core/Vector2.hpp"
#include "engine/core/Vector3.hpp"
#include "engine/opengl/opengl.hpp"
#include "engine/opengl/Camera3D.hpp"

namespace zn
{
	Camera3D::Camera3D(const Vector2f viewportSize)
	{
		m_viewportSize = viewportSize;
		m_near = 1;
		m_far = 1000;
		m_fov = 70;
		m_vertical.set(0,0,1);
		m_forward.set(0,1,0);
		m_projectionChanged = true;
		m_positionChanged = true;
	}

	void Camera3D::updateViewport(const Vector2f vps)
	{
		m_viewportSize = vps;
		m_projectionChanged = true;
	}

	void Camera3D::setNearAndFar(f32 near, f32 far)
	{
		m_near = near;
		m_far = far;
		m_projectionChanged = true;
	}

	void Camera3D::setFov(f32 fovDegrees)
	{
		m_fov = fovDegrees;
		m_projectionChanged = true;
	}

	void Camera3D::setPosition(const Vector3f pos)
	{
		m_pos = pos;
		m_positionChanged = true;
	}

	void Camera3D::setVertical(const Vector3f vert)
	{
		m_vertical = vert;
		m_positionChanged = true;
	}

	void Camera3D::setForward(const Vector3f fw)
	{
		m_forward = fw;
		m_positionChanged = true;
	}

	void Camera3D::look()
	{
	#if defined ZN_OPENGL2 //{

		// Projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(m_fov,
			m_viewportSize.x / m_viewportSize.y, m_near, m_far);

		// Orientation
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		const Vector3f target = m_pos + m_forward;
		gluLookAt(
			m_pos.x, m_pos.y, m_pos.z,
			target.x, target.y, target.z,
			m_vertical.x, m_vertical.y, m_vertical.z);

		m_positionChanged = false;
		m_projectionChanged = false;

	#elif defined ZN_OPENGL3
		#error "This file doesn't supports OpenGL 3"
	#endif // if
	}

} // namespace zn



