/*
WidgetType.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "WidgetType.hpp"

namespace zn
{
namespace ui
{
	std::string toString(WidgetType t)
	{
		switch(t)
		{
		case GENERIC: return "Generic";
		case ROOT: return "Root";
		case PANEL: return "Panel";
		case TEXT: return "Text";
		case PUSH_BUTTON: return "PushButton";
		case CHECK_BOX: return "CheckBox";
		case DRAG_ZONE: return "DragZone";
		default: return "Generic";
		}
	}

} // namespace ui
} // namespace zn

