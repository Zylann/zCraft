/*
Label.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_TEXTLABEL_HPP_INCLUDED
#define ZENGUI_TEXTLABEL_HPP_INCLUDED

#include "Widget.hpp"

namespace zn
{
namespace ui
{
	class TextLabel : public AWidget
	{
	private :

		std::string m_text;

	public :

		TextLabel() : AWidget() {}
		virtual ~TextLabel() {}

		void setText(const std::string & text);

		inline const std::string & getText() const { return m_text; }

		void render(IRenderer & r) override;

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_TEXTLABEL_HPP_INCLUDED
