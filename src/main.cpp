/*
main.cpp
Copyright (C) 2010-2013 Marc GILLERON
This file is part of the zCraft project.
*/

/*//////////////////////////////////////////////////////////////////////////////

lib/compiler dependencies :
- C++11 (tested on gcc 4.7.2)
- sfml 2.0
- opengl 2.0
- glu
- glew

project-scope package dependencies :
Note : this is just an overview.

engine/core 		: config.hpp
engine/opengl 		: engine/core
engine/noise		: engine/core
engine/bmfont		: engine/opengl
engine/game			: engine/opengl
engine/system		: engine/core

zcraft/				: engine/
experimental/		: engine/

////////////////////////////////////////////////////////////////////////////////

Estimated total dev time
- Marc Gilleron : 77h

//////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <cstdio>

//#include "experimental/tween/TweenTest.hpp"
//#include "experimental/opengl33/game.hpp"
#include "experimental/gui/GuiTest.hpp"
#include "zcraft/zcraft.hpp"

using namespace zn;

int main(int argc, char * argv[])
{
	std::cout << "ZCRAFT main begin" << std::endl;
	int code = 0;

	try
	{
//		code = runGame(new experimental::TweenTest());
//		code = experimental::gl::testgl33();
//		code = runGame(new experimental::GuiTest());
		code = zcraft::shell(argc, argv);
	}
	catch(std::exception & e)
	{
		std::cout << "MAIN EXCEPTION: " << e.what() << std::endl;
		std::cout << "Please inform the development team to help fix the problem." << std::endl;
		std::cout << "The program will exit. Press any key...";
		code = -1;
		getchar();
	}

	std::cout << "ZCRAFT main end (code=" << code << ")" << std::endl;
	return code;
}




