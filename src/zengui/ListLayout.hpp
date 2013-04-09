/*
ListLayout.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_LISTLAYOUT_HPP_INCLUDED
#define ZENGUI_LISTLAYOUT_HPP_INCLUDED

#include "Composite.hpp"

namespace zn
{
namespace ui
{
	enum Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	class ListLayout : public AComposite
	{
	private :

		Orientation m_orientation;
		int m_spacing;

	public :

		ListLayout(Orientation orient = VERTICAL, int spacing = 0)
			: AComposite(), m_orientation(orient), m_spacing(0)
		{}

		virtual ~ListLayout() {}

		void layout() override;

	private :

		void layoutHorizontal();
		void layoutVertical();

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_LISTLAYOUT_HPP_INCLUDED


