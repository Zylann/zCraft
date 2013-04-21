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

	bool AComposite::checkChild(const AWidget * child, const std::string & from)
	{
		if(child == nullptr)
		{
			std::cout << "ERROR: AComposite::" << from << ": "
				<< "given widget is null." << std::endl;
			return false;
		}
		if(child == this)
		{
			std::cout << "ERROR: AComposite::" << from << ": "
				<< "can't do that with self."
				<< "ID=\"" << child->getID() << '"' << std::endl;
			return false;
		}
		return true;
	}

	std::list<AWidget*>::iterator
			AComposite::getCheckChild(
					const AWidget * child, const std::string & from)
	{
		if(!checkChild(child, from))
			return m_children.end();

		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if((*it) == child)
				return it;
		}

		std::cout << "ERROR: AComposite::" << from << ": "
			<< "child not found. "
			<< "ID=\"" << child->getID() << '"' << std::endl;
		return m_children.end();
	}

	bool AComposite::contains(const AWidget * child) const
	{
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if((*it) == child)
				return true;
		}
		return false;
	}

	void AComposite::add(AWidget * child)
	{
		if(!checkChild(child, "add"))
			return;
		if(contains(child))
		{
			std::cout << "ERROR: AComposite::add: "
				<< "can't add twice the same widget. "
				<< "ID=\"" << child->getID() << '"' << std::endl;
			return;
		}

		m_children.push_back(child);

		child->setParent(this);

		if(r_skin != nullptr)
		{
			//std::cout << "DEBUG: set skin on child" << std::endl;
			child->setSkin(*r_skin);
		}
	}

	void AComposite::erase(AWidget * child)
	{
		auto it = getCheckChild(child, "erase");
		if(it != m_children.end())
		{
			delete (*it);
			m_children.erase(it);
		}
	}

	void AComposite::eraseAll()
	{
		for(auto it = m_children.begin(); it != m_children.end(); it++)
			delete (*it);
	}

	AWidget * AComposite::getChildFromID(const std::string & ID)
	{
		AWidget * w;
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			w = (*it);
			if(w->getID() == ID)
				return w;
		}
		return nullptr;
	}

	void AComposite::bringChildToFront(AWidget * child)
	{
		// TODO AWidget: widgets should bring-to-front upwards-recursively if a child widget is focused
		auto it = getCheckChild(child, "bringChildToFront");
		if(it != m_children.end())
		{
			m_children.erase(it);
			m_children.push_front(child);
		}
	}

	void AComposite::layout()
	{
	}

	bool AComposite::processInput(const InputEvent & e)
	{
		if(!isVisible())
			return false;

		bool consumed = false;

		// Fetch children first
		for(auto & w : m_children)
		{
			if(w->isVisible())
			{
				// Mouse over
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

		if(!consumed) // Then process the event for the composite itself
			return IInputListener::processInput(e);
		return consumed;
	}

	void AComposite::render(IRenderer & r)
	{
		// TODO separate render, renderWidget and renderChildren
		if(m_visible)
		{
			if(r_skin != nullptr)
				r_skin->drawDummyWidget(r, *this);
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
		AWidget * w;
		for(auto it = m_children.rbegin(); it != m_children.rend(); it++)
		{
			w = (*it);
			if(w->isVisible())
				w->render(r);
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



