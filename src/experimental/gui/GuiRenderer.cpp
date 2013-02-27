/*
GuiRenderer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/opengl/opengl.hpp"
#include "GuiRenderer.hpp"

using namespace zn;

namespace experimental
{
	void GuiRenderer::begin()
	{
	#if defined ZN_OPENGL2
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void GuiRenderer::end()
	{
	#if defined ZN_OPENGL2
		glPopMatrix();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	bool GuiRenderer::loadTexture(ui::Texture & texture)
	{
		return false;
	}

	bool GuiRenderer::freeTexture(ui::Texture & texture)
	{
		return false;
	}

	bool GuiRenderer::loadFont(ui::Font & font)
	{
		return false;
	}

	bool GuiRenderer::freeFont(ui::Font & font)
	{
		return false;
	}

	void GuiRenderer::setColor(const Color & color)
	{
		m_color = color;
	}

	void GuiRenderer::setLineWidth(unsigned int w)
	{
		glLineWidth(w);
	}

	void GuiRenderer::setTexture(ui::Texture & texture)
	{

	}

	void GuiRenderer::setTextureClip(const IntRect clip)
	{

	}

	void GuiRenderer::setFont(ui::Font & font)
	{

	}

	void GuiRenderer::drawLine(float xa, float ya, float xb, float yb)
	{
	#if defined ZN_OPENGL2
		glColor4ub(m_color.r, m_color.g, m_color.b, m_color.a);
		glBegin(GL_LINES);
		glVertex2f(xa, ya);
		glVertex2f(xb, yb);
		glEnd();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void GuiRenderer::drawRect(float x, float y, float w, float h, bool fill)
	{
	#if defined ZN_OPENGL2
		glColor4ub(m_color.r, m_color.g, m_color.b, m_color.a);

		if(fill)
			glBegin(GL_QUADS);
		else
			glBegin(GL_LINE_LOOP);

		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);

		glEnd();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void GuiRenderer::drawText(const std::string & text, int x, int y, int begin, int end)
	{

	}

	int GuiRenderer::getFontLineHeight(ui::Font & font) const
	{
		return 0;
	}

	Vector2i GuiRenderer::getTextSize(ui::Font & font, const std::string & text, int begin, int end)
	{
		return Vector2i();
	}


} // namespace experimental

