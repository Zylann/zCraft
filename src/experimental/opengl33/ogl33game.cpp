/*
game.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>

#include <SFML/Graphics.hpp>
#include "engine/system/Time.hpp"

#include "experimental/opengl33/ogl33game.hpp"
#include "experimental/opengl33/GScene.hpp"
#include "experimental/opengl33/AxesSceneNode.hpp"
#include "engine/opengl/ShaderProgram.hpp"
#include "experimental/opengl33/opengl3.hpp"

using namespace zn;

namespace experimental
{
namespace gl
{
	int testgl33()
	{
		// Configure context
		sf::ContextSettings contextSettings;
		contextSettings.depthBits = 32;
		contextSettings.antialiasingLevel = 0;
		contextSettings.stencilBits = 0;
		// OpenGL 3.3
		contextSettings.majorVersion = 3;
		contextSettings.minorVersion = 3;

		// Create window
		sf::Window window(
			sf::VideoMode(800, 600), "GL33",
			sf::Style::Default, contextSettings);
		window.setVerticalSyncEnabled(true);

		// Initialize OpenGL extensions
		if(!gl::init(true, true))
			return -1;

		// Load testing texture
		sf::Texture texture;
		if(!texture.loadFromFile("assets/textures/test.png"))
			return -1;

		bool running = true;
		sf::Clock time;

		Scene scene;
		//scene.addNode(new AxesSceneNode());

		while(running)
		{
			Time delta(time.restart().asMilliseconds());

			// Poll events
			sf::Event event;
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					running = false;
				}
				else if(event.type == sf::Event::Resized)
				{
					glViewport(0, 0, event.size.width, event.size.height);
				}
				else if(event.type == sf::Event::KeyPressed)
				{
					if(event.key.code == sf::Keyboard::F3)
						std::cout << "FPS: " << 1.f / delta.s() << std::endl;
				}
			}

			// Update game logic
			//...

			// Draw everything

			gl::beginRender();

			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//scene.renderAll();
			gl::drawAxes();

			/*textureShader.bind();
			texture.bind();
			gl::color(255,0,255);
			gl::drawTexturedRect(0,0,1,1,0,0,1,1);
			textureShader.unbind();*/

			gl::endRender();

			// Swap buffers and displays the next frame
			window.display();
		}

		// Free resources
		gl::dispose();

		return 0;
	}

} // namespace gl33
} // namespace experimental

