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
engine/gui/         : engine/core (except for renderers/ and inputs/)
zcraft/ 			: engine/
zcraft/demos/ 		: zcraft/

Estimated total dev time
- Marc Gilleron : 86h

//////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <cstdio>

//#include "experimental/tween/TweenTest.hpp"
//#include "experimental/opengl33/game.hpp"
#include "experimental/gui/GuiTest.hpp"
//#include "zcraft/zcraft.hpp"
#include "engine/utf8.hpp"
#include <fstream>

using namespace zn;

void testUTF8()
{
	std::ifstream ifs("utf8.txt");
	if(!ifs.is_open())
		return;
	std::string line;
	while(std::getline(ifs, line))
	{
		if(!utf8::is_valid(line.begin(), line.end()))
			std::cout << "Invalid line : " << line << std::endl;
		else
		{
			// Print raw
			std::cout << line << std::endl;

			// Convert to UTF16
			std::wstring wline;
			utf8::utf8to16(line.begin(), line.end(), std::back_inserter(wline));
			std::wcout << wline << std::endl;

			for(unsigned int i = 0; i < wline.size(); ++i)
			{
				std::wcout << L"[" << wline[i] << L"] " << (int)wline[i] << std::endl;
			}

			// And back to UTF8
			line.clear();
			utf8::utf16to8(wline.begin(), wline.end(), std::back_inserter(line));
			std::cout << line << std::endl;
		}
	}
	ifs.close();
}

int main(int argc, char * argv[])
{
	std::cout << "ZCRAFT main begin" << std::endl;
	int code = 0;

	std::cout << "Size of wchar_t : " << sizeof(wchar_t) << std::endl;

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




