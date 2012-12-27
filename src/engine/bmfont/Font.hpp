/*
Font.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_BM_FONT_HPP_INCLUDED
#define ENGINE_BM_FONT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "engine/bmfont/FontSettings.hpp"
#include "engine/bmfont/FontInfo.hpp"

namespace engine
{
namespace bmfont
{
	/*
		This is a simple C++ OpenGL BMFont implementation.
		Requires SFML, glew and C++11 compiler.
		Documentation about BMFont : http://www.angelcode.com/products/bmfont/
		(included in the installer provided on the website)
	*/

	class Font
	{
	private :

		// Spec
		FontSettings m_settings;
		FontInfo m_info;

		sf::Texture * m_textures; // array of textures

	public :

		// Creates an dummy font.
		Font();

		// Destroys the font.
		~Font();

		// Loads the font settings and texture from a FNT file.
		// The FNT file must be in text format.
		// Cannot be called twice.
		bool loadFromFile(const std::string fpath);

		// Draws a text at (x,y) using the font. The invertYAxis parameter is
		// useful when you have a coordinate system where Y axis goes upside.
		void draw(const std::string text, float x, float y, bool invertYAxis = false);

		// Draws a text using the current OpenGL state. The invertYAxis parameter is
		// useful when you have a coordinate system where Y axis goes upside.
		void draw(const std::string text, bool invertYAxis = false);

	private :

		// Loads settings and font info from a .fnt text file.
		bool parse(const std::string fpath);

	};

} // namespace bmfont
} // namespace engine

#endif // ENGINE_BM_FONT_HPP_INCLUDED


