#ifndef DRAGZONE_HPP
#define DRAGZONE_HPP

#include "Widget.hpp"
#include "Skin.hpp"

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

		DragZone() : AWidget() {}
		virtual ~DragZone() {}

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

#endif // DRAGZONE_HPP
