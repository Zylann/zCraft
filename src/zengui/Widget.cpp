/*
Widget.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Widget.hpp"
#include "Composite.hpp"
#include "Root.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	Root * AWidget::getRoot()
	{
		if(r_parent != nullptr)
			return r_parent->getRoot();
		return nullptr; // Should be overrided in Root
	}

	void AWidget::bringToFront()
	{
		if(r_parent != nullptr)
			r_parent->bringChildToFront(this);
	}

	void AWidget::setParent(AComposite * w)
	{
		if(r_parent != nullptr)
		{
			std::cout << "ERROR: AWidget::setParent: "
				<< "parent widget is already set (ID=\""
				<< r_parent->getID() << "\", given ID=\""
				<< w->getID() << "\"" << std::endl;
			return;
		}
		r_parent = w;
	}

	void AWidget::setBounds(IntRect bounds)
	{
		bounds.normalize();
		m_bounds = bounds;
	}

	IntRect AWidget::getOuterBounds() const
	{
		IntRect outerBounds = m_bounds;
		outerBounds.min.x -= m_margin.left;
		outerBounds.min.y -= m_margin.top;
		outerBounds.max.x += m_margin.right;
		outerBounds.max.y += m_margin.bottom;
		return outerBounds;
	}

	IntRect AWidget::getInnerBounds() const
	{
		IntRect innerBounds;
		innerBounds.min.x = m_padding.left;
		innerBounds.min.y = m_padding.top;
		innerBounds.max.x = m_bounds.width() - m_padding.right;
		innerBounds.max.y = m_bounds.height() - m_padding.bottom;
		return innerBounds;
	}

	Vector2i AWidget::getAbsolutePosition() const
	{
		if(r_parent != nullptr)
			return m_bounds.min + r_parent->getAbsolutePosition();
		return m_bounds.min;
	}

	void AWidget::setSizeLimits(const Vector2i & minSize, const Vector2i & maxSize)
	{
		m_sizeLimit.min = minSize;
		m_sizeLimit.max = maxSize;

		if(m_sizeLimit.min.x < 0)
			m_sizeLimit.min.x = 0;
		if(m_sizeLimit.min.y < 0)
			m_sizeLimit.min.y = 0;

		if(m_sizeLimit.max.x < 0)
			m_sizeLimit.max.x = 0;
		if(m_sizeLimit.max.y < 0)
			m_sizeLimit.max.y = 0;

		m_sizeLimit.normalize();
	}

	void AWidget::setSkin(ISkin & skin, bool recursive)
	{
		std::cout << "DEBUG: AWidget: set skin (ID=" << getID() << ')' << std::endl;
		r_skin = &skin;
	}

	void AWidget::show()
	{
		m_visible = true;
	}

	void AWidget::hide()
	{
		m_visible = false;
	}

	void AWidget::render(IRenderer & r)
	{
		if(r_skin != nullptr)
		{
			r_skin->drawDummyWidget(r, *this);
		}
	}

	void AWidget::requestFocus()
	{
		if(r_parent != nullptr)
		{
			r_parent->focusChild(this);
			bringToFront();
		}
		else
			setFocused(true);
	}

	void AWidget::setAlign(Align align)
	{
		m_align = align;
	}

	bool AWidget::applySizeLimit()
	{
		bool changed = false;

		/* Apply size limits */

		if(m_sizeLimit.max.x > 0 && m_sizeLimit.max.y > 0)
		{
			if(m_bounds.width() > m_sizeLimit.max.x)
			{
				m_bounds.max.x = m_bounds.min.x + m_sizeLimit.max.x;
				changed = true;
			}
			if(m_bounds.height() > m_sizeLimit.max.y)
			{
				m_bounds.max.y = m_bounds.min.y + m_sizeLimit.max.y;
				changed = true;
			}
		}

		if(m_bounds.width() < m_sizeLimit.min.x)
		{
			m_bounds.max.x = m_bounds.min.x + m_sizeLimit.min.x;
			changed = true;
		}
		if(m_bounds.height() < m_sizeLimit.min.y)
		{
			m_bounds.max.y = m_bounds.min.y + m_sizeLimit.min.y;
			changed = true;
		}

		return changed;
	}

	void AWidget::setMargin(const Margin & m)
	{
		m_margin = m;
	}

	void AWidget::setPadding(const Padding & p)
	{
		m_padding = p;
	}

	void AWidget::layout()
	{
	}

	void AWidget::setFocused(bool f, bool recursive)
	{
		m_focused = f;
	}

	void AWidget::setHovered(bool h)
	{
		if(m_hovered)
		{
			if(!h)
			{
				m_hovered = false;
				onMouseQuit();
			}
		}
		else
		{
			if(h)
			{
				m_hovered = true;
				onMouseEnter();
			}
		}
	}

	/*
		Input
	*/

	bool AWidget::mouseMoved(int oldX, int oldY, int newX, int newY)
	{
		// Note : AComposite takes care of setting hover flags
		return m_bounds.contains(newX, newY);
	}

	bool AWidget::mousePressed(Mouse::Button button)
	{
		if(m_hovered)
		{
			m_pressed = true;
			requestFocus();
			onPress();
			return true;
		}
		return false;
	}

	bool AWidget::mouseReleased(Mouse::Button button)
	{
		if(m_pressed)
		{
			m_pressed = false;
			onRelease();
			return true;
		}
		return false;
	}

	bool AWidget::mouseWheelMoved(int delta)
	{
		return m_hovered;
	}

	bool AWidget::keyPressed(Keyboard::Key key, int unicode)
	{
		if(key == Keyboard::Key::RETURN && m_focused)
		{
			m_pressed = true;
			onPress();
			return true;
		}
		return false;
	}

	bool AWidget::keyReleased(Keyboard::Key key)
	{
		if(m_pressed)
		{
			m_pressed = false;
			onRelease();
			return true;
		}
		return false;
	}

} // namespace ui
} // namespace zn




