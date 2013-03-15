/*
BasicTheme.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "BasicTheme.hpp"
#include "zengui/Color.hpp"
#include "zengui/Renderer.hpp"

using namespace zn;
using namespace ui;

namespace experimental
{
	std::string BasicTheme::getName()
	{
		return "Basic";
	}

	void BasicTheme::drawDummyWidget(IRenderer & r, const AWidget & w)
	{
		Vector2i pos = w.getAbsolutePosition();
		const int width = w.getBounds().width();
		const int height = w.getBounds().height();

		static const Color borderColor(224, 224, 224);

		r.setColor(borderColor);
		r.drawRect(pos.x, pos.y, width, height, false);
	}

	void BasicTheme::drawPanel(IRenderer & r, const AWidget & panel)
	{
		Vector2i pos = panel.getAbsolutePosition();
		const int width = panel.getBounds().width();
		const int height = panel.getBounds().height();

		static const Color borderColor(224, 224, 224);
		static const Color fillColor(224, 224, 224);

		r.setColor(borderColor);
		r.drawRect(pos.x, pos.y, width, height, false);
		r.setColor(fillColor);
		r.drawRect(pos.x, pos.y, width, height, true);
	}


} // namespace experimental



