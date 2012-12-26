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

		virtual void preRender();

		virtual void postRender();

		virtual void resized(const Vector2i & newSize) {}

		virtual void processEvent(const sf::Event & event) {}

	};

} // namespace engine

#endif // BASICGAME_HPP_INCLUDED


