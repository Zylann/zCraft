/*
GuiRenderer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/opengl/opengl.hpp"
#include "OGLGuiRenderer.hpp"

namespace zn
{
namespace ui
{
	OGLGuiRenderer::OGLGuiRenderer() : ui::IRenderer()
	{
		r_font = nullptr;
	}

	OGLGuiRenderer::~OGLGuiRenderer()
	{
		// Free fonts
		for(auto & p : m_fonts)
		{
			if(p.second != nullptr)
				delete p.second;
		}
		m_fonts.clear();
	}

	void OGLGuiRenderer::begin()
	{
	#if defined ZN_OPENGL2
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void OGLGuiRenderer::end()
	{
	#if defined ZN_OPENGL2
		glPopMatrix();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	bool OGLGuiRenderer::loadTexture(ui::Texture & /*texture*/)
	{
		return false; // Not supported
	}

	bool OGLGuiRenderer::freeTexture(ui::Texture & /*texture*/)
	{
		return false; // Not supported
	}

	bool OGLGuiRenderer::loadFont(ui::Font & font)
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

	bool OGLGuiRenderer::freeFont(ui::Font & font)
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

	void OGLGuiRenderer::setColor(const Color & color)
	{
		m_color = color;
	}

	void OGLGuiRenderer::setLineWidth(unsigned int w)
	{
		glLineWidth(w);
	}

	void OGLGuiRenderer::setTexture(ui::Texture & /*texture*/)
	{
		// Not supported
	}

	void OGLGuiRenderer::setTextureClip(const IntRect /*clip*/)
	{
		// Not supported
	}

	void OGLGuiRenderer::setFont(ui::Font & font)
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			r_font = it->second;
	}

	void OGLGuiRenderer::drawLine(float xa, float ya, float xb, float yb)
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

	void OGLGuiRenderer::drawRect(zn::IntRect rect, bool fill)
	{
	#if defined ZN_OPENGL2
		glColor4ub(m_color.r, m_color.g, m_color.b, m_color.a);

		if(fill)
			glBegin(GL_QUADS);
		else
			glBegin(GL_LINE_LOOP);

		glVertex2f(rect.min.x, rect.min.y);
		glVertex2f(rect.max.x, rect.min.y);
		glVertex2f(rect.max.x, rect.max.y);
		glVertex2f(rect.min.x, rect.max.y);

		glEnd();
	#else
		#error "OpenGL3 not supported"
	#endif
	}

	void OGLGuiRenderer::drawText(const std::wstring & text, int x, int y, int begin, int end)
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

	Vector2i OGLGuiRenderer::getTextSize(ui::Font & font, const std::wstring &text, int begin, int end) const
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			return it->second->getTextSize(text, begin, end);
		return Vector2i();
	}

	int OGLGuiRenderer::getFontLineHeight(ui::Font &font) const
	{
		auto it = m_fonts.find(font.ID);
		if(it != m_fonts.end())
			return it->second->getLineHeight();
		return 0;
	}

} // namespace ui
} // namespace zn

