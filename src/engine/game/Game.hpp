/*
Game.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_GAME_HPP_INCLUDED
#define ENGINE_GAME_HPP_INCLUDED

#include "engine/system/Time.hpp"

namespace zn
{
	class IGame
	{
	public :

		virtual ~IGame() {}

		/// Starts game's execution.
		/// It may be blocking depending on the implementation.
		virtual void start() = 0;

		/// Tells the game to stop and close cleanly
		virtual void stop() = 0;

	protected :

		/// Initializes the game (loads resources...)
		virtual bool init() = 0;

		/// Updates game logic
		virtual void update(const Time & delta) = 0;

		/// Draws the whole game on the screen
		virtual void render(const Time & delta) = 0;

		/// Frees game resources before closing
		virtual void dispose() = 0;

	};

	// Convenience routine that runs the given game and handles top-level exceptions.
	// Returns -1 if an exception occured, 0 otherwise.
	int runGame(IGame * game);

} // namespace zn

#endif // ENGINE_GAME_HPP_INCLUDED


