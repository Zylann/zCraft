/*
Root.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_ROOT_HPP_INCLUDED
#define ZENGUI_ROOT_HPP_INCLUDED

#include <unordered_map>

#include "Composite.hpp"
#include "Renderer.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief This is the main GUI object, the root of widgets arborescence.
	 * It should only be created once.
	 * It is both a widget and a global manager (it holds the renderer and
	 * gui-scoppe global variables/methods).
	 * Root can be accessed from any widget by using getRoot(), assuming that
	 * they are part of the same tree.
	 * @note it could be a singleton, but I don't want it to be accessible
	 * from Everywhere, and it's a safer way of handling objects.
	 */
	class Root : public AComposite
	{
	private :

		IRenderer * m_renderer = nullptr;
		std::unordered_map<std::string,ISkin*> m_skins; // Installed skins {name, skin}
		AWidget * r_focusedWidget;

		//IAudioDriver * m_audio; // Not supported yet

	public :

		/**
		 * @brief Creates the GUI with the given screen size.
		 * @param width : in pixels
		 * @param height : in pixels
		 */
		Root(unsigned int width, unsigned int height);

		/**
		 * @brief Destroys the GUI and its content (skins, renderer and widgets)
		 */
		virtual ~Root();

		WidgetType getType() const override { return ROOT; }

		/**
		 * @brief Returns the root element itself.
		 * This override is needed for the children to access Root,
		 * whithout having to keep a reference attribute.
		 * @return root element
		 */
		Root * getRoot() override { return this; }

		/**
		 * @brief Setup the renderer of the GUI. May be called once.
		 * You don't need to manage or delete the renderer after.
		 * @param r : renderer, usually new MyRenderer(args...)
		 */
		void setRenderer(IRenderer * r);

		/**
		 * @brief Stores and loads a C++classCoded skin.
		 * You don't need to manage, load, unload or delete the skin yourself after.
		 * A call to setSkin(name|ref) is required for a skin to take effect.
		 * @param newSkin : the skin to install (usually new MySkin(params))
		 * @return true if successfully installed, false if not.
		 */
		bool installSkin(ISkin * newSkin);

		/**
		 * @brief Activates an installed skin.
		 * @param name : name of the skin.
		 * @param recursive : applies the skin to the whole GUI, not only to Root.
		 * True by default.
		 */
		void setSkin(const std::string & name, bool recursive = true);

		/**
		 * @brief sets the current focused widget.
		 * @param w : a focused widget (w.isFocused() == true)
		 * @note this is for internal use, you shouldn't have to call it.
		 */
		void setFocusedWidget(AWidget * w);

		/**
		 * @brief Get the widget currently having the focus.
		 * @return a focused widget, or nullptr if nothing has the focus
		 */
		AWidget * getFocusedWidget() const;

		/**
		 * @brief Renders the whole GUI using the current renderer.
		 * It does nothing if no renderer has been set.
		 * @note it does the same as the inherited render(renderer),
		 * but you may only use the one without parameters.
		 */
		void render();

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_ROOT_HPP_INCLUDED


