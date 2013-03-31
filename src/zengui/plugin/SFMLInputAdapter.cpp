/*
SFMLInputAdapter.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "SFMLInputAdapter.hpp"

namespace zn
{
namespace ui
{
	bool SFMLInputAdapter::forward(const sf::Event & e, Root & root)
	{
		switch(e.type)
		{
		case sf::Event::KeyPressed :
			m_event.type = InputEvent::KEY_PRESSED;
			m_event.keyCode = convertKeyCode(e.key.code);
			break;

		case sf::Event::KeyReleased :
			m_event.type = InputEvent::KEY_RELEASED;
			m_event.keyCode = convertKeyCode(e.key.code);
			break;

		case sf::Event::MouseMoved :
			m_event.type = InputEvent::MOUSE_MOVED;
			m_event.mouseLastPos = m_event.mousePos;
			m_event.mousePos.x = e.mouseMove.x;
			m_event.mousePos.y = e.mouseMove.y;
			break;

		case sf::Event::MouseButtonPressed :
			m_event.type = InputEvent::MOUSE_PRESSED;
			m_event.mouseButton = convertMouseButton(e.mouseButton.button);
			break;

		case sf::Event::MouseButtonReleased :
			m_event.type = InputEvent::MOUSE_RELEASED;
			m_event.mouseButton = convertMouseButton(e.mouseButton.button);
			break;

		case sf::Event::MouseWheelMoved :
			m_event.type = InputEvent::MOUSE_WHEEL_MOVED;
			m_event.mouseWheelDelta = e.mouseWheel.delta;
			break;

		default :
			return false;
		}

		return root.processInput(m_event);
	}

	Keyboard::Key SFMLInputAdapter::convertKeyCode(sf::Keyboard::Key code) const
	{
		switch(code)
		{
		case sf::Keyboard::Key::A :			return Keyboard::Key::A;
		case sf::Keyboard::Key::B :			return Keyboard::Key::B;
		case sf::Keyboard::Key::C :			return Keyboard::Key::C;
		case sf::Keyboard::Key::D :			return Keyboard::Key::D;
		case sf::Keyboard::Key::E :			return Keyboard::Key::E;
		case sf::Keyboard::Key::F :			return Keyboard::Key::F;
		case sf::Keyboard::Key::G :			return Keyboard::Key::G;
		case sf::Keyboard::Key::H :			return Keyboard::Key::H;
		case sf::Keyboard::Key::I :			return Keyboard::Key::I;
		case sf::Keyboard::Key::J :			return Keyboard::Key::J;
		case sf::Keyboard::Key::K :			return Keyboard::Key::K;
		case sf::Keyboard::Key::L :			return Keyboard::Key::L;
		case sf::Keyboard::Key::M :			return Keyboard::Key::M;
		case sf::Keyboard::Key::N :			return Keyboard::Key::N;
		case sf::Keyboard::Key::O :			return Keyboard::Key::O;
		case sf::Keyboard::Key::P :			return Keyboard::Key::P;
		case sf::Keyboard::Key::Q :			return Keyboard::Key::Q;
		case sf::Keyboard::Key::R :			return Keyboard::Key::R;
		case sf::Keyboard::Key::S :			return Keyboard::Key::S;
		case sf::Keyboard::Key::T :			return Keyboard::Key::T;
		case sf::Keyboard::Key::U :			return Keyboard::Key::U;
		case sf::Keyboard::Key::V :			return Keyboard::Key::V;
		case sf::Keyboard::Key::W :			return Keyboard::Key::W;
		case sf::Keyboard::Key::X :			return Keyboard::Key::X;
		case sf::Keyboard::Key::Y :			return Keyboard::Key::Y;
		case sf::Keyboard::Key::Z :			return Keyboard::Key::Z;

		case sf::Keyboard::Key::Add : 		return Keyboard::Key::ADD;
		case sf::Keyboard::Key::BackSlash : return Keyboard::Key::BACKSLASH;
		case sf::Keyboard::Key::BackSpace :	return Keyboard::Key::BACK;
		case sf::Keyboard::Key::Comma : 	return Keyboard::Key::COMMA;
		case sf::Keyboard::Key::Dash :		return Keyboard::Key::DASH;
		case sf::Keyboard::Key::Delete :	return Keyboard::Key::DELETE;
		case sf::Keyboard::Key::Divide :	return Keyboard::Key::DIVIDE;
		case sf::Keyboard::Key::Down :		return Keyboard::Key::DOWN;
		case sf::Keyboard::Key::End :		return Keyboard::Key::END;
		case sf::Keyboard::Key::Equal :		return Keyboard::Key::EQUAL;
		case sf::Keyboard::Key::Escape :	return Keyboard::Key::ESCAPE;
		case sf::Keyboard::Key::Home :		return Keyboard::Key::HOME;
		case sf::Keyboard::Key::Insert :	return Keyboard::Key::INSERT;
		case sf::Keyboard::Key::LAlt :		return Keyboard::Key::LALT;
		case sf::Keyboard::Key::LBracket :	return Keyboard::Key::LBRACKET;
		case sf::Keyboard::Key::LControl :	return Keyboard::Key::LCONTROL;
		case sf::Keyboard::Key::LShift :	return Keyboard::Key::LSHIFT;
		case sf::Keyboard::Key::LSystem :	return Keyboard::Key::LSYSTEM;
		case sf::Keyboard::Key::Left :		return Keyboard::Key::LEFT;
		case sf::Keyboard::Key::Menu :		return Keyboard::Key::MENU;
		case sf::Keyboard::Key::Multiply :	return Keyboard::Key::MULTIPLY;
		case sf::Keyboard::Key::PageDown :	return Keyboard::Key::PAGEDOWN;
		case sf::Keyboard::Key::PageUp :	return Keyboard::Key::PAGEUP;
		case sf::Keyboard::Key::Pause : 	return Keyboard::Key::PAUSE;
		case sf::Keyboard::Key::Period :	return Keyboard::Key::PERIOD;
		case sf::Keyboard::Key::Quote :		return Keyboard::Key::QUOTE;
		case sf::Keyboard::Key::RAlt : 		return Keyboard::Key::RALT;
		case sf::Keyboard::Key::RBracket :	return Keyboard::Key::RBRACKET;
		case sf::Keyboard::Key::RControl :	return Keyboard::Key::RCONTROL;
		case sf::Keyboard::Key::RShift : 	return Keyboard::Key::RSHIFT;
		case sf::Keyboard::Key::RSystem :	return Keyboard::Key::RSYSTEM;
		case sf::Keyboard::Key::Return :	return Keyboard::Key::RETURN;
		case sf::Keyboard::Key::Right :		return Keyboard::Key::RIGHT;
		case sf::Keyboard::Key::SemiColon :	return Keyboard::Key::SEMICOLON;
		case sf::Keyboard::Key::Slash :		return Keyboard::Key::SLASH;
		case sf::Keyboard::Key::Space :		return Keyboard::Key::SPACE;
		case sf::Keyboard::Key::Subtract :	return Keyboard::Key::SUBTRACT;
		case sf::Keyboard::Key::Tab :		return Keyboard::Key::TAB;
		case sf::Keyboard::Key::Tilde :		return Keyboard::Key::TILDE;
//		case sf::Keyboard::Key::Unknown :	return Keyboard::Key::UNKNOWN;
		case sf::Keyboard::Key::Up :		return Keyboard::Key::UP;

		case sf::Keyboard::Key::F1 :		return Keyboard::Key::F1;
		case sf::Keyboard::Key::F2 :		return Keyboard::Key::F2;
		case sf::Keyboard::Key::F3 :		return Keyboard::Key::F3;
		case sf::Keyboard::Key::F4 :		return Keyboard::Key::F4;
		case sf::Keyboard::Key::F5 :		return Keyboard::Key::F5;
		case sf::Keyboard::Key::F6 :		return Keyboard::Key::F6;
		case sf::Keyboard::Key::F7 :		return Keyboard::Key::F7;
		case sf::Keyboard::Key::F8 :		return Keyboard::Key::F8;
		case sf::Keyboard::Key::F9 :		return Keyboard::Key::F9;
		case sf::Keyboard::Key::F10 :		return Keyboard::Key::F10;
		case sf::Keyboard::Key::F11 :		return Keyboard::Key::F11;
		case sf::Keyboard::Key::F12 :		return Keyboard::Key::F12;
		case sf::Keyboard::Key::F13 :		return Keyboard::Key::F13;
		case sf::Keyboard::Key::F14 :		return Keyboard::Key::F14;
		case sf::Keyboard::Key::F15 :		return Keyboard::Key::F15;

		case sf::Keyboard::Key::Num0 :		return Keyboard::Key::NUM0;
		case sf::Keyboard::Key::Num1 :		return Keyboard::Key::NUM1;
		case sf::Keyboard::Key::Num2 :		return Keyboard::Key::NUM2;
		case sf::Keyboard::Key::Num3 :		return Keyboard::Key::NUM3;
		case sf::Keyboard::Key::Num4 :		return Keyboard::Key::NUM4;
		case sf::Keyboard::Key::Num5 :		return Keyboard::Key::NUM5;
		case sf::Keyboard::Key::Num6 :		return Keyboard::Key::NUM6;
		case sf::Keyboard::Key::Num7 :		return Keyboard::Key::NUM7;
		case sf::Keyboard::Key::Num8 :		return Keyboard::Key::NUM8;
		case sf::Keyboard::Key::Num9 :		return Keyboard::Key::NUM9;

		case sf::Keyboard::Key::Numpad0 :	return Keyboard::Key::NUMPAD0;
		case sf::Keyboard::Key::Numpad1 :	return Keyboard::Key::NUMPAD1;
		case sf::Keyboard::Key::Numpad2 :	return Keyboard::Key::NUMPAD2;
		case sf::Keyboard::Key::Numpad3 :	return Keyboard::Key::NUMPAD3;
		case sf::Keyboard::Key::Numpad4 :	return Keyboard::Key::NUMPAD4;
		case sf::Keyboard::Key::Numpad5 :	return Keyboard::Key::NUMPAD5;
		case sf::Keyboard::Key::Numpad6 :	return Keyboard::Key::NUMPAD6;
		case sf::Keyboard::Key::Numpad7 :	return Keyboard::Key::NUMPAD7;
		case sf::Keyboard::Key::Numpad8 :	return Keyboard::Key::NUMPAD8;
		case sf::Keyboard::Key::Numpad9 :	return Keyboard::Key::NUMPAD9;

		default : return Keyboard::Key::UNKNOWN;
		}
	}

	Mouse::Button SFMLInputAdapter::convertMouseButton(sf::Mouse::Button btn) const
	{
		switch(btn)
		{
		case sf::Mouse::Button::Left : 		return Mouse::Button::LEFT;
		case sf::Mouse::Button::Middle :	return Mouse::Button::MIDDLE;
		case sf::Mouse::Button::Right :		return Mouse::Button::RIGHT;

		default : return Mouse::Button::LEFT;
		}
	}

} // namespace ui
} // namespace zn



