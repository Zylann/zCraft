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

////////////////////////////////////////////////////////////////////////////////

Estimated total dev time
- Marc Gilleron : 82h

////////////////////////////////////////////////////////////////////////////////

Coding style

Class names :
	CamelCase, first letter upper case.
	Interfaces are prefixed by I, abstract classes are prefixed by A.

function and variable names :
	camelCase, first letter lower case

member variables :
	prefixed by m_ if the class owns their memory allocation,
	prefixed by r_ if they are treated as references. For example, a wheel
	keeping a pointer on the car may use r_parent as member variable,
	but shouldn't do a delete on it.
	prefix variables by _ should be allowed, then the r_ semantic
	would be changed to a "Ref" suffix.

file policy :
	Extensions are hpp and cpp.
	1 class per file, except for internal uses or convenience.
	each file has the name of the class, without the A or I prefix.
	if there is no classes in the file, its name must be lower case.
	folders are allowed as separated packages or sub-packages.
	Don't forget to include the namespace in header guards.
	TEMPORARY:
		do not use the same CPP file name twice,
		because qmake doesn't likes this. Two HPPs is Ok.

Margin :
	set to 80 characters.
	Strip the code on several lines if it overlaps to much.

Indentation : tabs

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




