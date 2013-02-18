#ifndef GLUTILS_HPP_INCLUDED
#define GLUTILS_HPP_INCLUDED

/*
	This header declares several utility functions dealing with OpenGL.
	If you want to use OpenGL or SFML graphics stuff, just include this header.
*/

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "engine/types.hpp"

namespace zn
{
namespace gl
{
	/// Draws 1-unit-sized 3D axes. X:red, Y:green, Z:blue
	void drawAxes();

	/// Draws scaled 3D axes. X:red, Y:green, Z:blue
	void drawAxes(float scale);

	/// Initializes all available OpenGL extensions using GLEW and returns true if success.
	/// Returns false and prints an error message if GLEW init failed,
	/// or if one of required options (parameters) are not available.
	bool initExtensions(bool requireVBO = true, bool requireShaders = true);

	void fillRect(const float x, const float y, const float w, const float h);

	void drawRect(const float x, const float y, const float w, const float h);

	void drawTexturedRect(
		const f32 x, const f32 y, const f32 w, const f32 h,
		const f32 tx=0, const f32 ty=0, const f32 tw=0, const f32 th=0);

	void drawCross(const float x, const float y, const float s = 1);

	void drawGrid(const float cx, const float cy, const float r);

	void drawTestCube(const float c = 1);

	void drawCubeLines(const float c = 1);

	void fillCircle(const float x, const float y, const float r);

} // namespace gl
} // namespace zn

#endif // GLUTILS_HPP_INCLUDED



