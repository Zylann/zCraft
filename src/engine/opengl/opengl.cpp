#include <iostream>
#include <GL/glew.h>
#include <cmath>

#include "engine/opengl/opengl.hpp"

#ifdef ZN_OPENGL3
	#error "This file doesn't supports OpenGL 3, and is outdated. Use opengl.hpp instead (experimental)"
#endif // ZN_OPENGL3

namespace engine
{
namespace gl
{
	void drawAxes()
	{
	#if defined ZN_OPENGL2
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawAxes doesn't supports OpenGL 3"
	#endif
	}

	void drawAxes(float scale)
	{
	#if defined ZN_OPENGL2
		glPushMatrix();
		glScalef(scale, scale, scale);
		drawAxes();
		glPopMatrix();
	#elif defined ZN_OPENGL3
		#warning "gl::drawAxes doesn't supports OpenGL 3"
	#endif
	}

	bool initExtensions(bool requireVBO, bool requireShaders)
	{
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

		return true;
	}

	void fillRect(const float x, const float y, const float w, const float h)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::fillRect doesn't supports OpenGL 3"
	#endif
	}

	void drawRect(const float x, const float y, const float w, const float h)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawRect doesn't supports OpenGL 3"
	#endif
	}

	void drawTexturedRect(
			const f32 x, const f32 y, const f32 w, const f32 h,
			const f32 tx, const f32 ty, const f32 tw, const f32 th)
	{
	#ifdef ZN_OPENGL2
		glBegin(GL_QUADS);

		glTexCoord2f(tx, ty);
		glVertex2i(x, y);

		glTexCoord2f(tx + tw, ty);
		glVertex2i(x + w, y);

		glTexCoord2f(tx + tw, ty + th);
		glVertex2i(x + w, y + h);

		glTexCoord2f(tx, ty + th);
		glVertex2i(x, y + h);

		glEnd();
	#elif defined ZN_OPENGL3
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
		glEnableVertexAttribArray(ShaderIn::POSITION);

		glVertexAttribPointer(ShaderIn::TEXCOORD0, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
		glEnableVertexAttribArray(ShaderIn::TEXCOORD0);


		glDrawArrays(GL_QUADS, 0, 4);

		glDisableVertexAttribArray(ShaderIn::COLOR);
		glDisableVertexAttribArray(ShaderIn::POSITION);
	#endif // defined
	}

	void drawCross(const float x, const float y, const float s)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_LINES);
		glVertex2f(x - s, y);
		glVertex2f(x + s, y);
		glVertex2f(x, y - s);
		glVertex2f(x, y + s);
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawCross doesn't supports OpenGL 3"
	#endif
	}

	void drawGrid(const float cx, const float cy, const float r)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_LINES);
		for(float x = cx - r; x < cx + r; x++)
		{
			glVertex2f(x, cy - r);
			glVertex2f(x, cy + r);
		}
		glEnd();

		glBegin(GL_LINES);
		for(float y = cy - r; y < cy + r; y++)
		{
			glVertex2f(cx - r, y);
			glVertex2f(cx + r, y);
		}
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawGrid doesn't supports OpenGL 3"
	#endif
	}

	void drawTestCube(const float c)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_QUADS);

		// Bottom
		glColor3ub(0, 0, 255);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f( c,  c, -c);
		glVertex3f( c, -c, -c);

		// Top
		glColor3ub(0, 255, 255);
		glVertex3f(-c, -c, c);
		glVertex3f(-c,  c, c);
		glVertex3f( c,  c, c);
		glVertex3f( c, -c, c);

		// West
		glColor3ub(255, 0, 0);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f(-c,  c,  c);
		glVertex3f(-c, -c,  c);

		// East
		glColor3ub(255, 255, 0);
		glVertex3f(c, -c, -c);
		glVertex3f(c,  c, -c);
		glVertex3f(c,  c,  c);
		glVertex3f(c, -c,  c);

		// South
		glColor3ub(0, 128, 0);
		glVertex3f(-c, -c,  c);
		glVertex3f(-c, -c, -c);
		glVertex3f( c, -c, -c);
		glVertex3f( c, -c,  c);

		// North
		glColor3ub(0, 255, 0);
		glVertex3f(-c, c,  c);
		glVertex3f(-c, c, -c);
		glVertex3f( c, c, -c);
		glVertex3f( c, c,  c);

		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawTestCube doesn't supports OpenGL 3"
	#endif
	}

	void drawCubeLines(const float c)
	{
	#if defined ZN_OPENGL2
		// Bottom
		glBegin(GL_LINE_LOOP);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f( c,  c, -c);
		glVertex3f( c, -c, -c);
		glEnd();

		// Top
		glBegin(GL_LINE_LOOP);
		glVertex3f(-c, -c, c);
		glVertex3f(-c,  c, c);
		glVertex3f( c,  c, c);
		glVertex3f( c, -c, c);
		glEnd();

		// West
		glBegin(GL_LINE_LOOP);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f(-c,  c,  c);
		glVertex3f(-c, -c,  c);
		glEnd();

		// East
		glBegin(GL_LINE_LOOP);
		glVertex3f(c, -c, -c);
		glVertex3f(c,  c, -c);
		glVertex3f(c,  c,  c);
		glVertex3f(c, -c,  c);
		glEnd();

		// South
		glBegin(GL_LINE_LOOP);
		glVertex3f(-c, -c,  c);
		glVertex3f(-c, -c, -c);
		glVertex3f( c, -c, -c);
		glVertex3f( c, -c,  c);
		glEnd();

		// North
		glBegin(GL_LINE_LOOP);
		glVertex3f(-c, c,  c);
		glVertex3f(-c, c, -c);
		glVertex3f( c, c, -c);
		glVertex3f( c, c,  c);
		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::drawCubeLines doesn't supports OpenGL 3"
	#endif
	}

	void fillCircle(const float x, const float y, const float r)
	{
	#if defined ZN_OPENGL2
		glBegin(GL_POLYGON);

		for(float t = -3.1415; t < 3.1415; t += 0.2f)
			glVertex2f(x + r * cos(t), y + r * sin(t));

		glEnd();
	#elif defined ZN_OPENGL3
		#warning "gl::fillCircle doesn't supports OpenGL 3"
	#endif
	}

} // namespace gl
} // namespace engine



