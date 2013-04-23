/*
SFMLInputAdapter.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_SFMLINPUTADAPTER_HPP_INCLUDED
#define ZENGUI_SFMLINPUTADAPTER_HPP_INCLUDED

#include <SFML/Window.hpp>
#include "../Root.hpp"

namespace zn
{
namespace ui
{
	class SFMLInputAdapter
	{
	private :

		InputEvent m_event;

	public :

		bool forward(const sf::Event & e, Root & root);

		Keyboard::Key convertKeyCode(sf::Keyboard::Key code) const;
		Mouse::Button convertMouseButton(sf::Mouse::Button btn) const;

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_SFMLINPUTADAPTER_HPP_INCLUDED
