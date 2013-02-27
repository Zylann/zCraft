/*
BasicTheme.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXPERIMENTAL_BASICTHEME_HPP_INCLUDED
#define EXPERIMENTAL_BASICTHEME_HPP_INCLUDED

#include "zengui/Theme.hpp"

namespace experimental
{
	class BasicTheme : public zn::ui::ITheme
	{
	public :

		virtual ~BasicTheme() {}

		std::string getName();

		virtual void drawDummyWidget(zn::ui::IRenderer & r, const zn::ui::AWidget & w) override;

	};

} // namespace experimental


#endif // EXPERIMENTAL_BASICTHEME_HPP_INCLUDED


