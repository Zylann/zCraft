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
	GuiRenderer::GuiRenderer() : ui::IRenderer()
	{
		r_font = nullptr;
	}

	GuiRenderer::~GuiRenderer()
	{
		// Free fonts
		for(auto & p : m_fonts)
		{
			if(p.second != nullptr)
				delete p.second;
		}
		m_fonts.clear();
	}

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

	bool GuiRenderer::loadTexture(ui::Texture & /*texture*/)
	{
		return false; // Not supported
	}

	bool GuiRenderer::freeTexture(ui::Texture & /*texture*/)
	{
		return false; // Not supported
	}

	bool GuiRenderer::loadFont(ui::Font & font)
	{
		zn::bmfont::Font * asset = new zn::bmfont::Font();
		if(!asset->loadFromFile(font.src))
		{
			delete asset;
			return false;
		}
		//font.lineHeight = asset->getLineHeight();
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
		{
			delete it->second;
			it->second = asset;
		}
		else
			m_fonts[font.ID] = asset;
		return true;
	}

	bool GuiRenderer::freeFont(ui::Font & font)
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
		{
			delete it->second;
			m_fonts.erase(it);
			return true;
		}
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

	void GuiRenderer::setTexture(ui::Texture & /*texture*/)
	{
		// Not supported
	}

	void GuiRenderer::setTextureClip(const IntRect /*clip*/)
	{
		// Not supported
	}

	void GuiRenderer::setFont(ui::Font & font)
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			r_font = it->second;
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
		glVertex2f(x+w-1 , y);
		glVertex2f(x+w-1, y+h-1);
		glVertex2f(x, y+h-1);

		glEnd();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void GuiRenderer::drawText(const std::string & text, int x, int y, int begin, int end)
	{
		if(r_font == nullptr)
			return;
	#if defined ZN_OPENGL2
		glColor4ub(m_color.r, m_color.g, m_color.b, m_color.a);
		r_font->draw(text, x, y);
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	Vector2i GuiRenderer::getTextSize(ui::Font & font, const std::string & text, int begin, int end)
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			return it->second->getTextSize(text, begin, end);
		return Vector2i();
	}

	int GuiRenderer::getFontLineHeight(ui::Font &font)
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			return it->second->getLineHeight();
		return 0;
	}

} // namespace experimental

