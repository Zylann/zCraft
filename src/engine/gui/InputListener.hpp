/*
IInputListener.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_IINPUTLISTENER_HPP_INCLUDED
#define ZENGUI_IINPUTLISTENER_HPP_INCLUDED

#include "Input.hpp"

namespace zn
{
namespace ui
{
	/*
		Every GUI element that respond to input implement this interface.
		Note : this is not a "pure design" interface (see processInput())
	*/
	class IInputListener
	{
	public :

		IInputListener() {}
		virtual ~IInputListener() {}

		// Dispatches the given event to appropriate methods.
		// Note : this method shouldn't be overrided except for general purpose.
		// Note 2 : and yes, this is not a pure interface.
		// 			I made this method to clarify the code and avoid copy-paste.
		virtual bool processInput(const InputEvent & e);

		// Note : all methods below return a boolean indicating if
		// the input has been consumed (true) or not (false).
		// Consumed means that the GUI intercepted the input and it shouldn't be
		// forwarded to the game/app.

	protected :

		/* Mouse */

		// Positions must be relative to the listener.
		virtual bool mouseMoved(int oldX, int oldY, int newX, int newY) = 0;

		virtual bool mousePressed(Mouse::Button button) = 0;
		virtual bool mouseReleased(Mouse::Button button) = 0;
		virtual bool mouseWheelMoved(int delta) = 0;

		/* Keyboard */

		virtual bool keyPressed(Keyboard::Key key) = 0;
		virtual bool keyReleased(Keyboard::Key key) = 0;
		virtual bool textEntered(unsigned int unicode) = 0;

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_IINPUTLISTENER_HPP_INCLUDED
