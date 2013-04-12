/*
BasicTheme.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "BasicSkin.hpp"
#include "zengui/Color.hpp"
#include "zengui/Renderer.hpp"

using namespace zn;
using namespace ui;

namespace experimental
{
	bool BasicSkin::load(IRenderer &r)
	{
		m_defaultFont.src = "assets/fonts/arial32.fnt";
		m_defaultFont.ID = "arial32";
		if(!r.loadFont(m_defaultFont))
			return false;
		return true;
	}

	bool BasicSkin::unload(IRenderer &r)
	{
		if(!r.freeFont(m_defaultFont))
			return false;
		return true;
	}

	Font &BasicSkin::getDefaultFont()
	{
		return m_defaultFont;
	}

	void BasicSkin::drawDummyWidget(IRenderer & r, const AWidget & w)
	{
		Vector2i pos = w.getAbsolutePosition();
		const int width = w.getBounds().width();
		const int height = w.getBounds().height();

		static const Color borderColor(224, 224, 224);

		r.setColor(borderColor);
		r.drawRect(pos.x, pos.y, width, height, false);
	}

	void BasicSkin::drawPanel(IRenderer & r, const AWidget & panel)
	{
		Vector2i pos = panel.getAbsolutePosition();
		const int width = panel.getBounds().width();
		const int height = panel.getBounds().height();

		static const Color borderColor(160, 160, 160);
		static const Color borderColorHover(224, 224, 224);
		static const Color borderColorFocus(0xff8800ff);
		static const Color borderColorFocusHover(0xffc481ff);
		static const Color fillColor(64, 64, 64);
		static const Color fillColorPress(48, 48, 48);

		if(panel.isHovered())
		{
			if(panel.isFocused())
				r.setColor(borderColorFocusHover);
			else
				r.setColor(borderColorHover);
		}
		else
		{
			if(panel.isFocused())
				r.setColor(borderColorFocus);
			else
				r.setColor(borderColor);
		}

		r.drawRect(pos.x, pos.y-1, width+1, height+1, false);

		if(panel.isPressed())
			r.setColor(fillColorPress);
		else
			r.setColor(fillColor);
		r.drawRect(pos.x, pos.y, width, height, true);
	}

} // namespace experimental





