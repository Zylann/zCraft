/*
Composite.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_COMPOSITE_HPP_INCLUDED
#define ZENGUI_COMPOSITE_HPP_INCLUDED

#include "WidgetList.hpp"

namespace zn
{
namespace ui
{
	class AComposite : public AWidget
	{
	public :

		AComposite() : AWidget() {}

		virtual ~AComposite();

		void setSkin(ISkin & theme, bool recursive = true) override;

		/**
			Widget management
		**/

		/**
		 * @brief Adds a child widget to the composite.
		 * @param child : widget to add.
		 * @return generic pointer to the newly added widget, nullptr if
		 * something got wrong.
		 * @note if you want to get the right widget return type, use the
		 * template add() version. Also, this method is not virtual, and it
		 * may stay as this, because it may be used in constructors.
		 */
		AWidget * add(AWidget * newChild);

		/**
		 * @brief Adds a child widget to the composite (template version).
		 * This version is recommended because the widget you create has directly
		 * an access to the GUI hierarchy (certain tasks require this).
		 * Also note that this method never returns nullptr.
		 * @return pointer to the newly added widget (never nullptr).
		 * @note Widgets added using this method must define a default constructor.
		 */
		template <class T>
		T * add()
		{
			T * child = new T();
			if(add(child))
				return child;
			return nullptr;
		}

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

		virtual void layout(IntRect space) override;

		/**
		 * @brief Reorganizes contained widgets from the size of their container.
		 */
		void layout();

		unsigned int getChildCount() const override { return m_children.size(); }

		/**
			Main loop
		*/

		virtual void render(IRenderer & r) override;
		virtual void animate(float dt) override;

		/**
			Input
		**/

		virtual bool processInput(const InputEvent & e) override;

	protected :

		// Calls render() on each child of the container
		void renderChildren(IRenderer & r);

		// Calls animate() on each child of the container
		void animateChildren(float dt);

		/** Internal **/

		// Checks if the widget is neither null nor the container itself.
		// Outputs and error and returns false if it fails.
		bool checkChild(const AWidget * child, const std::string & from);

		/** Attributes **/

		// List of widgets ordered by reverse adding time.
		// events will be received in this order, but rendered the reverse way,
		// so that last widgets will be drawn first.
		// Widgets are destroyed when the container is deleted.
		WidgetList m_children;

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_COMPOSITE_HPP_INCLUDED
