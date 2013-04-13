/*
Text.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Text.hpp"
#include "Renderer.hpp"
#include "Skin.hpp"
#include "Composite.hpp"

namespace zn
{
namespace ui
{
	Text::Text() : AWidget()
	{
		m_wrap = false;
		r_font = nullptr;
		m_textNeedUpdate = false;
		m_blocksInput = false;
	}

	Text::~Text()
	{}

	void Text::setText(const std::string & text)
	{
		m_text = text;
		m_textNeedUpdate = true;
	}

	void Text::setWrap(bool enable)
	{
		if(m_wrap != enable)
		{
			m_wrap = enable;
			m_textNeedUpdate = true;
		}
	}

	void Text::setFont(Font &font)
	{
		r_font = &font;
		m_textNeedUpdate = true;
	}

	void Text::render(IRenderer & r)
	{
		if(r_font == nullptr && r_skin != nullptr)
		{
			r_font = &r_skin->getDefaultFont();
		}

		if(m_textNeedUpdate)
		{
			updateText(r);
		}

		if(r_font != nullptr)
		{
			r.setFont(*r_font);
			Vector2i off = getGlobalPosition();
			for(unsigned int i = 0; i < m_dispText.size(); ++i)
			{
				const Line & line = m_dispText[i];
				r.setColor(Color(255,255,255));
				r.drawText(line.str,
						   line.bounds.min.x + off.x,
						   line.bounds.min.y + off.y, 0,
						   line.str.size()-1);
			}
		}
//		else
//		{
//			// TODO Text: blocky rendering if no font is defined
//		}
	}

	inline bool isWhiteSpace(char c)
	{
		return c==' ' || c=='\t' || c=='\n' || c=='\r';
	}

	inline bool isReturn(char c)
	{
		return c=='\n' || c=='\r';
	}

	int findLastWhitespace(const std::string & str)
	{
		if(str.empty())
			return -1;
		for(int i = str.size()-1; i >= 0; --i)
		{
			if(isWhiteSpace(str[i]))
				return i;
		}
		return -1;
	}

	void Text::updateText(IRenderer &r)
	{
		m_dispText.clear();

		if(m_text.empty() || r_font == nullptr)
		{
			m_textNeedUpdate = false;
			std::cout << "DEBUG: empty text" << std::endl;
			return;
		}

		// TODO Text: alignment
		if(!m_wrap)
		{
			// No wrap
			Line line;
			line.bounds = getLocalInnerBounds();
			line.str = m_text;
			m_dispText.push_back(line);
		}
		else // wrap
		{
			int lineHeight = r.getFontLineHeight(*r_font);
			IntRect innerBounds = getLocalInnerBounds();
			IntRect lineBounds(0,0,0,lineHeight);
			std::string lstr;
			char c;
			bool ret = false;

			// FIXME infinite loop somewhere (probably caused by unimplemented getTextSize())

			for(unsigned int i = 0; i < m_text.size(); ++i)
			{
				c = m_text[i];
				std::cout << "i=" << i << ", c=" << c << ' ';

				// Carriage return
				ret = isReturn(c);

				lstr += c;

				// Inner bounds overlapping
				// TODO Text: use a more efficient text size test
				if(!ret && r.getTextSize(*r_font, lstr, 0, lstr.size()-1).x >= innerBounds.width())
				{
					// TODO Text: handle tabs size
					// FIXME Text: sometimes letters get misplaced

					if(lstr.size() > 1) // If we can split the chain
					{
						int j = findLastWhitespace(lstr);
						if(j < 0)
						{
							// No space found, split on letters
							lstr = lstr.substr(0, 1);
							--i; // Go back 1 character
						}
						else
						{
							// Space found, split on words
							if(i != 0)
							{
								// Go back to the beginning of the limit-crossing word
								i -= lstr.size()-j-1;
							}
							lstr = lstr.substr(0, j); // cut last space-delimited part
						}
					}
					ret = true;
				}

				if(ret || i == m_text.size()-1) // If new line strip or end of text
				{
					// Push the new/last line
					lineBounds.max.x = r.getTextSize(*r_font, lstr, 0, lstr.size()-1).x;
					Line line;
					line.str = lstr;
					line.bounds = lineBounds;
					std::cout << " nl" << lineBounds;
					m_dispText.push_back(line);

					lstr.clear();
					lineBounds.offset(0, lineHeight);
				}
				std::cout << std::endl;
			}
		}

		m_textNeedUpdate = false;
	}

} // namespace ui
} // namespace zcraft





