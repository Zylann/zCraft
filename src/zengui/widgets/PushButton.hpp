/*
Button.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_BUTTON_HPP_INCLUDED
#define ZENGUI_BUTTON_HPP_INCLUDED

#include "../Composite.hpp"
#include "../Signal.hpp"
#include "Text.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief A simple push-button that emits a signal once clicked.
	 * (press and release are also supported).
	 */
	class PushButton : public AComposite
	{
	public :

		PushButton();
		virtual ~PushButton() {}

		WidgetType getType() const override { return PUSH_BUTTON; }

		void setText(const std::string & str);

		Signal0 onPressSignal;
		Signal0 onReleaseSignal;
		Signal0 onClickSignal;

	protected :

		virtual void renderSelf(IRenderer & r) override;

		virtual void onSizeChanged() override;
		virtual void onPress() override;
		virtual void onRelease() override;

	private :

		Text * r_text; // Reference to child widget

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_PUSHBUTTON_HPP_INCLUDED
