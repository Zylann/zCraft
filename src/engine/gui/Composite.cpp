/*
Container.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Composite.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	AComposite::~AComposite()
	{
		eraseAll();
	}

	void AComposite::setSkin(ISkin & theme, bool recursive)
	{
		//std::cout << "DEBUG: AComposite: setSkin (ID=" << getID() << ")" << std::endl;
		r_skin = &theme;
		if(recursive)
		{
			for(auto & child : m_children)
				child->setSkin(theme, recursive);
		}
	}

	bool AComposite::contains(const AWidget * child) const
	{
		return m_children.contains(child);
	}

	AWidget * AComposite::add(AWidget * newChild)
	{
		if(newChild == nullptr)
		{
			std::cout << "ERROR: AComposite::add: "
				"given widget is null." << std::endl;
			return nullptr;
		}
		if(newChild == this)
		{
			std::cout << "ERROR: AComposite::add: "
				"can't do that with self."
				"ID=\"" << newChild->getID() << '"' << std::endl;
			return nullptr;
		}
		if(contains(newChild))
		{
			std::cout << "ERROR: AComposite::add: "
				"can't add twice the same widget. "
				"ID=\"" << newChild->getID() << '"' << std::endl;
			return nullptr;
		}

		m_children.add(newChild);

		newChild->setParent(this);

		if(r_skin != nullptr)
		{
			//std::cout << "DEBUG: set skin on newChild" << std::endl;
			newChild->setSkin(*r_skin);
		}
		return newChild;
	}

	void AComposite::erase(AWidget * child)
	{
		m_children.erase(child);
	}

	void AComposite::eraseAll()
	{
		m_children.clear();
	}

	AWidget * AComposite::getChildFromID(const std::string & ID)
	{
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			AWidget * w = (*it);
			if(w->getID() == ID)
				return w;
		}
		return nullptr;
	}

	void AComposite::bringChildToFront(AWidget * child)
	{
		m_children.toFront(child);
	}

	void AComposite::layout(IntRect space)
	{
		AWidget::layout(space);
		layout();
	}

	void AComposite::layout()
	{
		IntRect ownSpace;
		ownSpace.min.x = m_padding.left;
		ownSpace.min.y = m_padding.top;
		ownSpace.max.x = m_localBounds.width() - m_padding.right - 1;
		ownSpace.max.y = m_localBounds.height() - m_padding.bottom - 1;

		for(AWidget* & child : m_children)
		{
			child->layout(ownSpace);
		}
	}

	bool AComposite::processInput(const InputEvent & e)
	{
		if(!isVisible())
			return false;

		bool consumed = false;

		// Start deferred mode because the list may be modified in the loop
		m_children.beginDefer();
		// Fetch children first
		for(AWidget *& w : m_children)
		{
			if(w->isVisible())
			{
				// Mouse over
				// Note : this is not done in the widget itself because it would
				// cause too much overhead due to the lack of direct-access
				// to other widgets
				if(e.type == InputEvent::MOUSE_MOVED)
				{
					if(consumed)
						w->setHovered(false);
					else
					{
						w->setHovered(w->getBounds().contains(e.mousePos));
					}
				}

				if(!consumed)
				{
					if(w->processInput(e))
					{
						if(w->blocksInput())
							consumed = true;
					}
				}
			}
		}
		// End of deferring mode
		m_children.endDefer();

		if(!consumed) // Then process the event for the composite itself
			return IInputListener::processInput(e);
		return consumed;
	}

	void AComposite::render(IRenderer & r)
	{
		if(m_visible)
		{
			if(r_skin != nullptr)
				renderSelf(r);
			renderChildren(r);
		}
	}

	void AComposite::animate(float dt)
	{
		if(m_visible)
		{
			animateChildren(dt);
		}
	}

	void AComposite::renderChildren(IRenderer & r)
	{
		for(auto it = m_children.rbegin(); it != m_children.rend(); ++it)
		{
			(*it)->render(r);
		}
	}

	void AComposite::animateChildren(float dt)
	{
		for(auto & w : m_children)
		{
			if(w->isVisible())
				w->animate(dt);
		}
	}

} // namespace ui
} // namespace zn



