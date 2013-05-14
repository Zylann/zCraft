/*
WidgetList.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_UI_WIDGETLIST_HPP_INCLUDED
#define ZN_UI_WIDGETLIST_HPP_INCLUDED

#include "Widget.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief this is a Widget container used internally by the GUI.
	 * it implements a deferred container-order manipulation :
	 * each operations on it are not directly applied until flush() is called.
	 * This is useful if the structure of the list is modified while iterating on it.
	 * For this, you need to call beginDefer() before a loop,
	 * and endDefer() after the loop.
	 * The list behaves as a normal list outside of these calls.
	 */
	class WidgetList
	{
	public:

		typedef typename std::list<AWidget*>::iterator 					iterator;
		typedef typename std::list<AWidget*>::const_iterator 			const_iterator;
		typedef typename std::list<AWidget*>::reverse_iterator 			reverse_iterator;
		typedef typename std::list<AWidget*>::const_reverse_iterator	const_reverse_iterator;

		WidgetList();

		// Destroys widgets contained in the list.
		~WidgetList();

		void add(AWidget * w);
		void erase(AWidget *w);
		void toFront(AWidget *w);
		void clear();

		// Gets how many elements there is in the list.
		// Elements in deferred list are not counted.
		inline unsigned int size() const { return m_widgets.size(); }

		// Tests if the given widget is contained into the list.
		// In deferred mode, it also checks if it has been added by the add()
		// operation that is not performed yet (but not true for clear/erase).
		bool contains(const AWidget * w) const;

		// Starts deferred block (increments defer counter).
		void beginDefer();

		// Ends a deferred block (decrements defer counter).
		// If the defer counter reaches zero, flush() is called.
		// Does nothing if called more.
		void endDefer();

		inline iterator begin() 						{ return m_widgets.begin(); }
		inline iterator end() 							{ return m_widgets.end(); }

		inline const_iterator cbegin() const 			{ return m_widgets.cbegin(); }
		inline const_iterator cend() const 				{ return m_widgets.cend(); }

		inline reverse_iterator rbegin() 				{ return m_widgets.rbegin(); }
		inline reverse_iterator rend() 					{ return m_widgets.rend(); }

		inline const_reverse_iterator crbegin() const 	{ return m_widgets.crbegin(); }
		inline const_reverse_iterator crend() const 	{ return m_widgets.crend(); }

	private:

		void doAdd(AWidget * w);
		void doErase(AWidget *w);
		void doToFront(AWidget *w);
		void doClear();

		// Applies all previously called operations (also called in endDefer).
		void flush();

		struct Operation
		{
			enum Type
			{
				ADD, ERASE, TO_FRONT, CLEAR
			};

			AWidget * widget = nullptr;
			Type type;

			Operation(AWidget * w, Type t)
				: widget(w), type(t)
			{}
		};

		std::list<AWidget*> m_widgets;
		std::list<Operation> m_operations;
		unsigned int m_deferCount;
	};

} // namespace ui
} // namespace zn

#endif // ZN_UI_WIDGETLIST_HPP_INCLUDED





