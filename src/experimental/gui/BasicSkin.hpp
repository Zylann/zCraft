/*
BasicTheme.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXPERIMENTAL_BASICSKIN_HPP_INCLUDED
#define EXPERIMENTAL_BASICSKIN_HPP_INCLUDED

#include "zengui/Skin.hpp"

namespace experimental
{
	class BasicSkin : public zn::ui::ISkin
	{
	public :

		virtual ~BasicSkin() {}

		virtual std::string getName() override;

		virtual void drawDummyWidget(zn::ui::IRenderer & r, const zn::ui::AWidget & w) override;

		virtual void drawPanel(zn::ui::IRenderer & r, const zn::ui::AWidget & panel) override;

	};

} // namespace experimental


#endif // EXPERIMENTAL_BASICSKIN_HPP_INCLUDED


