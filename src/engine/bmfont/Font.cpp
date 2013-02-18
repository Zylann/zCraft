/*
Font.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "engine/opengl/opengl.hpp"
#include "engine/config.hpp"
#include "engine/bmfont/Font.hpp"
#include "engine/stringutils.hpp" // for cropStr()

namespace zn
{
namespace bmfont
{
	// TODO Font: handle accentued characters

	Font::Font()
	{
		m_textures = nullptr;
	}

	Font::~Font()
	{
		if(m_textures != nullptr)
			delete[] m_textures;
	}

	bool Font::loadFromFile(const std::string fpath)
	{
		if(m_textures != nullptr)
		{
			std::cout << "WARNING: Font::loadFromFile(): "
				<< "called twice. Second call is ignored." << std::endl;
			return false;
		}

		// Parse .fnt file

		std::cout << "Font: parsing \"" << fpath << "\"..." << std::endl;
		if(!parse(fpath))
			return false;

		// Load resources

		std::cout << "Font: loading textures..." << std::endl;

		int dirCharPos = fpath.find_last_of("/\\");
		std::string dir = fpath.substr(0, dirCharPos + 1);

		m_textures = new sf::Texture[m_settings.pages.size()];

		for(unsigned int i = 0; i < m_settings.pages.size(); i++)
		{
			const std::string texPath = dir + m_settings.pages[i];
			if(!m_textures[i].loadFromFile(texPath))
			{
				std::cout << "ERROR: Font::loadFromFile(): "
					<< "Couldn't load texture file \"" << texPath << "\"" << std::endl;
				return false;
			}
		}

		return true;
	}

	bool Font::parse(const std::string fpath)
	{
		std::ifstream ifs(fpath);
		if(!ifs.good())
		{
			std::cout << "ERROR: Font::loadFromFile: "
				<< "couldn't open file \"" << fpath << "\"" << std::endl;
			return false;
		}

		// Note : the '>>' operator is formatting, so we use short typed values
		// to be sure that they will be read as integers

		while(!ifs.eof())
		{
			unsigned int i = 0;
			std::stringstream lineStream;
			std::string tag, pair, key, value;
			std::string line;

			std::getline(ifs, line);
			lineStream << line;
			lineStream >> tag;

			//std::cout << lineStream.str() << std::endl;

			if(tag == "info")
			{
				// Not implemented yet
				lineStream.str("");
			}
			else if(tag == "common")
			{
				while(!lineStream.eof())
				{
					lineStream >> pair;
					i = pair.find('=');
					key = pair.substr(0, i);
					value = pair.substr(i + 1);
					std::stringstream converter;
					converter << value;

					if(key == "lineHeight")
						converter >> m_settings.lineHeight;
					else if(key == "base")
						converter >> m_settings.base;
					else if(key == "scaleW")
						converter >> m_settings.scaleW;
					else if(key == "scaleH")
						converter >> m_settings.scaleH;
					else if(key == "packed")
						converter >> m_settings.packed;
					else if(key == "alphaChnl")
						converter >> m_settings.alphaChnl;
					else if(key == "redChnl")
						converter >> m_settings.redChnl;
					else if(key == "greenChnl")
						converter >> m_settings.greenChnl;
					else if(key == "blueChnl")
						converter >> m_settings.blueChnl;
					/*else if(key == "pages") // pages are automatically counted
						converter >> ?*/
				}
			}
			else if(tag == "page")
			{
				unsigned short id = 0;
				while(!lineStream.eof())
				{
					lineStream >> pair;
					i = pair.find('=');
					key = pair.substr(0, i);
					value = pair.substr(i + 1);
					std::stringstream converter;
					converter << value;

					if(key == "id")
					{
						converter >> id;
						if(id >= m_settings.pages.size())
							m_settings.pages.resize(id + 1);
					}
					else if(key == "file")
					{
						// Remove quotes
						const std::string filename = cropStr(value, '"');
						m_settings.pages[id] = filename;
					}
				}
			}
			else if(tag == "char")
			{
				CharDescriptor cd;
				// Note : char count is ignored because not needed
				while(!lineStream.eof())
				{
					lineStream >> pair;
					i = pair.find('=');
					key = pair.substr(0, i);
					value = pair.substr(i + 1);
					std::stringstream converter;
					converter << value;

					if(key == "id")
						converter >> cd.id;
					else if(key == "x")
						converter >> cd.x;
					else if(key == "y")
						converter >> cd.y;
					else if(key == "width")
						converter >> cd.width;
					else if(key == "height")
						converter >> cd.height;
					else if(key == "xoffset")
						converter >> cd.xoffset;
					else if(key == "yoffset")
						converter >> cd.yoffset;
					else if(key == "xadvance")
						converter >> cd.xadvance;
					else if(key == "page")
						converter >> cd.page;
					else if(key == "chnl")
						converter >> cd.chnl;
				}

				m_settings.addChar(cd);
			}
			else if(tag == "kerning")
			{
				Kerning k;
				// Note : Kerning count is ignored because not needed
				while(!lineStream.eof())
				{
					lineStream >> pair;
					i = pair.find('=');
					key = pair.substr(0, i);
					value = pair.substr(i + 1);
					std::stringstream converter;
					converter << value;

					if(key == "first")
						converter >> k.first;
					else if(key == "second")
						converter >> k.second;
					else if(key == "amount")
						converter >> k.amount;
				}

				m_settings.addKerning(k);
			}
		}

		return true;
	}

	void Font::draw(const std::string text, bool invertYAxis)
	{
		draw(text, 0, 0, invertYAxis);
	}

	// TODO Font: add kerning support
	// It is parsed but not used

	// TODO Font: optimize rendering

	void Font::draw(const std::string text, float x0, float y0, bool invertYAxis)
	{
		unsigned int originX = x0, originY = y0; // Cursor position
		unsigned int x, y; // Shifted position
		float tx, ty, tw, th; // Texture sub-rect coordinates
		char c; // Current read character

	#if defined ZN_OPENGL2
		glEnable(GL_TEXTURE_2D);
	#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for(unsigned int i = 0; i < text.size(); i++)
		{
			c = text[i];

			// Line endings
			if(c == '\n')
			{
				originY += m_settings.lineHeight;
				originX = x0;
				continue;
			}
			else if(c == '\r')
			{
				continue;
			}

			// Get character descriptor
			const CharDescriptor * cd = m_settings.getChar(c);
			if(cd == nullptr)
			{
				//std::cout << "E" << (int)c;
				break;
			}

			// Use the glyph atlas texture
			const sf::Texture & tex = m_textures[cd->page];

			// Get glyph texture sub-rect
			const sf::Vector2u ts = tex.getSize();
			tx = static_cast<float>(cd->x) / static_cast<float>(ts.x);
			ty = static_cast<float>(cd->y) / static_cast<float>(ts.y);
			tw = static_cast<float>(cd->width) / static_cast<float>(ts.x);
			th = static_cast<float>(cd->height) / static_cast<float>(ts.y);

			// Get drawing coordinates
			x = originX + cd->xoffset;
			y = originY + cd->yoffset;

			// Draw glyph

			tex.bind();
			gl::drawTexturedRect(
				x, y, cd->width, cd->height,
				tx, ty, tw, th);

//			glBegin(GL_QUADS);
//
//			glTexCoord2f(tx, ty);
//			glVertex2i(x, y);
//
//			glTexCoord2f(tx + tw, ty);
//			glVertex2i(x + cd->width, y);
//
//			glTexCoord2f(tx + tw, ty + th);
//			glVertex2i(x + cd->width, y + cd->height);
//
//			glTexCoord2f(tx, ty + th);
//			glVertex2i(x, y + cd->height);
//
//			glEnd();

			// Advance cursor
			originX += cd->xadvance;

			// DEBUG
			// This code draws glyph rectangles
			/*
			glDisable(GL_TEXTURE_2D);

			glColor4f(1,1,0,1);
			glBegin(GL_LINE_LOOP);
			glVertex2i(originX, originY);
			glVertex2i(originX + cd->width, originY);
			glVertex2i(originX + cd->width, originY + cd->height);
			glVertex2i(originX, originY + cd->height);
			glEnd();

			glColor4f(0,1,1,1);
			glBegin(GL_LINE_LOOP);
			glVertex2i(x, y);
			glVertex2i(x + cd->width, y);
			glVertex2i(x + cd->width, y + cd->height);
			glVertex2i(x, y + cd->height);
			glEnd();

			glColor4f(1,1,1,1);
			glEnable(GL_TEXTURE_2D);
			*/
		}
	}

} // namespace bmfont
} // namespace zn







