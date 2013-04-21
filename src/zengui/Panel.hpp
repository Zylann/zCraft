/*
Panel.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_PANEL_HPP_INCLUDED
#define ZENGUI_PANEL_HPP_INCLUDED

#include "Composite.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	class Panel : public AComposite
	{
	public :

		Panel() : AComposite() {}
		virtual ~Panel() {}

	protected :

		virtual void renderSelf(IRenderer & r) override
		{
			r_skin->drawPanel(r, *this);
		}

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_PANEL_HPP_INCLUDED
