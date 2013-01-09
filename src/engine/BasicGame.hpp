/*
BasicGame.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef BASICGAME_HPP_INCLUDED
#define BASICGAME_HPP_INCLUDED

#include <engine/opengl/glutils.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "engine/Vector2.hpp"
#include "engine/Game.hpp"

namespace engine
{
	class ABasicGame : public IGame
	{
	private :

		bool m_running;

	protected :

		sf::Window m_window;

		sf::Clock m_time;

	public :

		ABasicGame(u32 width, u32 height, const std::string title = "Untitled game");

		virtual ~ABasicGame();

		virtual void start();

		virtual void stop();

	protected :

		// Renders all that must be displayed
		void render(const Time & delta) override;

		// Draws the scene
		virtual void renderScene(const Time & delta) = 0;

		// Draws the GUI on a pixel-match rendering configuration (by default)
		virtual void renderGUI(const Time & delta) {};

		// Called when the game window is resized
		virtual void resized(const Vector2i & newSize) {}

		// Called each time the game window receives an event
		// (event-based inputs)
		virtual void processEvent(const sf::Event & event) {}

	};

} // namespace engine

#endif // BASICGAME_HPP_INCLUDED


