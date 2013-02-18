#ifndef OPENGL_HPP_INCLUDED
#define OPENGL_HPP_INCLUDED

#include <GL/glew.h>

#include "engine/types.hpp"

namespace experimental
{
namespace gl
{
	// These constants are used to identify generic shader attributes
	// for OpenGL 3.x. They are not required by GL, but it's good to define
	// them once for a custom render pipeline.
	// >> See ShaderProgram
	enum ShaderIn
	{
		POSITION = 0,
		COLOR = 1,
		TEXCOORD0 = 2,
		NORMAL = 3
	};

	// Compiles required basic shaders and
	// initializes all available OpenGL extensions using GLEW and returns true if success.
	// Returns false and prints an error message if GLEW init failed,
	// or if one of required options (parameters) are not available.
	bool init(bool requireVBO = true, bool requireShaders = true);

	void beginRender();

	void endRender();

	void dispose();

	void color(engine::u8 r, engine::u8 g, engine::u8 b, engine::u8 a = 255);

	void useProgram(const GLuint ID);

	/* The methods below use immediate-rendering. */

	void drawAxes();

	void drawTexturedRect(
		const engine::f32 x, const engine::f32 y, const engine::f32 w, const engine::f32 h,
		const engine::f32 tx=0, const engine::f32 ty=0, const engine::f32 tw=1, const engine::f32 th=1);

	void drawTestCube();


} // namespace gl
} // namespace experimental

#endif // OPENGL_HPP_INCLUDED
