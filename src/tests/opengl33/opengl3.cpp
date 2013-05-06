/*
opengl.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>

#include "engine/core/types.hpp"
#include "opengl3.hpp"
#include "engine/opengl/ShaderProgram.hpp"
#include "engine/core/Matrix4.hpp"

using namespace zn;

namespace experimental
{
namespace gl
{
	// Global variables are evil !
	// ShaderPrograms can cause end-of-app crashes if instancied statically.
	// That's why I use dynamic allocation as a workaround.
	// But that's not enough, later I will preferably write a classy renderer...

	zn::gl::ShaderProgram * g_colorShader;
	zn::gl::ShaderProgram * g_textureShader;
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

		g_colorShader = new zn::gl::ShaderProgram();
		if(!g_colorShader->load(
			"assets/shaders/150/basic3d.vert", "",
			"assets/shaders/150/basic.frag"))
		{
			return false;
		}

		g_textureShader = new zn::gl::ShaderProgram();
		if(!g_textureShader->load(
			"assets/shaders/150/basic3d.vert", "",
			"assets/shaders/150/textured.frag"))
		{
			return false;
		}

		return true;
	}

	void dispose()
	{
		if(g_colorShader != nullptr)
		{
			delete g_colorShader;
			g_colorShader = nullptr;
		}
		if(g_textureShader != nullptr)
		{
			delete g_textureShader;
			g_textureShader = nullptr;
		}
	}

	void useProgram(const GLuint ID)
	{
		glUseProgram(ID);
	}

	void beginRender()
	{
		glUseProgram(g_colorShader->getID());

		glEnableVertexAttribArray(zn::gl::Attrib::POSITION);
		glEnableVertexAttribArray(zn::gl::Attrib::COLOR);
		//glEnableVertexAttribArray(Attrib::TEXCOORD0);
		//glEnableVertexAttribArray(Attrib::NORMAL);
	}

	void endRender()
	{
		//glDisableVertexAttribArray(Attrib::NORMAL);
		//glDisableVertexAttribArray(Attrib::TEXCOORD0);
		glDisableVertexAttribArray(zn::gl::Attrib::COLOR);
		glDisableVertexAttribArray(zn::gl::Attrib::POSITION);

		glFlush();
	}

	void color(u8 r, u8 g, u8 b, u8 a)
	{
		glVertexAttrib4f(zn::gl::Attrib::COLOR, r/255.f, g/255.f, b/255.f, a/255.f);
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
		glVertexAttribPointer(zn::gl::Attrib::POSITION, 3, GL_UNSIGNED_BYTE, GL_FALSE, 0, g_axes_positions);

		glVertexAttribPointer(zn::gl::Attrib::COLOR, 3, GL_UNSIGNED_BYTE, GL_FALSE, 0, g_axes_colors);

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

		glVertexAttribPointer(zn::gl::Attrib::POSITION, 2, GL_FLOAT, GL_FALSE, 0, positions);
		//glEnableVertexAttribArray(Attrib::POSITION);

		glVertexAttribPointer(zn::gl::Attrib::TEXCOORD0, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
		//glEnableVertexAttribArray(Attrib::TEXCOORD0);

		glDrawArrays(GL_QUADS, 0, 4);

		//glDisableVertexAttribArray(Attrib::TEXCOORD0);
		//glDisableVertexAttribArray(Attrib::POSITION);
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




