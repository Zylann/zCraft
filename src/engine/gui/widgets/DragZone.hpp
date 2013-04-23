/*
DragZone.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_DRAGZONE_HPP
#define ZENGUI_DRAGZONE_HPP

#include "../Widget.hpp"
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief An empty widget that moves its parent if dragged
	 */
	class DragZone : public AWidget
	{
	public:
		// TODO DragZone: specify the dragged widget instead of using the parent

		DragZone() : AWidget() {}
		virtual ~DragZone() {}

		WidgetType getType() const override { return DRAG_ZONE; }

		virtual bool mousePressed(Mouse::Button button) override
		{
			if(AWidget::mousePressed(button))
			{
				if(r_parent != nullptr)
				{
					// Will bring the parent to front
					r_parent->setFocused(true);
				}
				return true;
			}
			return false;
		}

		virtual bool mouseMoved(int oldX, int oldY, int newX, int newY) override
		{
			if(isPressed() && r_parent != nullptr)
			{
				r_parent->setLocalBounds(
					r_parent->getLocalBounds().offset(newX-oldX, newY-oldY));
				return true;
			}
			return AWidget::mouseMoved(oldX, oldY, newX, newY);
		}

	protected:

		virtual void renderSelf(IRenderer &r) override
		{
			r_skin->drawDragZone(r, *this);
		}
	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_DRAGZONE_HPP
