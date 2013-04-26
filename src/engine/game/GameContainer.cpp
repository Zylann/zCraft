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

