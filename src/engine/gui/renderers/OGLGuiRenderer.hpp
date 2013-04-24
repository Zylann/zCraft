/*
OGLGuiRenderer.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_UI_OGLGUIRENDERER__HPP_INCLUDED
#define ZN_UI_OGLGUIRENDERER__HPP_INCLUDED

#include <unordered_map>
#include "../Renderer.hpp"
#include "engine/bmfont/Font.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief This is an OpenGL2 renderer for zENGui using a custom BMFont implementation.
	 * @note in the future, I think it will use SFML for texture loading.
	 */
	class OGLGuiRenderer : public IRenderer
	{
	private :

		zn::Color m_color; // Current color
		zn::bmfont::Font * r_font; // Current font

		std::unordered_map<std::string,zn::bmfont::Font*> m_fonts;

	public :

		OGLGuiRenderer();
		virtual ~OGLGuiRenderer();

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
		void drawRect(zn::IntRect rect, bool fill) override;
		void drawText(const std::wstring &text, int x, int y, int begin, int end) override;

		zn::Vector2i getTextSize(zn::ui::Font & font, const std::wstring & text, int begin, int end) const override;
		int getFontLineHeight(zn::ui::Font & font) const override;

	};

} // namespace ui
} // namespace zn


#endif // ZN_UI_OGLGUIRENDERER_HPP_INCLUDED
