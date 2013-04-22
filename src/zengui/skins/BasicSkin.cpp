#include "BasicSkin.hpp"

namespace zn
{
namespace ui
{
	BasicSkin::BasicSkin(std::string name, std::string globalFontFilepath)
	{
		m_defaultFont.src = globalFontFilepath;
		m_defaultFont.ID = "global";
		m_name = name;
	}

	bool BasicSkin::load(IRenderer &r)
	{
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
		static const Color borderColor(224, 224, 224);
		r.setColor(borderColor);
		r.drawRect(w.getBounds(), false);
	}

	void BasicSkin::drawPanel(IRenderer & r, const AWidget & panel)
	{
		IntRect bounds = panel.getBounds();

		static const Color borderColor(0, 0, 0);
		static const Color borderColorFocus(0xff8800ff);
		static const Color fillColor(64, 64, 64);

		r.setColor(fillColor);
		r.drawRect(bounds.pad(1), true); // Fill

		if(panel.isFocused())
			r.setColor(borderColorFocus);
		else
			r.setColor(borderColor);
		r.drawRect(bounds, false); // Border
	}

	void BasicSkin::drawPushButton(IRenderer &r, const AWidget &btn)
	{
		IntRect bounds = btn.getBounds();

		static const Color borderColor(0, 0, 0);
		static const Color borderColorHover(0, 0, 0);
		static const Color borderColorFocus(0xff8800ff);
		static const Color borderColorFocusHover(0xff8800ff);
		static const Color fillColor(96, 96, 96);
		static const Color fillColorPress(112, 112, 112);

		if(btn.isPressed())
			r.setColor(fillColorPress);
		else
			r.setColor(fillColor);

		r.drawRect(bounds.pad(1), true); // Fill

		if(btn.isHovered())
		{
			if(btn.isFocused())
				r.setColor(borderColorFocusHover);
			else
				r.setColor(borderColorHover);
		}
		else
		{
			if(btn.isFocused())
				r.setColor(borderColorFocus);
			else
				r.setColor(borderColor);
		}

		r.drawRect(bounds, false); // Border
	}

	void BasicSkin::drawDragZone(IRenderer & r, const AWidget & dz)
	{
		IntRect bounds = dz.getBounds();

		static const Color fillColor(64, 64, 64);
		static const Color fillColorHover(72, 72, 72);

		r.setColor(dz.isHovered() ? fillColorHover : fillColor);
		if(dz.isFocused())
			r.setColor(Color(96,96,96));
		r.drawRect(bounds, true); // Fill
	}

} // namespace ui
} // namespace zn






