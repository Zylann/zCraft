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
		PUSH_BUTTON,
		DRAG_ZONE,

		COUNT // Keep last
	};

	std::string toString(WidgetType t);

} // namespace ui
} // namespace zn

#endif // ZENGUI_WIDGETTYPE_HPP




