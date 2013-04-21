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

		static const Color borderColor(160, 160, 160);
		static const Color borderColorHover(224, 224, 224);
		static const Color borderColorFocus(0xff8800ff);
		static const Color borderColorFocusHover(0xffc481ff);
		static const Color fillColor(64, 64, 64);
		static const Color fillColorPress(48, 48, 48);

		if(panel.isPressed())
			r.setColor(fillColorPress);
		else
			r.setColor(fillColor);

		r.drawRect(bounds, true); // Fill

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

		r.drawRect(bounds.pad(1), false); // Border
	}

} // namespace ui
} // namespace zn






