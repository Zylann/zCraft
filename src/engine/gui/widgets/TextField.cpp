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
		}
	}

	std::string TextField::getText() const
	{
		return r_text->getText();
	}

	void TextField::renderSelf(IRenderer &r)
	{
		r_skin->drawTextField(r, *this);
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
				}
				else if(key == Keyboard::RIGHT && m_caretIndex != r_text->getText().size())
				{
					++m_caretIndex;
				}
				else if(key == Keyboard::END)
				{
					m_caretIndex = r_text->getText().size();
				}
				else if(key == Keyboard::BACK && m_caretIndex != 0)
				{
					--m_caretIndex;
					std::string str = r_text->getText();
					str.erase(m_caretIndex, 1);
					r_text->setText(str);
				}
				else if(key == Keyboard::DELETE && m_caretIndex != r_text->getText().size())
				{
					std::string str = r_text->getText();
					str.erase(m_caretIndex, 1);
					r_text->setText(str);
				}
			}

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
				if(r_text->getText().empty() || m_caretIndex != r_text->getText().size()-1)
				{
					std::cout << '[' << (char)unicode << ']' << std::endl;
					std::string str = r_text->getText();
					str.insert(m_caretIndex, 1, unicode);
					++m_caretIndex;
					r_text->setText(str);
				}
			}
			return true;
		}
		return false;
	}

} // namespace ui
} // namespace zn




