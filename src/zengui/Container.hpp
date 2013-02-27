/*
Container.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_CONTAINER_HPP_INCLUDED
#define ZENGUI_CONTAINER_HPP_INCLUDED

#include "Widget.hpp"

namespace zn
{
namespace ui
{
	class AContainer : public AWidget
	{
	private :

		// List of widgets ordered by reverse adding time.
		// events will be received in this order, but rendered the reverse way,
		// so that last widgets will be drawn first.
		// Widgets are destroyed when the container is deleted.
		std::list<AWidget*> m_children;

	public :

		AContainer() : AWidget() {}

		virtual ~AContainer()
		{
			eraseAll();
		}

		void setTheme(ITheme & theme, bool recursive = true) override;

		/*
			Widget management
		*/

		// Adds a widget to the container.
		// If a layout has been set on it, the indexes will be used to
		// position the widget into the layout.
		// Fails silently if the widget is already in the container.
		virtual void add(AWidget * child);

		// Erases the given widget from the container.
		// If it is not found, it will not be deleted.
		virtual void erase(AWidget * child);

		// Erases all widgets in the container.
		void eraseAll();

		// Tests if a widget is in the container.
		bool contains(const AWidget * child) const;

		// Finds and returns a contained widget from its ID.
		// If two widgets have the same ID, only one of them will be returned.
		// Returns null if not found.
		AWidget * getChildFromID(const std::string & ID);

		// Brings the given widget to front,
		// so it will be displayed before the others.
		void bringChildToFront(AWidget * widget);

		// Focuses a contained widget and unfocuses others.
		// If the given pointer is null, this will unfocus all children.
		void focusChild(const AWidget * widget);

		/*
			Main loop
		*/

		virtual void render(IRenderer & r) override;
		virtual void animate(float dt) override;

		/*
			Input
		*/

		virtual bool processInput(const InputEvent & e) override;

	protected :

		void renderChildren(IRenderer & r);
		void animateChildren(float dt);

	private :

		/*
			Internal
		*/

		// Checks if the widget is neither null nor the container itself.
		// Outputs and error and returns false if it fails.
		bool checkChild(const AWidget * child, const std::string & from);

		// Finds a child in the container and returns its iterator within the list.
		// If the given widget is invalid, it outputs an error and returns end iterator.
		std::list<AWidget*>::iterator getCheckChild(const AWidget * child, const std::string & from);

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_CONTAINER_HPP_INCLUDED
