/*
Slider.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Slider.hpp"
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	Slider::Slider() : AWidget()
	{
		m_ratio = 0;
		m_orientation = HORIZONTAL;
	}

	void Slider::setRatio(float ratio)
	{
		m_ratio = ratio < 0 ? 0 : ratio > 1 ? 1 : ratio;
		onValueChangedSignal(m_ratio);
	}

	void Slider::renderSelf(IRenderer &r)
	{
		r_skin->drawSlider(r, *this);
	}

	bool Slider::mouseMoved(int oldX, int oldY, int newX, int newY)
	{
		bool consumed = AWidget::mouseMoved(oldX, oldY, newX, newY);
		if(m_pressed)
		{
			IntRect bounds = getBounds();

			if(m_orientation == HORIZONTAL)
			{
				if(newX <= bounds.min.x)
					m_ratio = 0;
				else if(newX >= bounds.max.x)
					m_ratio = 1;
				else
				{
					m_ratio = static_cast<float>(newX - bounds.min.x)
							/ static_cast<float>(bounds.width());
				}
			}
			else
			{
				// Note : Y is inverted because UP is seen as a max value for users
				if(newY <= bounds.min.y)
					m_ratio = 1;
				else if(newY >= bounds.max.y)
					m_ratio = 0;
				else
				{
					m_ratio = static_cast<float>(bounds.max.y - newY)
							/ static_cast<float>(bounds.height());
				}
			}

			onValueChangedSignal(m_ratio);
			return true;
		}
		return consumed;
	}

	bool Slider::keyPressed(Keyboard::Key key)
	{
		bool consumed = AWidget::keyPressed(key);

		if(m_focused)
		{
			if(key == Keyboard::ADD ||
			   key == Keyboard::RIGHT ||
			   key == Keyboard::UP)
			{
				m_ratio += 0.1f;
				if(m_ratio > 1)
					m_ratio = 1;
				onValueChangedSignal(m_ratio);
				return true;
			}
			else if(key == Keyboard::SUBTRACT ||
					key == Keyboard::LEFT ||
					key == Keyboard::DOWN)
			{
				m_ratio -= 0.1f;
				if(m_ratio < 0)
					m_ratio = 0;
				onValueChangedSignal(m_ratio);
				return true;
			}
		}

		return consumed;
	}

} // namespace ui
} // namespace zn


