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
	/**
	 * @brief A skin is a kind of widget renderer.
	 * It can either use the generic GUI renderer (more portable)
	 * or use your custom one (not recommended).
	 */
	class ISkin
	{
	public :

		virtual ~ISkin() {}

		/**
		 * @brief Get the name of the skin. It will be used by the GUI to be
		 * differenciated from others.
		 * @return
		 */
		virtual std::string getName() = 0;

		/**
		 * @brief Loads resources needed by the skin (textures, fonts...).
		 * @param r : the renderer is provided for calls to loadXXX
		 * @return true if success, false if something got wrong
		 */
		virtual bool load(IRenderer & r) = 0;

		/**
		 * @brief Unloads resources of the skin.
		 * @param r : the renderer is provided for calls to freeXXX
		 * @return true if success, false if something got wrong
		 */
		virtual bool unload(IRenderer & r) = 0;

		/**
		 * @brief Get the default font of this skin. It will be used as a fallback
		 * for all textual elements. You can't display any text if this one is not
		 * provided.
		 * @return the font descriptor (see Renderer.hpp to know what it means)
		 */
		virtual Font & getDefaultFont() = 0;

		/**
			Methods below are used to draw widgets.
			Each time the GUI generic renderer is provided, and a read-only
			reference to the widget to draw.
			Some methods are optionnal.
		**/

		virtual void drawPanel(IRenderer & r, const AWidget & panel) = 0;
		virtual void drawPushButton(IRenderer & r, const AWidget & btn) = 0;

		virtual void drawDragZone(IRenderer & /*r*/, const AWidget & /*dragZone*/) {}

		/*
			Optional methods
		*/

		/**
		 * @brief Default rendering of unknown widgets. Usually for debug.
		 */
		virtual void drawDummyWidget(IRenderer & /*r*/, const AWidget & /*w*/) {}

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_SKIN_HPP_INCLUDED



