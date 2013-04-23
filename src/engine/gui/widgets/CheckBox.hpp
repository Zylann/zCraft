/*
CheckBox.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_CHECKBOX_HPP
#define ZENGUI_CHECKBOX_HPP

#include "../Composite.hpp"
#include "../Signal.hpp"
#include "Text.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief A two-state button composed of a little checkbox and a label.
	 * The clickable area is defined around both.
	 */
	class CheckBox : public AComposite
	{
	public:

		CheckBox();
		virtual ~CheckBox() {}

		WidgetType getType() const override { return CHECK_BOX; }

		void setText(const std::string text);

		inline bool isChecked() const { return m_checked; }
		void setChecked(bool check);

		Signal1<bool> onChangeSignal;

	protected:

		virtual void renderSelf(IRenderer & r) override;

		virtual void onSizeChanged() override;
		virtual void onRelease() override;

	private:

		Text * r_text;
		bool m_checked;
	};

} // namespace ui
} // namespace zn

#endif // CHECKBOX_HPP


