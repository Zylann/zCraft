/*
Skin.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_SKIN_HPP_INCLUDED
#define ZENGUI_SKIN_HPP_INCLUDED

#include "Widget.hpp"
#include "Renderer.hpp"

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

		// Get the name of the skin.
		virtual std::string getName() = 0;

		// Loads resources needed by the skin (textures, fonts...).
		virtual bool load(IRenderer & r) = 0;

		// Unloads resources of the skin
		virtual bool unload(IRenderer & r) = 0;

		// Get the default font
		virtual Font & getDefaultFont() = 0;

		/*
			Methods below are used to draw widgets.
		*/

		virtual void drawPanel(IRenderer & r, const AWidget & panel) = 0;

		/*
			Facultative methods
		*/

		// Default rendering of unknown widgets. Usually for debug.
		virtual void drawDummyWidget(IRenderer & r, const AWidget & w) {}

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_SKIN_HPP_INCLUDED



