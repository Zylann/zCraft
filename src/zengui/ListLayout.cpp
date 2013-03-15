/*
ListLayout.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "ListLayout.hpp"

namespace zn
{
namespace ui
{
	void ListLayout::layout()
	{
		if(m_orientation == Orientation::VERTICAL)
			layoutVertical();
		else
			layoutHorizontal();
	}

	void ListLayout::layoutHorizontal()
	{
		std::cout << "INFO: ListLayout::layoutHorizontal: not supported yet." << std::endl;
	}

	void ListLayout::layoutVertical()
	{
		const IntRect innerBounds = getInnerBounds();

		IntRect r;
		int y = innerBounds.min.y;

		for(auto & child : m_children)
		{
			r.min.x = innerBounds.min.x + child->getMargin().left;
			r.min.y = y + child->getMargin().top;
			r.max.x = innerBounds.max.x - child->getMargin().right;
			r.max.y = r.min.y + child->getBounds().height();

			child->setBounds(r);

			y += r.max.y + child->getMargin().bottom + m_spacing;
		}
	}

} // namespace ui
} // namespace zn

