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
- Marc Gilleron : 78h

////////////////////////////////////////////////////////////////////////////////

Coding style

Class names :
	CamelCase, first letter upper case.
	Interfaces are prefixed by I, abstract classes are prefixed by A.

function and variable names :
	camelCase, first letter lower case

member variables :
	prefixed by m_ if the class owns their memory allocation,
	prefixed by r_ if they are treated as references. For example, a child
	keeping a pointer on its parent may use r_parent as member variable,
	and shouldn't do a delete on it.
	prefix variables by _ should be allowed, then the r_ semantic
	would be changed to a "Ref" suffix.

file policy :
	1 class per file, except for internal uses or convenience.
	each file has the name of the class, without the A or I prefix.
	if there is no classes in the file, its name must be lower case.
	folders are allowed as separated packages or sub-packages.
	TEMPORARY:
		do not use the same file name twice,
		because qmake doesn't likes this.

namespaces :
	must be small (2-4 letters) and lower case for big packages.

Margin :
	set to 80 characters.
	Strip the code on several lines if it overlaps to much.

Brace policy :
	Aligned, indent after.
	Even conditions before single operation should have braces too,
	except for clarity cases.

//////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <cstdio>

//#include "experimental/tween/TweenTest.hpp"
//#include "experimental/opengl33/game.hpp"
#include "experimental/gui/GuiTest.hpp"
//#include "zcraft/zcraft.hpp"

using namespace zn;

int main(int argc, char * argv[])
{
	std::cout << "ZCRAFT main begin" << std::endl;
	int code = 0;

	// TODO remove the "experimental" namespace.
	// experimental things are actually like end-user code that would be
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




