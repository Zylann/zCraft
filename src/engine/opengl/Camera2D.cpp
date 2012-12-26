/*
Camera2D.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include <iostream>
#include "engine/opengl/glutils.hpp"
#include "engine/opengl/Camera2D.hpp"

namespace engine
{
	Camera2D::Camera2D(const Vector2f viewportSize)
	{
		m_rotationDegrees = 0;
		m_zoom = 1;
		m_viewportSize = viewportSize;
		m_autoViewportUpdate = true;
	}

	void Camera2D::look()
	{
		// Viewport-match 2D orthogonal view

		if(m_autoViewportUpdate)
		{
			GLint vps[4] = {0};
			glGetIntegerv(GL_VIEWPORT, vps);
			updateViewport(Vector2f(vps[2] - vps[0], vps[3] - vps[1]));
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, m_viewportSize.x, 0, m_viewportSize.y);

		// Apply translation, zoom and rotation

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// TODO Camera2D: optimize look()

		glScalef(
			m_viewportSize.x,
			m_viewportSize.y, 0);

		glScalef(
			1.f / (m_viewportSize.x / m_zoom),
			1.f / (m_viewportSize.y / m_zoom), 0);

		glTranslatef(
			-(m_center.x - m_viewportSize.x / m_zoom / 2.f),
			-(m_center.y - m_viewportSize.y / m_zoom / 2.f), 0);

		if(m_rotationDegrees != 0)
			glRotatef(m_rotationDegrees, 0, 0, 1);
	}

	void Camera2D::updateViewport(const Vector2f & viewportSize)
	{
		m_viewportSize = viewportSize;
	}

	void Camera2D::setZoom(const f32 z)
	{
		m_zoom = z != 0 ? z : 1;
	}

	void Camera2D::zoom(const f32 z)
	{
		m_zoom *= z != 0 ? z : 1;
	}

	void Camera2D::setCenter(const f32 x, const f32 y)
	{
		m_center.set(x, y);
	}

	void Camera2D::setCenter(const Vector2f & pos)
	{
		m_center = pos;
	}

	void Camera2D::setRotation(const f32 rotationDegrees)
	{
		m_rotationDegrees = rotationDegrees;
	}

	void Camera2D::rotate(const f32 rotationDegrees)
	{
		m_rotationDegrees += rotationDegrees;
	}

	void Camera2D::move(const f32 x, const f32 y)
	{
		m_center.x += x;
		m_center.y += y;
	}

	void Camera2D::move(const Vector2f & vec)
	{
		m_center += vec;
	}

	std::string Camera2D::toString() const
	{
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

	std::ostream & operator<<(std::ostream & os, const Camera2D & cam)
	{
		return os << "viewport: " << cam.getViewport()
			<< "center: " << cam.getCenter()
			<< ", zoom: " << cam.getZoom()
			<< ", rotation: " << cam.getRotation();
	}

	std::string operator+(std::string const & a, Camera2D const & b)
	{
		return a + b.toString();
	}

} // namespace engine




