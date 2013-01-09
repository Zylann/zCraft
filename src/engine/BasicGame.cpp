#include <iostream>
#include "engine/BasicGame.hpp"

namespace engine
{
	ABasicGame::ABasicGame(u32 width, u32 height, const std::string title)
	{
		m_window.create(
			sf::VideoMode(width, height), title,
			sf::Style::Default, sf::ContextSettings(32));
		m_window.setVerticalSyncEnabled(true);
		//m_window.setFramerateLimit(60);
		m_running = false;
	}

	ABasicGame::~ABasicGame()
	{
	}

	void ABasicGame::stop()
	{
		m_running = false;
	}

	void ABasicGame::start()
	{
		if(!init())
		{
			std::cout << "Failed to initialize the game." << std::endl;
			return;
		}

		m_running = true;
		m_time.restart();

		while(m_running)
		{
			Time delta(m_time.restart().asMilliseconds());

			// Poll events
			sf::Event event;
			while(m_window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					m_running = false;
				}
				else if(event.type == sf::Event::Resized)
				{
					glViewport(0, 0, event.size.width, event.size.height);
					resized(Vector2i(event.size.width, event.size.height));
				}
				else if(event.type == sf::Event::KeyPressed)
				{
					if(event.key.code == sf::Keyboard::F3)
						std::cout << "FPS: " << 1.f / delta.s() << std::endl;
				}

				processEvent(event);
			}

			// Update game logic
			update(delta);

			// Draw everything
			render(delta);

			// Swap buffers and displays the next frame
			glFlush();
			m_window.display();
		}

		// Free resources
		dispose();
	}

	void ABasicGame::render(const Time & delta)
	{
		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Scene */

		// Configure basic view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		renderScene(delta);

		/* GUI */

		// Pixel-match view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Note : Y axis is inverted to start from tom to bottom
		gluOrtho2D(0, m_window.getSize().x, m_window.getSize().y, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		renderGUI(delta);
	}

} // namespace engine



