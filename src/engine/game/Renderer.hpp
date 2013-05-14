/*
Entity.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_RENDERER_HPP
#define ZN_GAME_RENDERER_HPP

// TODO EntityRenderer: rename this file "Renderer" when QBS will work

#include "Component.hpp"
#include "Drawable.hpp"

namespace zn
{
	class ARenderer : public AComponent, public IDrawable
	{
	public:
		virtual ~ARenderer() {}
	};

} // namespace zn

#endif // ZN_GAME_RENDERER_HPP
