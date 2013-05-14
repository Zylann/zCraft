/*
Skin.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_UI_TEXTFIELD_HPP
#define ZN_UI_TEXTFIELD_HPP

#include "../Composite.hpp"
#include "Text.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief A simple one-line editable text area.
	 */
	class TextField : public AComposite
	{
	public:

		TextField();
		virtual ~TextField();

		WidgetType getType() const override { return TEXT_FIELD; }

		void setText(const std::wstring str);
		std::wstring getText() const;

		void setSecret(bool s);
		inline bool isSecret() const { return r_text->isSecret(); }

		inline unsigned int getCaretIndex() const { return m_caretIndex; }

	protected:

		virtual void renderSelf(IRenderer & r) override;

		virtual bool mousePressed(Mouse::Button button) override;
		virtual bool keyPressed(Keyboard::Key key) override;
		virtual bool textEntered(unsigned int unicode) override;

	private:

		void updateCaret();

		Text * r_text;
		unsigned int m_caretIndex;
		int m_caretPosX;
		bool m_caretNeedUpdate;

	};

} // namespace ui
} // namespace zn

#endif // ZN_UI_TEXTFIELD_HPP


