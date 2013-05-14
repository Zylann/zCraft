/*
WidgetList.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "WidgetList.hpp"

namespace zn
{
namespace ui
{
	WidgetList::WidgetList()
	{
		m_deferCount = 0;
	}

	WidgetList::~WidgetList()
	{
		flush();
		for(AWidget *& w : m_widgets)
			delete w;
	}

	void WidgetList::add(AWidget* w)
	{
		if(w != nullptr)
		{
			if(m_deferCount == 0)
				doAdd(w);
			else
				m_operations.push_back(Operation(w, Operation::Type::ADD));
		}
	}

	void WidgetList::erase(AWidget* w)
	{
		if(w != nullptr)
		{
			if(m_deferCount == 0)
				doErase(w);
			else
				m_operations.push_back(Operation(w, Operation::Type::ERASE));
		}
	}

	void WidgetList::toFront(AWidget *w)
	{
		if(w != nullptr)
		{
			if(m_deferCount == 0)
				doToFront(w);
			else
				m_operations.push_back(Operation(w, Operation::Type::TO_FRONT));
		}
	}

	void WidgetList::clear()
	{
		if(m_deferCount == 0)
			doClear();
		else
			m_operations.push_back(Operation(nullptr, Operation::Type::CLEAR));
	}

	void WidgetList::beginDefer()
	{
		++m_deferCount;
	}

	void WidgetList::endDefer()
	{
		if(m_deferCount != 0)
		{
			--m_deferCount;
			if(m_deferCount == 0)
				flush();
		}
	}

	void WidgetList::doAdd(AWidget* w)
	{
		m_widgets.push_back(w);
	}

	void WidgetList::doErase(AWidget* w)
	{
		m_widgets.remove(w);
		delete w;
	}

	void WidgetList::doToFront(AWidget* w)
	{
		auto it = m_widgets.begin();
		for(; it != m_widgets.end(); ++it)
		{
			if(*it == w)
				break;
		}
		m_widgets.erase(it);
		m_widgets.push_front(w);
	}

	void WidgetList::doClear()
	{
		for(AWidget *& w : m_widgets)
			delete w;
		m_widgets.clear();
	}

	void WidgetList::flush()
	{
		for(Operation & op : m_operations)
		{
			switch(op.type)
			{
			case Operation::Type::ADD: 		doAdd(op.widget); break;
			case Operation::Type::ERASE:	doErase(op.widget); break;
			case Operation::Type::TO_FRONT: doToFront(op.widget); break;
			case Operation::Type::CLEAR:	doClear(); break;
			default: break;
			}
		}
		m_operations.clear();
	}

	bool WidgetList::contains(const AWidget * w) const
	{
		for(auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
		{
			if((*it) == w)
				return true;
		}
		for(const Operation & op : m_operations)
		{
			if(op.type == Operation::Type::ADD && w == op.widget)
				return true;
		}
		return false;
	}

} // namespace ui
} // namespace zn




