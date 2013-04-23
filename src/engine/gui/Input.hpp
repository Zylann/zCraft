/*
Input.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_INPUT_HPP_INCLUDED
#define ZENGUI_INPUT_HPP_INCLUDED

#include "Vector2.hpp"

namespace zn
{
namespace ui
{
	namespace Mouse
	{
		enum Button
		{
			LEFT,
			MIDDLE,
			RIGHT
		};
	}

	namespace Keyboard
	{
		// Note : this enum has the same values (same order) as SFML2RC sf::Key.
		enum Key
		{
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
			ESCAPE,
			LCONTROL, LSHIFT, LALT, LSYSTEM,
			RCONTROL, RSHIFT, RALT, RSYSTEM,
			MENU,
			LBRACKET,
			RBRACKET,
			SEMICOLON,
			COMMA,
			PERIOD,
			QUOTE,
			SLASH,
			BACKSLASH,
			TILDE,
			EQUAL,
			DASH,
			SPACE,
			RETURN,
			BACK,
			TAB,
			PAGEUP,
			PAGEDOWN,
			END,
			HOME,
			INSERT,
			DELETE,
			ADD,
			SUBTRACT,
			MULTIPLY,
			DIVIDE,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4,
			NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
			PAUSE,

			KEYCOUNT, // Keep at this position
			UNKNOWN
		};

	} // namespace Keyboard

	struct InputEvent
	{
		enum Type
		{
			MOUSE_MOVED,
			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_WHEEL_MOVED,
			KEY_PRESSED,
			KEY_RELEASED,
			TEXT_ENTERED
		};

		Type type;

		/* Mouse */

		Vector2i mousePos;
		Vector2i mouseLastPos;
		Mouse::Button mouseButton;
		int mouseWheelDelta;

		/* Keyboard */

		Keyboard::Key keyCode;
		unsigned int charUnicode;
	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_INPUT_HPP_INCLUDED



