/*
GameContainer.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "GameContainer.hpp"

namespace zn
{
	AGameContainer::AGameContainer(IGame * game)
	{
		m_game = game;
	}

	AGameContainer::~AGameContainer()
	{
		if(m_game != nullptr)
			delete m_game;
	}

} // namespace zn

