/*
SFML2GameContainer.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_SFML2GAMECONTAINER_HPP
#define ZN_SFML2GAMECONTAINER_HPP

#include <SFML/Window.hpp>
#include "GameContainer.hpp"

namespace zn
{
	class SFML2GameContainer : public AGameContainer
	{
	public:

		SFML2GameContainer(IGame * game);
		virtual ~SFML2GameContainer();

		void setVideoMode(VideoSettings videoSettings, std::string title="") override;

		void setTitle(const std::string & title) override;
		const std::string & getTitle() override;

		u32 getWidth() const override;
		u32 getHeight() const override;

		void setFullscreen(bool fullscreen) override;
		bool isFullscreen() const override;

		void start() override;

	protected:

		sf::Window m_window;
		std::string m_title;

	};

} // namespace zn

#endif // ZN_SFML2GAMECONTAINER_HPP



