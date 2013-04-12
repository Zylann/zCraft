/*
Text.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_TEXT_HPP_INCLUDED
#define ZENGUI_TEXT_HPP_INCLUDED

#include <vector>
#include "Widget.hpp"
#include "Font.hpp"

namespace zn
{
namespace ui
{
	class Text : public AWidget
	{
		struct Line
		{
			std::string str;
			IntRect bounds;
		};

	private :

		// TODO Text: Unicode support
		std::string m_text;
		std::vector<Line> m_dispText;
		Font * r_font;
		bool m_textNeedUpdate;
		bool m_wrap;

	public :

		Text();
		virtual ~Text();

		void setText(const std::string & text);

		void setWrap(bool enable);

		void setFont(Font & font);

		inline Font * getFont() { return r_font; }

		inline const std::string & getText() const { return m_text; }

		void render(IRenderer & r) override;

	private :

		void updateText(IRenderer & r);

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_TEXT_HPP_INCLUDED
