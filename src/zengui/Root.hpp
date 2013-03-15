/*
Root.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_ROOT_HPP_INCLUDED
#define ZENGUI_ROOT_HPP_INCLUDED

#include "Container.hpp"
#include "Renderer.hpp"

namespace zn
{
namespace ui
{
	/*
		This is the main GUI object, the root of widgets arborescence.
		It should only be created once.
		Note: it could be a singleton, but I don't want it to be accessible
		from Everywhere...
	*/
	class Root : public AContainer
	{
	private :

		IRenderer * m_renderer = nullptr;
		//IAudioDriver * m_audio; // Not supported yet

	public :

		// Creates the GUI with the given screen size.
		Root(unsigned int width, unsigned int height);

		virtual ~Root();

		Root * getRoot() override { return this; }

		// Sets the renderer of the GUI.
		// If it is already set, the old one is deleted.
		// Once set, the renderer will be automatically deleted when Root
		// is deleted.
		void setRenderer(IRenderer * r);

		// Renders the whole GUI using the current renderer.
		// It does nothing if no renderer has been set.
		// Note : it does the same as render(renderer), but you shouldn't use it.
		void render();

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_ROOT_HPP_INCLUDED


