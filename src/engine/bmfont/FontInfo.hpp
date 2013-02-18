/*
FontInfo.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef FONTINFO_HPP_INCLUDED
#define FONTINFO_HPP_INCLUDED

namespace zn
{
namespace bmfont
{
	/*
		FontInfo gather informations about how the font was created
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

} // namespace bmfont
} // namespace engin

#endif // FONTINFO_HPP_INCLUDED





