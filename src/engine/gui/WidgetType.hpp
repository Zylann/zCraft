/*
WidgetType.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_WIDGETTYPE_HPP
#define ZENGUI_WIDGETTYPE_HPP

#include <string>

namespace zn
{
namespace ui
{
	/**
	 * @brief This is a list of numeric identifiers for internal widgets.
	 */
	enum WidgetType
	{
		GENERIC = 0,
		ROOT,
		PANEL,
		TEXT,
		TEXT_FIELD,
		PUSH_BUTTON,
		CHECK_BOX,
		DRAG_ZONE,
		PROGRESS_BAR,
		SLIDER,

		COUNT // Keep last
	};

	std::string toString(WidgetType t);

} // namespace ui
} // namespace zn

#endif // ZENGUI_WIDGETTYPE_HPP




