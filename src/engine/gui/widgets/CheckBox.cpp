/*
CheckBox.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "CheckBox.hpp"
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	CheckBox::CheckBox() : AComposite()
	{
		m_checked = false;
		r_text = new Text();
		r_text->setPadding(Padding(4,4,4,4));
		add(r_text);
	}

	void CheckBox::setText(const std::wstring str)
	{
		// TODO CheckBox: update text rect after setText()
		r_text->setText(str);
	}

	void CheckBox::setChecked(bool check)
	{
		if(check != m_checked)
		{
			m_checked = check;
			onChangeSignal(m_checked);
		}
	}

	void CheckBox::renderSelf(IRenderer &r)
	{
		// TODO CheckBox: find a way to let the skin draw text
		r_skin->drawCheckBox(r, *this, m_checked);
	}

	void CheckBox::onSizeChanged()
	{
		// TODO CheckBox: use layout for this
		int offX = m_localBounds.height();
		r_text->setLocalBounds(IntRect(
			offX, 0, m_localBounds.width()-offX, m_localBounds.height()-1));
	}

	void CheckBox::onRelease()
	{
		setChecked(!m_checked);
	}

} // namespace ui
} // namespace zn

