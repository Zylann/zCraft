/*
SFML2GameContainer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include "SFML2GameContainer.hpp"

namespace zn
{
	SFML2GameContainer::SFML2GameContainer(IGame * game)
		: AGameContainer(game)
	{
	}

	SFML2GameContainer::~SFML2GameContainer()
	{
	}

	void SFML2GameContainer::setVideoMode(VideoSettings videoSettings, std::string title)
	{
		m_videoSettings = videoSettings;

		sf::ContextSettings contextSettings;
		contextSettings.depthBits = 32;
		contextSettings.antialiasingLevel = 0;
		contextSettings.stencilBits = 0;
		contextSettings.minorVersion = m_videoSettings.openGLMinorVersion;
		contextSettings.majorVersion = m_videoSettings.openGLMajorVersion;

		std::cout << "Target OpenGL version : "
			<< contextSettings.majorVersion << "."
			<< contextSettings.minorVersion << std::endl;

		m_window.create(
			sf::VideoMode(m_videoSettings.width, m_videoSettings.height), title,
			sf::Style::Default, contextSettings);
		m_window.setVerticalSyncEnabled(true);
		//m_window.setFramerateLimit(60);
	}

	void SFML2GameContainer::setTitle(const std::string &title)
	{
		m_title = title;
		m_window.setTitle(title);
	}

	const std::string &SFML2GameContainer::getTitle()
	{
		return m_title;
	}

	u32 SFML2GameContainer::getWidth() const
	{
		return m_window.getSize().x;
	}

	u32 SFML2GameContainer::getHeight() const
	{
		return m_window.getSize().y;
	}

	void SFML2GameContainer::setFullscreen(bool /*fullscreen*/)
	{
		std::cout << "ERROR: SFML2GameContainer::setFullscreen: not supported yet" << std::endl;
	}

	bool SFML2GameContainer::isFullscreen() const
	{
		return false;
	}

	void SFML2GameContainer::start()
	{
		if(!m_window.isOpen())
		{
			// If the window is not opened yet, use default video mode
			setVideoMode(m_videoSettings, "SFML Window");
		}

		m_game->start();
	}

} // namespace zn



