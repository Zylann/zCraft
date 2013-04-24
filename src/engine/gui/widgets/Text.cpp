/*
Text.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Text.hpp"
#include "../Renderer.hpp"
#include "../Skin.hpp"
#include "../Composite.hpp"
#include "../Root.hpp"

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

	void Text::setText(const std::wstring &text)
	{
		m_sourceText = text;
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

	void Text::renderSelf(IRenderer & r)
	{
		// TODO Text: add caret index and caret rendering

		if(r_font == nullptr)
		{
			r_font = &r_skin->getDefaultFont();
		}

		if(m_textNeedUpdate)
		{
			updateText(&r);
		}

		if(r_font != nullptr)
		{
			r.setFont(*r_font);
			Vector2i off = getGlobalPosition();
			r.setColor(Color(255,255,255));
			for(unsigned int i = 0; i < m_lines.size(); ++i)
			{
				const Line & line = m_lines[i];
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

//		r.drawRect(getBounds(), false); // For debug
	}

	void Text::onSizeChanged()
	{
		m_textNeedUpdate = true;
	}

	inline bool isWhiteSpace(wchar_t c)
	{
		return c==' ' || c=='\t' || c=='\n' || c=='\r';
	}

	inline bool isReturn(wchar_t c)
	{
		return c=='\n' || c=='\r';
	}

	int findLastWhitespace(const std::wstring & str)
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

	void Text::updateText(const IRenderer *renderer)
	{
		if(renderer == nullptr)
		{
			Root * root = getRoot();
			if(root == nullptr)
				return;
			renderer = root->getRenderer();
			if(renderer == nullptr)
				return;
		}

		m_lines.clear();

		if(m_sourceText.empty() || r_font == nullptr)
		{
			m_textNeedUpdate = false;
			return;
		}

		// TODO Text: alignment
		if(!m_wrap)
		{
			// No wrap
			Line line;
			line.bounds = getLocalInnerBounds();
			line.str = m_sourceText;
			m_lines.push_back(line);
		}
		else // wrap
		{
			int lineHeight = renderer->getFontLineHeight(*r_font);
			IntRect innerBounds = getLocalInnerBounds();
			IntRect lineBounds(0,0,0,lineHeight);
			std::wstring lstr;
			char c;
			bool ret = false;

//			std::cout << "---" << std::endl;
			for(unsigned int i = 0; i < m_sourceText.size(); ++i)
			{
				c = m_sourceText[i];

				// Carriage return
				ret = isReturn(c);

				lstr += c;
//				std::cout << "i=" << i << ", [" << lstr << ']';

				// Inner bounds overlapping
				// TODO Text: use a more efficient text size test
				if(!ret && renderer->getTextSize(*r_font, lstr, 0, lstr.size()-1).x >= innerBounds.width())
				{
					// TODO Text: handle tabs size
					// FIXME Text: sometimes letters get misplaced

					if(lstr.size() > 1) // If we can split the chain
					{
						int j = findLastWhitespace(lstr);
						if(j < 0)
						{
							// No space found, split on letters
							//lstr = lstr.substr(lstr.size()-2, 1);
							lstr.pop_back();
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

				if(ret || i == m_sourceText.size()-1) // If new line strip or end of text
				{
					// Push the new/last line
					// FIXME Text: line bounds height seems incorrect
					lineBounds.max.x = renderer->getTextSize(*r_font, lstr, 0, lstr.size()-1).x;
					Line line;
					line.str = lstr;
					line.bounds = lineBounds;
//					std::cout << " nl" << lineBounds << '[' << lstr << ']';
					m_lines.push_back(line);

					lstr.clear();
					lineBounds.offset(0, lineHeight);
				}
//				std::cout << std::endl;
			}
		}

		m_textNeedUpdate = false;
	}

	const std::wstring &Text::getLine(unsigned int index) const
	{
		static const std::wstring dummyString;
		if(m_lines.empty())
			return dummyString;
		return m_lines[index].str;
	}

	Vector2i Text::getCharacterPos(unsigned int col, unsigned int line)
	{
		Vector2i pos;

		// If needed, force text update if possible
		if(m_textNeedUpdate)
			updateText();

		// If no lines in the text or if no text update were possible,
		// return origin position.
		if(m_lines.empty())
		{
			return pos;
		}

		// Get the root to access the current renderer
		Root * root = getRoot();
		if(root == nullptr)
		{
			std::cout << "ERROR: Text::getCharacterPos: "
						 "cannot perform this operation without root access. "
						 "You must add the widget to the hierarchy first." << std::endl;
			return pos;
		}
		// Get renderer for measuring fonts
		const IRenderer * renderer = root->getRenderer();
		if(renderer == nullptr)
		{
			std::cout << "ERROR: Text::getCharacterPos: "
						 "cannot perform this operation without renderer."
						 "you must set a renderer on the GUI root first." << std::endl;
			return pos;
		}
		// A skin must be defined to know which font to work with
		if(r_skin == nullptr)
		{
			std::cout << "ERROR: Text::getCharacterPos: "
						 "cannot perform this operation without a defined skin."
						 "maybe you should add the widget to the hierarchy first,"
						 "or set the skin manually." << std::endl;
			return pos;
		}

		// If no font set, the skin must provide a default one
		if(r_font == nullptr)
		{
			r_font = &r_skin->getDefaultFont();
		}

		// Get Y first from the line index
		pos.y = line * renderer->getFontLineHeight(*r_font);

		// Now get X :
		// If in lines range and not on first column
		if(line < m_lines.size() && col != 0)
		{
			// The X coordinate is the size of the text before the caret
			pos.x = renderer->getTextSize(*r_font, m_lines[line].str, 0, col-1).x;
			return pos;
		}
		else
		{
			// Beginning of the line : X = 0
			return pos;
		}
	}

	Text::Pos Text::getColumnAndLine(int x, int y)
	{
		unsigned int col=0, line;

		for(line = 0; line < m_lines.size(); ++line)
		{
			if(getCharacterPos(col, line).y >= y)
			{
				if(line != 0)
					--line;
				break;
			}
		}

		const std::wstring & str = m_lines[line].str;
		for(col = 0; col < str.size(); ++col)
		{
			if(getCharacterPos(col, line).x >= x)
			{
				if(col != 0)
					--col;
				break;
			}
		}

		return Text::Pos(col, line);
	}


} // namespace ui
} // namespace zcraft





