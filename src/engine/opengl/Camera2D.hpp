/*
Camera2D.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_CAMERA2D_HPP_INCLUDED
#define ENGINE_CAMERA2D_HPP_INCLUDED

#include "engine/Vector2.hpp"

namespace engine
{
	class Camera2D
	{
	private :

		Vector2f m_center;
		f32 m_rotationDegrees;
		f32 m_zoom;
		Vector2f m_viewportSize;
		bool m_autoViewportUpdate;

	public :

		/// Creates an origin-centered camera with no zoom and no rotation,
		/// based on a viewport size. If not specified, the viewport size will
		/// have a default value.
		Camera2D(const Vector2f viewportSize = Vector2f(512));

		/// Configures OpenGL matrixes before drawing
		void look();

		void setZoom(const f32 z);

		void zoom(const f32 z);

		void setCenter(const f32 x, const f32 y);

		void setCenter(const Vector2f & pos);

		void setRotation(const f32 rotationDegrees);

		/// Manually updates the viewport size.
		void updateViewport(const Vector2f & viewportSize);

		/// If set to true, viewport size will be automatically checked
		/// when calling look() by querying OpenGL.
		void setAutoViewportUpdate(bool enable);

		void rotate(const f32 rotationDegrees);

		void move(const f32 x, const f32 y);

		void move(const Vector2f & vec);

		inline const Vector2f getViewport() const { return m_viewportSize; }

		inline const Vector2f getCenter() const { return m_center; }

		inline f32 getZoom() const { return m_zoom; }

		inline f32 getRotation() const { return m_rotationDegrees; }

		std::string toString() const;

	};

	std::ostream & operator<<(std::ostream & os, const Camera2D & cam);
	std::string operator+(std::string const & a, Camera2D const & b);

} // namespace engine


#endif // ENGINE_CAMERA2D_HPP_INCLUDED

