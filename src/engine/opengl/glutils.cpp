#include <iostream>
#include <GL/glew.h>

namespace engine
{
namespace gl
{
	void drawAxes()
	{
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
	}

	void drawAxes(float scale)
	{
		glPushMatrix();
		glScalef(scale, scale, scale);
		drawAxes();
		glPopMatrix();
	}

	bool initOpenglExtensions(bool requireVBO, bool requireShaders)
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

		// TODO glutils: check shaders support using glew

		return true;
	}

	void fillRect(const float x, const float y, const float w, const float h)
	{
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();
	}

	void drawRect(const float x, const float y, const float w, const float h)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();
	}

	void drawCross(const float x, const float y, const float s = 1)
	{
		glBegin(GL_LINES);
		glVertex2f(x - s, y);
		glVertex2f(x + s, y);
		glVertex2f(x, y - s);
		glVertex2f(x, y + s);
		glEnd();
	}

	void drawGrid(const float cx, const float cy, const float r)
	{
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
	}

	void drawTestCube(const float c)
	{
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
	}

	void drawCubeLines(const float c = 1)
	{
		// Bottom
		glBegin(GL_LINE_STRIP);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f( c,  c, -c);
		glVertex3f( c, -c, -c);
		glEnd();

		// Top
		glBegin(GL_LINE_STRIP);
		glVertex3f(-c, -c, c);
		glVertex3f(-c,  c, c);
		glVertex3f( c,  c, c);
		glVertex3f( c, -c, c);
		glEnd();

		// West
		glBegin(GL_LINE_STRIP);
		glVertex3f(-c, -c, -c);
		glVertex3f(-c,  c, -c);
		glVertex3f(-c,  c,  c);
		glVertex3f(-c, -c,  c);
		glEnd();

		// East
		glBegin(GL_LINE_STRIP);
		glVertex3f(c, -c, -c);
		glVertex3f(c,  c, -c);
		glVertex3f(c,  c,  c);
		glVertex3f(c, -c,  c);
		glEnd();

		// South
		glBegin(GL_LINE_STRIP);
		glVertex3f(-c, -c,  c);
		glVertex3f(-c, -c, -c);
		glVertex3f( c, -c, -c);
		glVertex3f( c, -c,  c);
		glEnd();

		// North
		glBegin(GL_LINE_STRIP);
		glVertex3f(-c, c,  c);
		glVertex3f(-c, c, -c);
		glVertex3f( c, c, -c);
		glVertex3f( c, c,  c);
		glEnd();
	}

} // namespace gl
} // namespace engine



