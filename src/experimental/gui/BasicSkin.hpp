/*
BasicTheme.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXPERIMENTAL_BASICSKIN_HPP_INCLUDED
#define EXPERIMENTAL_BASICSKIN_HPP_INCLUDED

#include "zengui/Skin.hpp"
#include "zengui/Renderer.hpp"

namespace experimental
{
	class BasicSkin : public zn::ui::ISkin
	{
	private :

		zn::ui::Font m_defaultFont;

	public :

		virtual ~BasicSkin() {}

		virtual bool load(zn::ui::IRenderer & r) override;

		virtual bool unload(zn::ui::IRenderer & r) override;

		virtual zn::ui::Font & getDefaultFont() override;

		virtual std::string getName() override { return "Basic"; }

		virtual void drawDummyWidget(zn::ui::IRenderer & r, const zn::ui::AWidget & w) override;

		virtual void drawPanel(zn::ui::IRenderer & r, const zn::ui::AWidget & panel) override;

	};

} // namespace experimental

#endif // EXPERIMENTAL_BASICSKIN_HPP_INCLUDED


