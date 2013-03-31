#include <cstdio>
#include <iostream>
#include "Game.hpp"

namespace zn
{
	int runGame(IGame * game)
	{
		int code = 0;

		try
		{
			game->start();
			delete game;
		}
		catch(std::exception & e)
		{
			std::cout << "GAME EXCEPTION: " << e.what() << std::endl;
			std::cout << "Please inform the development team to help fix the problem." << std::endl;
			std::cout << "The game will exit. Press any key...";
			getchar();

			if(game != nullptr)
				delete game;
			code = -1;
		}

		return code;
	}

}
