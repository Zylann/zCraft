/*
Entity.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_DRAWABLE_HPP
#define ZN_GAME_DRAWABLE_HPP

namespace zn
{
	class IDrawable
	{
	public:

		virtual ~IDrawable() {}

		virtual void render() = 0;
	};

} // namespace zn

#endif // ZN_GAME_DRAWABLE_HPP

