/*
Signal.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_SIGNAL_HPP_INCLUDED
#define ZENGUI_SIGNAL_HPP_INCLUDED

#include <functional>
#include <list>

namespace zn
{
namespace ui
{
	class AWidget;

	/*
		This struct is provided by GUI callbacks.
	*/
	struct SignalArgs
	{
		// The widget that triggered the signal
		AWidget * sender = nullptr;

		SignalArgs(AWidget & pSender)
		{
			sender = &pSender;
		}
	};

	// This is the type of function used for GUI callbacks.
	typedef std::function<void (SignalArgs&)> Slot;

	/*
		This is an implementation of C#-style events using lambdas.
		However, it doesn't supports the per-case -= operator.

		Important : then the handler must exist in a life span equal or
					greater than the event caller.

		// Use, where onClick is an Signal
		MyButton b;
		MyHandler h;
		b.onClick += [&](SignalArgs & args) {
			h.myMethod(...);
			// Any other code...
		};
	*/
	class Signal
	{
	private :

		std::list<Slot> m_slots;

	public :

		// Adds a slot for this signal. The slot is a function (or lambda)
		// that will be called when the signal is triggered.
		void operator+=(Slot slot);

		// TODO ui::Signal: find a wat to implement -= operator

		// Removes all slot from this signal.
		void disconnectAll();

		// Triggers the signal. sender is the widget that semantically triggered it.
		void trigger(SignalArgs & args)
		{
			for(auto it = m_slots.begin(); it != m_slots.end(); it++)
			{
				(*it)(args);
			}
		}

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_SIGNAL_HPP_INCLUDED




