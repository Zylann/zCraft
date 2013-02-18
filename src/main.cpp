/*
main.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

/*
zCraft project dependencies :
- C++0x (gcc 4.7.2 +)
- sfml 2.0
- opengl 2.0
- glu
- glew

Note : the engine/ folder is independent from zcraft.

Estimated total dev time
- Marc Gilleron : 65h

*/

#include <iostream>
#include <cstdio>
#include "zcraft/games/FlatMapViewer.hpp"
#include "zcraft/games/PerspectiveMapViewer.hpp"
#include "zcraft/cartographer/Cartographer.hpp"

//#include "experimental/tween/TweenTest.hpp"
#include "experimental/opengl33/game.hpp"

// TODO engine: rename namespace to 'zn' (for zENG)
using namespace engine;

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

		if(game != 0)
			delete game;
		code = -1;
	}

	return code;
}

int launchFlatMapViewer()
{
	return runGame(new zcraft::FlatMapViewer(800, 600));
}

int launchPerspectiveMapViewer()
{
	return runGame(new zcraft::PerspectiveMapViewer(800, 600));
}

int shell(int argc, char * argv[])
{
	if(argc < 2)
	{
		std::cout << "No commands." << std::endl;
		return 0;
	}

	std::string args[argc];
	for(int i = 0; i < argc; i++)
		args[i] = argv[i];

	if(args[1] == "-cart") // Cartographer
	{
		std::string worldDir;
		if(argc == 2)
		{
			std::cout << "World dir: ";
			std::cin >> worldDir;
		}
		else if(argc == 3)
			worldDir = args[2];
		else
		{
			std::cout << "Too much arguments." << std::endl;
			return 0;
		}

		if(!worldDir.empty())
		{
			zcraft::Cartographer::renderWorldToFile(worldDir, "world.png");
		}
		else
			std::cout << "Dir name is empty : abort." << std::endl;
	}
	else if(args[1] == "-fmv") // FlatMapViewer
	{
		return launchFlatMapViewer();
	}

	return 0;
}

int main(int argc, char * argv[])
{
	std::cout << "ZCRAFT main begin" << std::endl;
	int code = 0;

	zcraft::init();

	try
	{
		//code = runGame(new experimental::TweenTest());
		//code = experimental::gl::testgl33();

		if(argc <= 1) // Note : the first arg is the execution path
			code = launchPerspectiveMapViewer();
		else
			code = shell(argc, argv);
	}
	catch(std::exception & e)
	{
		std::cout << "MAIN EXCEPTION: " << e.what() << std::endl;
		std::cout << "Please inform the development team to help fix the problem." << std::endl;
		std::cout << "The program will exit. Press any key...";
		code = -1;
		getchar();
	}

	zcraft::free();

	std::cout << "ZCRAFT main end (code=" << code << ")" << std::endl;
	return code;
}




