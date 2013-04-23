/*
InputListener.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "InputListener.hpp"

namespace zn
{
namespace ui
{
	bool IInputListener::processInput(const InputEvent & e)
	{
		switch(e.type)
		{
		case InputEvent::MOUSE_MOVED :
			return mouseMoved(
				e.mouseLastPos.x, e.mouseLastPos.y,
				e.mousePos.x, e.mousePos.y);

		case InputEvent::MOUSE_PRESSED :
			return mousePressed(e.mouseButton);

		case InputEvent::MOUSE_RELEASED :
			return mouseReleased(e.mouseButton);

		case InputEvent::MOUSE_WHEEL_MOVED :
			return mouseWheelMoved(e.mouseWheelDelta);

		case InputEvent::KEY_PRESSED :
			return keyPressed(e.keyCode);

		case InputEvent::KEY_RELEASED :
			return keyReleased(e.keyCode);

		case InputEvent::TEXT_ENTERED :
			return textEntered(e.charUnicode);

		default :
			return false;
		}
	}

} // namespace ui
} // namespace zn

