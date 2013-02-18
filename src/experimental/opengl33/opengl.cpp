/*
opengl.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>

#include "engine/types.hpp"
#include "opengl.hpp"
#include "ShaderProgram.hpp"

using namespace engine;

namespace experimental
{
namespace gl
{
	ShaderProgram g_colorShader;
	ShaderProgram g_textureShader;
	//u32 g_currentShader;
	Matrix4 g_modelview;
	Matrix4 g_projection;

	bool init(bool requireVBO, bool requireShaders)
	{
		/* Init extensions */

		GLuint glewInitCode = glewInit();
		if(glewInitCode != GLEW_OK)
		{
			std::cout << "ERROR: glewInit() failed : "
				<< glewGetErrorString(glewInitCode) << std::endl;
			return false;
		}

		// Check VBO support
		if(requireVBO && glewIsExtensionSupported("GL_ARB_vertex_buffer_object") == GL_FALSE)
		{
			std::cout << "ERROR: GL_ARB_vertex_buffer_object is not supported" << std::endl;
			return false;
		}

		// TODO opengl: check shaders support using glew

		/* Load shaders */

		if(!g_colorShader.load(
			"assets/shaders/basic3d.vert",
			"assets/shaders/basic.frag"))
		{
			return false;
		}

		if(!g_textureShader.load(
			"assets/shaders/basic3d.vert",
			"assets/shaders/textured.frag"))
		{
			return false;
		}

		return true;
	}

	void dispose()
	{

	}

	void useProgram(const GLuint ID)
	{
		glUseProgram(ID);
	}

	void beginRender()
	{
		glUseProgram(g_colorShader.getID());

		glEnableVertexAttribArray(ShaderIn::POSITION);
		glEnableVertexAttribArray(ShaderIn::COLOR);
		//glEnableVertexAttribArray(ShaderIn::TEXCOORD0);
		//glEnableVertexAttribArray(ShaderIn::NORMAL);
	}

	void endRender()
	{
		//glDisableVertexAttribArray(ShaderIn::NORMAL);
		//glDisableVertexAttribArray(ShaderIn::TEXCOORD0);
		glDisableVertexAttribArray(ShaderIn::COLOR);
		glDisableVertexAttribArray(ShaderIn::POSITION);

		glFlush();
	}

	void color(u8 r, u8 g, u8 b, u8 a)
	{
		glVertexAttrib4f(ShaderIn::COLOR, r/255.f, g/255.f, b/255.f, a/255.f);
	}

	/*
		Immediate-rendering
	*/

	// Note : I should have used indices and shaders to color lines,
	// but here there is not very much data

	u8 g_axes_positions[6*3] =
	{
		0, 0, 0,
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
		0, 0, 1
	};

	u8 g_axes_colors[6*3] =
	{
		1, 0, 0,
		1, 0, 0,
		0, 1, 0,
		0, 1, 0,
		0, 0, 1,
		0, 0, 1
	};

	void drawAxes()
	{
		glVertexAttribPointer(ShaderIn::POSITION, 3, GL_UNSIGNED_BYTE, GL_FALSE, 0, g_axes_positions);

		glVertexAttribPointer(ShaderIn::COLOR, 3, GL_UNSIGNED_BYTE, GL_FALSE, 0, g_axes_colors);

		glDrawArrays(GL_LINES, 0, 6);

	}

	void drawTexturedRect(
			const f32 x, const f32 y, const f32 w, const f32 h,
			const f32 tx, const f32 ty, const f32 tw, const f32 th)
	{
		const f32 positions[4*2] =
		{
			x, y,
			x+w, y,
			x+w, y+h,
			x, y+h
		};

		const f32 texCoords[4*2] =
		{
			tx, ty,
			tx+tw, ty,
			tx+tw, ty+th,
			tx, ty+th
		};

		glVertexAttribPointer(ShaderIn::POSITION, 2, GL_FLOAT, GL_FALSE, 0, positions);
		//glEnableVertexAttribArray(ShaderIn::POSITION);

		glVertexAttribPointer(ShaderIn::TEXCOORD0, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
		//glEnableVertexAttribArray(ShaderIn::TEXCOORD0);

		glDrawArrays(GL_QUADS, 0, 4);

		//glDisableVertexAttribArray(ShaderIn::TEXCOORD0);
		//glDisableVertexAttribArray(ShaderIn::POSITION);
	}

	float g_cubePositions[6*4*3]
	{
		// Bottom
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
		1, 0, 0,
		// Top
		0, 0, 1,
		0, 1, 1,
		1, 1, 1,
		1, 0, 1,
		// West
		0, 0, 0,
		0, 1, 0,
		0, 1, 1,
		0, 0, 1,
		// East
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
		1, 0, 1,
		// South
		0, 0, 1,
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		// North
		0, 1, 1,
		0, 1, 0,
		1, 1, 0,
		1, 1, 1
	};

	void drawTestCube()
	{

	}


} // namespace gl
} // namespace experimental




