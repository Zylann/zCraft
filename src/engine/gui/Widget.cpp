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

	void AWidget::bringToFront(bool upwardRecursive)
	{
		if(r_parent != nullptr)
		{
			r_parent->bringChildToFront(this);
			if(upwardRecursive)
				r_parent->bringToFront(true);
		}
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

	IntRect AWidget::getBounds() const
	{
		if(r_parent != nullptr)
			return getLocalBounds().offset(r_parent->getGlobalPosition());
		return m_localBounds;
	}

	IntRect AWidget::getLocalBounds() const
	{
		return m_localBounds;
	}

	void AWidget::setLocalBounds(IntRect bounds)
	{
		bounds.repair();
		bool sizeChanged =
			m_localBounds.width() != bounds.width() ||
			m_localBounds.height() != bounds.height();
		m_localBounds = bounds;
		if(sizeChanged)
			onSizeChanged();
	}

	void AWidget::setBounds(IntRect globalBounds)
	{
		if(r_parent != nullptr)
			globalBounds.offset(-r_parent->getGlobalPosition());
		setLocalBounds(globalBounds);
	}

	IntRect AWidget::getLocalOuterBounds() const
	{
		IntRect outerBounds = m_localBounds;
		outerBounds.min.x -= m_margin.left;
		outerBounds.min.y -= m_margin.top;
		outerBounds.max.x += m_margin.right;
		outerBounds.max.y += m_margin.bottom;
		return outerBounds;
	}

	IntRect AWidget::getOuterBounds() const
	{
		if(r_parent != nullptr)
			return getLocalOuterBounds().offset(r_parent->getGlobalPosition());
		return getLocalOuterBounds();
	}

	IntRect AWidget::getLocalInnerBounds() const
	{
		IntRect innerBounds;
		innerBounds.min.x = m_padding.left;
		innerBounds.min.y = m_padding.top;
		innerBounds.max.x = m_localBounds.width() - m_padding.right;
		innerBounds.max.y = m_localBounds.height() - m_padding.bottom;
		return innerBounds;
	}

	IntRect AWidget::getInnerBounds() const
	{
		if(r_parent != nullptr)
			return getLocalInnerBounds().offset(r_parent->getGlobalPosition());
		return getLocalInnerBounds();
	}

	Vector2i AWidget::getGlobalPosition() const
	{
		if(r_parent != nullptr)
			return m_localBounds.min + r_parent->getGlobalPosition();
		return m_localBounds.min;
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

		m_sizeLimit.repair();
	}

	void AWidget::setSkin(ISkin & skin, bool /*recursive*/)
	{
		//std::cout << "DEBUG: AWidget: set skin (ID=" << getID() << ')' << std::endl;
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
		if(m_visible && r_skin != nullptr)
		{
			renderSelf(r);
		}
	}

	void AWidget::renderSelf(IRenderer &r)
	{
		r_skin->drawDummyWidget(r, *this);
	}

	void AWidget::setAlign(unsigned char align)
	{
		m_align = align;
	}

	bool AWidget::applySizeLimit()
	{
		bool changed = false;

		/* Apply size limits */

		if(m_sizeLimit.max.x > 0 && m_sizeLimit.max.y > 0)
		{
			if(m_localBounds.width() > m_sizeLimit.max.x)
			{
				m_localBounds.max.x = m_localBounds.min.x + m_sizeLimit.max.x;
				changed = true;
			}
			if(m_localBounds.height() > m_sizeLimit.max.y)
			{
				m_localBounds.max.y = m_localBounds.min.y + m_sizeLimit.max.y;
				changed = true;
			}
		}

		if(m_localBounds.width() < m_sizeLimit.min.x)
		{
			m_localBounds.max.x = m_localBounds.min.x + m_sizeLimit.min.x;
			changed = true;
		}
		if(m_localBounds.height() < m_sizeLimit.min.y)
		{
			m_localBounds.max.y = m_localBounds.min.y + m_sizeLimit.min.y;
			changed = true;
		}

		if(changed)
			onSizeChanged();

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

	void AWidget::layout(IntRect space)
	{
		if(m_align == NONE)
			return;

		space.min.x += m_margin.left;
		space.min.y += m_margin.top;
		space.max.x -= m_margin.right;
		space.max.y -= m_margin.bottom;

		IntRect newBounds = m_localBounds;

		if(m_align & CENTER_H)
		{
			newBounds.min.x = (space.width() - m_localBounds.width()) / 2;
			newBounds.max.x = (space.width() + m_localBounds.width()) / 2;
		}
		if(m_align & CENTER_V)
		{
			newBounds.min.y = (space.height() - m_localBounds.height()) / 2;
			newBounds.max.y = (space.height() + m_localBounds.height()) / 2;
		}

		if(m_align & FILL_H)
		{
			newBounds.min.x = space.min.x;
			newBounds.max.x = space.max.x;
		}
		else
		{
			if(m_align & LEFT)
			{
				newBounds.offset(space.min.x - newBounds.min.x, 0);
			}
			else if(m_align & RIGHT)
			{
				newBounds.offset(space.max.x - newBounds.max.x, 0);
			}
		}

		if(m_align & FILL_V)
		{
			newBounds.min.y = space.min.y;
			newBounds.max.y = space.max.y;
		}
		else
		{
			if(m_align & TOP)
			{
				newBounds.offset(0, space.min.y - newBounds.min.y);
			}
			else if(m_align & BOTTOM)
			{
				newBounds.offset(0, space.max.y - newBounds.max.y);
			}
		}

		newBounds.repair();

		setLocalBounds(newBounds);
	}

	void AWidget::setFocused(bool f)
	{
		if(f == m_focused)
			return; // Nothing to change

		Root * r = getRoot();
		if(r == nullptr)
		{
			std::cout << "ERROR: AWidget::setFocused: "
					  << "Root is unreachable." << std::endl;
			return;
		}

		m_focused = f;
		if(m_focused)
		{
			// If another different widget is focused
			AWidget * oldFocused = r->getFocusedWidget();
			if(oldFocused && oldFocused != this)
			{
				// Unfocus it
				oldFocused->setFocused(false);
			}

			r->setFocusedWidget(this);
			bringToFront(true); // Recursive
		}
		else
		{
			r->setFocusedWidget(nullptr);
		}
	}

	void AWidget::setHovered(bool h)
	{
		if(m_hovered)
		{
			if(!h)
			{
				m_hovered = false;
//				onMouseQuit();
			}
		}
		else
		{
			if(h)
			{
				m_hovered = true;
//				onMouseEnter();
			}
		}
	}

	/*
		Input
	*/

	bool AWidget::mouseMoved(int /*oldX*/, int /*oldY*/, int newX, int newY)
	{
		// Note : AComposite takes care of setting hover flags
		return m_localBounds.contains(newX, newY);
	}

	bool AWidget::mousePressed(Mouse::Button button)
	{
		if(m_hovered)
		{
			if(button == Mouse::LEFT)
				m_pressed = true;
			setFocused(true);
			onPress();
			return true;
		}
		return false;
	}

	bool AWidget::mouseReleased(Mouse::Button button)
	{
		if(m_pressed)
		{
			if(button == Mouse::LEFT)
				m_pressed = false;
			onRelease();
			return true;
		}
		return false;
	}

	bool AWidget::mouseWheelMoved(int /*delta*/)
	{
		return m_hovered;
	}

	bool AWidget::keyPressed(Keyboard::Key key)
	{
		if(key == Keyboard::Key::RETURN && m_focused)
		{
			m_pressed = true;
			onPress();
			return true;
		}
		return false;
	}

	bool AWidget::keyReleased(Keyboard::Key /*key*/)
	{
		if(m_pressed)
		{
			m_pressed = false;
			onRelease();
			return true;
		}
		return false;
	}

	bool AWidget::textEntered(unsigned int /*unicode*/)
	{
		return m_focused;
	}

} // namespace ui
} // namespace zn




