/*
GuiRenderer.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXPERIMENTAL_GUIRENDERER_HPP_INCLUDED
#define EXPERIMENTAL_GUIRENDERER_HPP_INCLUDED

#include <unordered_map>
#include "zengui/Renderer.hpp"
#include "engine/bmfont/Font.hpp"

namespace experimental
{
	class GuiRenderer : public zn::ui::IRenderer
	{
	private :

		zn::Color m_color; // Current color
		zn::bmfont::Font * r_font; // Current font

		std::unordered_map<std::string,zn::bmfont::Font*> m_fonts;

	public :

		GuiRenderer();
		virtual ~GuiRenderer();

		void begin() override;

		void end() override;

		bool loadTexture(zn::ui::Texture & texture) override;

		bool freeTexture(zn::ui::Texture & texture) override;

		bool loadFont(zn::ui::Font & font) override;

		bool freeFont(zn::ui::Font & font) override;

		void setColor(const zn::Color & color) override;

		void setLineWidth(unsigned int w) override;

		void setTexture(zn::ui::Texture & texture) override;

		void setTextureClip(const zn::IntRect clip) override;

		void setFont(zn::ui::Font & font) override;

		void drawLine(float xa, float ya, float xb, float yb) override;

		void drawRect(float x, float y, float w, float h, bool fill) override;

		void drawText(const std::string & text, int x, int y, int begin, int end) override;

		zn::Vector2i getTextSize(zn::ui::Font & font, const std::string & text, int begin, int end) override;

		int getFontLineHeight(zn::ui::Font & font) override;

	};

} // namespace experimental


#endif // GUIRENDERER_HPP_INCLUDED
