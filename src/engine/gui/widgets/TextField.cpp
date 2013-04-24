#include "TextField.hpp"
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	TextField::TextField() : AComposite()
	{
		r_text = new Text();
		r_text->setWrap(false);
		r_text->setPadding(Padding(4,4,4,4));
		add(r_text);
		m_caretIndex = 0;
		m_caretPosX = 0;
		m_caretNeedUpdate = false;
	}

	TextField::~TextField()
	{
	}

	void TextField::setText(const std::string str)
	{
		r_text->setText(str);

		if(m_caretIndex >= str.size())
		{
			if(str.empty())
				m_caretIndex = 0;
			else
				m_caretIndex = str.size()-1;
			m_caretNeedUpdate = true;
		}
	}

	std::string TextField::getText() const
	{
		return r_text->getText();
	}

	void TextField::renderSelf(IRenderer &r)
	{
		r_skin->drawTextField(r, *this);

		if(m_focused && r_text->getFont() != nullptr)
		{
			if(m_caretNeedUpdate)
				updateCaret();

			int caretHeight = r.getFontLineHeight(*r_text->getFont());
			IntRect bounds = r_text->getInnerBounds();

			static Color caretColor(255,255,255);

			int x = bounds.min.x + m_caretPosX;

			r.setColor(caretColor);
			r.drawLine(x, bounds.min.y,
					   x, bounds.min.y + caretHeight);
		}
	}

	bool TextField::mousePressed(Mouse::Button button)
	{
		return AComposite::mousePressed(button);
	}

	bool TextField::keyPressed(Keyboard::Key key)
	{
		if(AComposite::keyPressed(key) || m_focused)
		{
			if(!r_text->getText().empty())
			{
				if(key == Keyboard::LEFT && m_caretIndex != 0)
				{
					--m_caretIndex;
					m_caretNeedUpdate = true;
				}
				else if(key == Keyboard::RIGHT && m_caretIndex != r_text->getText().size())
				{
					++m_caretIndex;
					m_caretNeedUpdate = true;
				}
				else if(key == Keyboard::END)
				{
					m_caretIndex = r_text->getText().size();
					m_caretNeedUpdate = true;
				}
				else if(key == Keyboard::BACK && m_caretIndex != 0)
				{
					--m_caretIndex;
					std::string str = r_text->getText();
					str.erase(m_caretIndex, 1);
					r_text->setText(str);
					m_caretNeedUpdate = true;
				}
				else if(key == Keyboard::DELETE && m_caretIndex != r_text->getText().size())
				{
					std::string str = r_text->getText();
					str.erase(m_caretIndex, 1);
					r_text->setText(str);
				}
			}

			if(m_caretNeedUpdate)
				updateCaret();

			return true;
		}
		return false;
	}

	bool TextField::textEntered(unsigned int unicode)
	{
		if(AComposite::textEntered(unicode))
		{
			// If not a control char
			// (0x20 == ' ', 0x7f == ESC)
			if(unicode >= 0x20 && unicode != 0x7f)
			{
				//std::cout << "W[" << m_caretIndex << "]";
				//std::cout << '[' << (char)unicode << ']' << std::endl;
				std::string str = r_text->getText();
				str.insert(m_caretIndex, 1, unicode);
				++m_caretIndex;
				r_text->setText(str);
				m_caretNeedUpdate = true;
			}
			return true;
		}
		return false;
	}

	void TextField::updateCaret()
	{
		m_caretPosX = r_text->getCharacterPos(m_caretIndex).x;
		m_caretNeedUpdate = false;
		//std::cout << "updateCaret " << m_caretIndex << ", " << r_text->getText() << " => " << m_caretPosX << std::endl;
	}

} // namespace ui
} // namespace zn




