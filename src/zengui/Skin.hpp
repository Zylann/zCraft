/*
Theme.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_SKIN_HPP_INCLUDED
#define ZENGUI_SKIN_HPP_INCLUDED

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
	class ISkin
	{
	public :

		virtual ~ISkin() {}

		virtual std::string getName() = 0;

		// Default rendering of unknown widgets. Usually for debug.
		virtual void drawDummyWidget(IRenderer & r, const AWidget & w) {}

		virtual void drawPanel(IRenderer & r, const AWidget & panel) = 0;

		//...
	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_SKIN_HPP_INCLUDED


