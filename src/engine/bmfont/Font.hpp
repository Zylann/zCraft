/*
Font.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_BM_FONT_HPP_INCLUDED
#define ZN_BM_FONT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <unordered_map>

#include "engine/core/Vector2.hpp"

/**
	This is a simple C++ OpenGL BMFont implementation.
	Requires SFML (sf::Texture), glew and C++11 compiler.
	Documentation about BMFont : http://www.angelcode.com/products/bmfont/
	(included in the installer provided on the website)
**/

namespace zn
{
namespace bmfont
{
	/**
	 * @brief gather informations about how the font was created
	 */
	struct FontInfo
	{
		struct Padding
		{
			int up = 0;
			int right = 0;
			int down = 0;
			int left = 0;
		};

		struct Spacing
		{
			int horizontal = 0;
			int vertical = 0;
		};

		std::string face; // This is the name of the true type font.
		unsigned int size; // The size of the true type font.
		bool bold; // The font is bold.
		bool italic; // The font is italic.
		std::string charset; // The name of the OEM charset used (when not unicode).
		bool unicode; // Set to 1 if it is the unicode charset.
		unsigned int stretchH; // The font height stretch in percentage. 100% means no stretch.
		bool smooth; // Set to 1 if smoothing was turned on.
		unsigned int aa; // The supersampling level used. 1 means no supersampling was used.
		Padding padding; // The padding for each character (up, right, down, left).
		Spacing spacing; // The spacing for each character (horizontal, vertical).
		unsigned int outline; // The outline thickness for the characters.
	};

	/**
	 * @brief Indicates a specific X offset between two given characters.
	 */
	struct Kerning
	{
		short first = 0; // The first character id.
		short second = 0; // The second character id.

		// How much the x position should be adjusted when drawing the
		// second character immediately following the first.
		short amount = 0;
	};

	/**
	 * @brief Informations about a character and how to draw it
	 */
	struct CharDescriptor
	{
		int id = 0; //	The character id (usually unicode/UTF).

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

	/**
	 * @brief A set of character descriptors, kerning information and some metadata
	 */
	class CharSet
	{
	private :

		std::list<Kerning> m_kernings;
		std::unordered_map<int, CharDescriptor> m_chars; // (unicode/UTF, char)

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

	/**
	 * @brief This class allows to load AngelCode fonts encoded with the BMFont utility,
	 * and to draw them using SFML textures and OpenGL (no SFML/Graphics pipeline).
	 * @warning the only supported format is white text on alpha, with a textual FNT file.
	 */
	class Font
	{
	private :

		CharSet m_chars;
		FontInfo m_info;

		sf::Texture * m_textures; // array of textures

	public :

		// Creates an dummy font.
		Font();

		// Destroys the font.
		~Font();

		// TODO Font: copy constructor and operator=

		// Loads the font settings and texture from a FNT file.
		// The FNT file must be in text format.
		// Cannot be called twice.
		bool loadFromFile(const std::string fpath);

		// Draws a text at (x,y) using the font. The invertYAxis parameter is
		// useful when you have a coordinate system where Y axis goes upside.
		void draw(const std::wstring &text, float x0, float y0, bool invertYAxis = false);

		// Draws a text using the current OpenGL state. The invertYAxis parameter is
		// useful when you have a coordinate system where Y axis goes upside.
		void draw(const std::wstring &text, bool invertYAxis = false);

		// Gets the maximum height of a line written with this font
		int getLineHeight();

		/**
		 * @brief Get size in pixels of a portion of the given text using this font.
		 * The entire text will be measured if no range is given.
		 * @param text : source text
		 * @param begin : begin index of the text to measure.
		 * @param end : end index of the text to measure. If -1 or greater than text size,
		 * it will be clamped to the last index.
		 * @return width and height of the measured text.
		 */
		Vector2i getTextSize(const std::wstring & text, int begin=0, int end=-1);

	private :

		// Loads charset and font info from a .fnt text file.
		bool parse(const std::string fpath);

	};

} // namespace bmfont
} // namespace zn

#endif // ZN_BM_FONT_HPP_INCLUDED


