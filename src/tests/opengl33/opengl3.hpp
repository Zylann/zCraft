#ifndef ZN_OPENGL_HPP_INCLUDED
#define ZN_OPENGL_HPP_INCLUDED

#include <GL/glew.h>

#include "engine/core/types.hpp"

namespace experimental
{
namespace gl
{
	// Compiles required basic shaders and
	// initializes all available OpenGL extensions using GLEW and returns true if success.
	// Returns false and prints an error message if GLEW init failed,
	// or if one of required options (parameters) are not available.
	bool init(bool requireVBO = true, bool requireShaders = true);

	void beginRender();

	void endRender();

	void dispose();

	void color(zn::u8 r, zn::u8 g, zn::u8 b, zn::u8 a = 255);

	void useProgram(const GLuint ID);

	/* The methods below use immediate-rendering. */

	void drawAxes();

	void drawTexturedRect(
		const zn::f32 x, const zn::f32 y, const zn::f32 w, const zn::f32 h,
		const zn::f32 tx=0, const zn::f32 ty=0, const zn::f32 tw=1, const zn::f32 th=1);

	void drawTestCube();


} // namespace gl
} // namespace experimental

#endif // ZN_OPENGL_HPP_INCLUDED
