/*
Button.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_BUTTON_HPP_INCLUDED
#define ZENGUI_BUTTON_HPP_INCLUDED

#include "Widget.hpp"

namespace zn
{
	class AButton
	{
	private :

		std::string m_text;

	public :

		Signal onPress;
		Signal onRelease;
		Signal onClick;

		AButton(const std::string text = "");


	};

} // namespace zn

#endif // ZENGUI_PUSHBUTTON_HPP_INCLUDED
