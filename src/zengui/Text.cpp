/*
Text.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Text.hpp"
#include "Renderer.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	Text::Text() : AWidget()
	{
		m_wrap = false;
		r_font = nullptr;
		m_textNeedUpdate = false;
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
			for(unsigned int i = 0; i < m_dispText.size(); ++i)
			{
				const Line & line = m_dispText[i];
				r.setColor(Color(255,255,255));
				r.drawText(line.str, line.bounds.min.x, line.bounds.min.y, 0, line.str.size()-1);
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
			line.bounds = getInnerBounds();
			line.str = m_text;
			m_dispText.push_back(line);
			std::cout << "DEBUG: nowrap" << std::endl;
		}
		else // wrap
		{
			std::cout << "DEBUG: wrap" << std::endl;
			int lineHeight = r.getFontLineHeight(*r_font);
			IntRect innerBounds = getInnerBounds();
			IntRect lineBounds(0,0,0,lineHeight);
			std::string lstr;
			char c;
			bool ret = false;

			for(unsigned int i = 0; i < m_text.size(); ++i)
			{
				c = m_text[i];

				// Carriage return
				ret = isReturn(c);

				lstr += c;

				// Inner bounds overlapping
				// TODO Text: use a more efficient text size test
				if(!ret && r.getTextSize(*r_font, lstr, 0, lstr.size()-1).x >= innerBounds.width())
				{
					// TODO Text: handle tabs size

					int j = findLastWhitespace(lstr);
					if(j < 0)
						j = 0;
					lstr = lstr.substr(0, j+1);
					if(i != 0)
						i -= lstr.size() - j;
					ret = true;
				}

				if(ret)
				{
					lineBounds.max.x = r.getTextSize(*r_font, lstr, 0, lstr.size()-1).x;
					Line line;
					line.str = lstr;
					line.bounds = lineBounds;
					m_dispText.push_back(line);

					lstr.clear();
					lineBounds.offset(0, lineHeight);
				}
			}
		}

		std::cout << "DEBUG: update finished" << std::endl;
		m_textNeedUpdate = false;
	}

} // namespace ui
} // namespace zcraft





