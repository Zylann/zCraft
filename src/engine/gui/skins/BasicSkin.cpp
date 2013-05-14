#include "BasicSkin.hpp"

namespace zn
{
namespace ui
{
	BasicSkin::BasicSkin(std::string name,
			std::string globalFontFilepath,
			std::string globalMonoFontFilepath)
	{
		m_defaultFont.src = globalFontFilepath;
		m_defaultFont.ID = "global";

		m_defaultMonoFont.src = globalMonoFontFilepath;
		m_defaultMonoFont.ID = "global_mono";

		m_name = name;

		lightColor = Color(0xff8800ff); // Orange
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

	Font &BasicSkin::getDefaultMonoFont()
	{
		return m_defaultMonoFont;
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
		static const Color fillColor(64, 64, 64, 224);

		r.setColor(fillColor);
		r.drawRect(bounds.pad(1), true); // Fill

		if(panel.isFocused())
			r.setColor(lightColor);
		else
			r.setColor(borderColor);
		r.drawRect(bounds, false); // Border
	}

	void BasicSkin::drawPushButton(IRenderer &r, const AWidget &btn)
	{
		IntRect bounds = btn.getBounds();

		static const Color borderColor(0, 0, 0);
		static const Color borderColorHover(0, 0, 0);
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
				r.setColor(lightColor);
			else
				r.setColor(borderColorHover);
		}
		else
		{
			if(btn.isFocused())
				r.setColor(lightColor);
			else
				r.setColor(borderColor);
		}

		r.drawRect(bounds, false); // Border
	}

	void BasicSkin::drawCheckBox(IRenderer &r, const AWidget &cb, bool checked)
	{
		IntRect boxBounds = cb.getBounds();
		boxBounds.max.x = boxBounds.min.x + boxBounds.height();
		boxBounds.pad(-2);

		static const Color borderColor(0, 0, 0);
		static const Color fillColor(96, 96, 96);
		static const Color fillColorPress(128, 128, 128);
		static const Color uncheckColor(48, 48, 48);

		if(cb.isPressed())
			r.setColor(fillColorPress);
		else
			r.setColor(fillColor);
		r.drawRect(boxBounds.pad(1), true); // Fill

		if(cb.isFocused())
			r.setColor(lightColor);
		else
			r.setColor(borderColor);
		r.drawRect(boxBounds, false); // Border

		if(checked)
			r.setColor(lightColor);
		else
			r.setColor(uncheckColor);
		r.drawRect(boxBounds.pad(-3, -4, -4, -3), true);
	}

	void BasicSkin::drawTextField(IRenderer &r, const AWidget &tf)
	{
		IntRect bounds = tf.getBounds();

		static const Color borderColor(0, 0, 0);
		static const Color fillColor(32, 32, 32);

		r.setColor(fillColor);
		r.drawRect(bounds.pad(1), true); // Fill

		if(tf.isFocused())
			r.setColor(lightColor);
		else
			r.setColor(borderColor);
		r.drawRect(bounds, false); // Border
	}

	void BasicSkin::drawProgressBar(IRenderer &r, const AWidget &pb, float ratio)
	{
		IntRect bounds = pb.getBounds();

//		static const Color borderColor(0, 0, 0);
		static const Color fillColor(32, 32, 32);

		r.setColor(fillColor);
		r.drawRect(bounds.pad(1), true); // Fill

//		r.setColor(borderColor);
//		r.drawRect(bounds, false); // Border

		// Progress
		if(ratio > 0.001f)
		{
			bounds.pad(-3, -3, -3, -3);
			bounds.max.x = bounds.min.x + static_cast<float>(bounds.width()) * ratio;
			r.setColor(lightColor);
			r.drawRect(bounds, true);
		}
	}

	void BasicSkin::drawSlider(IRenderer &r, const Slider &s)
	{
		IntRect bounds = s.getBounds();
		IntRect cursorBounds = bounds;

		static const Color backColor(32,32,32);
		static const Color borderColor(0, 0, 0);
		static const Color fillColor(96, 96, 96);
		//static const Color fillColorPress(112, 112, 112);

		// Back

		r.setColor(backColor);
		if(s.getOrientation() == Slider::HORIZONTAL)
			r.drawRect(bounds.pad(0, -5, 0, -5), true);
		else
			r.drawRect(bounds.pad(-5, 0, -5, 0), true);

		// Cursor

		if(s.getOrientation() == Slider::HORIZONTAL)
		{
			cursorBounds.max.x = cursorBounds.min.x + 8;
			cursorBounds.offset(s.getRatio() * static_cast<float>(bounds.width() - 8), 0);
		}
		else
		{
			// Note : Y is inverted because UP is the max value for users
			cursorBounds.min.y = cursorBounds.max.y - 8;
			cursorBounds.offset(0, -s.getRatio() * static_cast<float>(bounds.height() - 8));
		}

		r.setColor(fillColor);
		r.drawRect(cursorBounds.pad(1), true); // Fill

		if(s.isFocused())
			r.setColor(lightColor);
		else
			r.setColor(borderColor);
		r.drawRect(cursorBounds, false); // Border
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






