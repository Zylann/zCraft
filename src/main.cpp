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

Overview of project-scope package dependencies :

engine/core/ 		: engine/config.hpp
engine/ 			: engine/core
zcraft/ 			: engine/
zcraft/demos/ 		: zcraft/
zengui/ 			: engine/core
zengui/plugin/ 		: engine/
experimental/ 		: *

Estimated total dev time
- Marc Gilleron : 85h

//////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <cstdio>

//#include "experimental/tween/TweenTest.hpp"
//#include "experimental/opengl33/game.hpp"
#include "experimental/gui/GuiTest.hpp"
//#include "zcraft/zcraft.hpp"

using namespace zn;

int main(/*int argc, char * argv[]*/)
{
	std::cout << "ZCRAFT main begin" << std::endl;
	int code = 0;

	// TODO remove the "experimental" namespace.
	// experimental things are actually treated as end-user code that would be
	// incorporated in the engine later.

	try
	{
//		code = runGame(new experimental::TweenTest());
//		code = experimental::gl::testgl33();
		code = runGame(new experimental::GuiTest());
//		code = zcraft::shell(argc, argv);
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




