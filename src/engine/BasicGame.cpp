#include <iostream>
#include "engine/BasicGame.hpp"

namespace zn
{
	ABasicGame::ABasicGame(
			u32 width, u32 height, const std::string title)
	{
		sf::ContextSettings contextSettings;
		contextSettings.depthBits = 32;
		contextSettings.antialiasingLevel = 0;
		contextSettings.stencilBits = 0;

	#if defined ZN_OPENGL2
		contextSettings.majorVersion = 2;
		contextSettings.minorVersion = 0;
	#elif defined ZN_OPENGL3
		contextSettings.majorVersion = 3;
		contextSettings.minorVersion = 3;
	#endif

		std::cout << "Target OpenGL version : "
			<< contextSettings.majorVersion << "."
			<< contextSettings.minorVersion << std::endl;

		m_window.create(
			sf::VideoMode(width, height), title,
			sf::Style::Default, contextSettings);
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

	#if defined ZN_OPENGL2 //{

		/* Scene */

		glPushMatrix();

		// Configure basic view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		renderScene(delta);

		glPopMatrix();

		/* GUI */

		glPushMatrix();
		// Pixel-match view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Note : Y axis is inverted to start from top to bottom
		gluOrtho2D(0, m_window.getSize().x, m_window.getSize().y, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		renderGUI(delta);
		glPopMatrix();

	//} ZN_OPENGL2
	#elif defined ZN_OPENGL3 // defined

		#error "zn::ABasicGame doesn't supports OpenGL 3"

	#endif
	}

} // namespace zn



