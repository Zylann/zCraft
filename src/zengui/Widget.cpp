/*
Widget.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Widget.hpp"
#include "Container.hpp"
#include "Root.hpp"
#include "Theme.hpp"

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

	void AWidget::setParent(AContainer * w)
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

	void AWidget::setMinSize(const Vector2i & minSize)
	{
		m_minSize = minSize;
		if(m_minSize.x < 0)
			m_minSize.x = 0;
		if(m_minSize.y < 0)
			m_minSize.y = 0;
	}

	void AWidget::setMaxSize(const Vector2i & maxSize)
	{
		m_maxSize = maxSize;
		if(m_maxSize.x < 0)
			m_maxSize.x = 0;
		if(m_maxSize.y < 0)
			m_maxSize.y = 0;
	}

	void AWidget::setTheme(ITheme & theme, bool recursive)
	{
		r_theme = &theme;
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
		if(r_theme != nullptr)
		{
			r_theme->drawDummyWidget(r, *this);
		}
	}

	void AWidget::requestFocus()
	{
		if(r_parent != nullptr)
		{
			r_parent->focusChild(this);
		}
		else
			setFocused(true);
	}

	/*
		Input
	*/

	// TODO Widget: use m_blocksInput

	bool AWidget::mouseMoved(int oldX, int oldY, int newX, int newY)
	{
		if(m_hovered)
		{
			if(!m_bounds.contains(newX, newY))
			{
				m_hovered = false;
				onMouseQuit();
			}
		}
		else
		{
			if(m_bounds.contains(newX, newY))
			{
				m_hovered = true;
				onMouseEnter();
			}
		}

		return false;
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




