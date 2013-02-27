/*
Theme.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_THEME_HPP_INCLUDED
#define ZENGUI_THEME_HPP_INCLUDED

#include "Widget.hpp"

namespace zn
{
namespace ui
{
	/*
		A theme is a kind of widget renderer.
		It can either use the generic GUI renderer (more portable)
		or use your custom one (less portable).
	*/
	class ITheme
	{
	public :

		virtual ~ITheme() {}

		std::string getName();

		// Default rendering of unknown widgets. Usually for debug.
		virtual void drawDummyWidget(IRenderer & r, const AWidget & w) {};

		//...
	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_THEME_HPP_INCLUDED



