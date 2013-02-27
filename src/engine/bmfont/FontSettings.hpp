/*
FontSettings.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_BM_FONTSETTINGS_HPP_INCLUDED
#define ENGINE_BM_FONTSETTINGS_HPP_INCLUDED

#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include "engine/bmfont/CharDescriptor.hpp"

namespace zn
{
namespace bmfont
{
	/*
		FontSettings is what is used from the specification to draw the font.
	*/

	struct Kerning
	{
		short first = 0; // The first character id.
		short second = 0; // The second character id.

		// How much the x position should be adjusted when drawing the
		// second character immediately following the first.
		short amount = 0;
	};

	struct CharDescriptor
	{
		short id = 0; //	The character id.

		short x = 0; 	//	The left position of the character image in the texture.
		short y = 0;	//	The top position of the character image in the texture.
		short width = 0; //	The width of the character image in the texture.
		short height = 0; //	The height of the character image in the texture.

		//	How much the current position should be offset when copying the
		// image from the texture to the screen.
		short xoffset = 0;
		short yoffset = 0;

		// How much the current position should be advanced
		// after drawing the character.
		short xadvance = 0;

		short page = 0; // The texture page where the character image is found.

		// The texture channel where the character image is found
		// (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).
		short chnl = 15;

	};

	class FontSettings
	{
	private :

		std::list<Kerning> m_kernings;
		std::unordered_map<int, CharDescriptor> m_chars; // (id, char)

	public :

		std::vector<std::string> pages; // [id] = file

		// This is the distance in pixels between each line of text.
		unsigned short lineHeight = 0;

		// The number of pixels from the absolute top of the line to the
		// base of the characters.
		unsigned short base = 0;

		// The size of the texture, normally used to scale the coordinates of
		// the character image.
		unsigned short scaleW = 0;
		unsigned short scaleH = 0;

		// Set to 1 if the monochrome characters have been packed into each of
		// the texture channels. In this case alphaChnl describes what is
		// stored in each channel.
		unsigned short packed = false;

		// For each color :
		// Set to 0 if the channel holds the glyph data, 1 if it holds the
		// outline, 2 if it holds the glyph and the outline, 3 if its set to
		// zero, and 4 if its set to one.
		unsigned short alphaChnl = 0;
		unsigned short redChnl = 4;
		unsigned short greenChnl = 4;
		unsigned short blueChnl = 4;

	public :

		void addKerning(Kerning k);
		short getKerning(int first, int second) const;

		void addChar(CharDescriptor cd);
		const CharDescriptor * getChar(int id) const;

	};

} // namespace bmfont
} // namespace zn

#endif // ENGINE_BM_FONTSETTINGS_HPP_INCLUDED



