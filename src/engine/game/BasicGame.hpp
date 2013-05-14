/*
BasicGame.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_BASICGAME_HPP_INCLUDED
#define ZN_BASICGAME_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <string>

#include "../opengl/opengl.hpp"
#include "../core/Vector2.hpp"
#include "Game.hpp"

namespace zn
{
	/**
	 * @brief This is a base class for solo or client-side games.
	 */
	class ABasicGame : public IGame
	{
	private :

		bool m_running;

		sf::Clock m_deltaTimer; // Used for frame time

	protected :

		sf::Window m_window;
		sf::Clock m_time; // Used for app time

	public :

		ABasicGame(
			u32 width, u32 height,
			const std::string title = "Untitled game");

		virtual ~ABasicGame();

		void start() override;

		void stop() override;

		void setTitle(const std::string & title);

	protected :

		// Renders all that must be displayed
		void render(const Time & delta) override;

		// Draws the scene
		virtual void renderScene(const Time & delta) = 0;

		// Draws the GUI on a pixel-match rendering configuration (by default)
		virtual void renderGUI(const Time & /*delta*/) {}

		// Called when the game window is resized
		virtual void resized(const Vector2i & /*newSize*/) {}

		// Called each time the game window receives an event
		// (event-based inputs)
		virtual void processEvent(const sf::Event & /*event*/) {}

	};

} // namespace zn

#endif // ZN_BASICGAME_HPP_INCLUDED


