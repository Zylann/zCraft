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
	/*
		This is the main GUI object, the root of widgets arborescence.
		It should only be created once.

		It is both a widget and a global manager (it holds the renderer and
		gui-scoppe global variables/methods).

		Root can be accessed from any widget by using getRoot(), assuming that
		they are part of the same tree.

		Note: it could be a singleton, but I don't want it to be accessible
		from Everywhere, and it's a safer way of handling objects.
	*/
	class Root : public AComposite
	{
	private :

		IRenderer * m_renderer = nullptr;
		std::unordered_map<std::string,ISkin*> m_skins; // Installed skins {name, skin}

		//IAudioDriver * m_audio; // Not supported yet

	public :

		// Creates the GUI with the given screen size.
		Root(unsigned int width, unsigned int height);

		// Destroys the GUI and its content.
		virtual ~Root();

		// This override is needed for the children to access Root.
		Root * getRoot() override { return this; }

		// Setup the renderer of the GUI, may be called once.
		// You don't need to manage or delete the renderer after.
		void setRenderer(IRenderer * r);

		// Stores and loads a C++classCoded skin.
		// You don't need to manage, load, unload or delete the skin yourself after.
		// A call to setSkin(name|ref) is required for a skin to take effect.
		bool installSkin(ISkin * newSkin);

		// Activates an installed skin.
		void setSkin(const std::string & name, bool recursive = true);

		// Renders the whole GUI using the current renderer.
		// It does nothing if no renderer has been set.
		// Note : it does the same as render(renderer), but you shouldn't use it.
		void render();

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_ROOT_HPP_INCLUDED


