/*
MapGenerator.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPGENERATOR_HPP_INCLUDED
#define MAPGENERATOR_HPP_INCLUDED

#include "zcraft/Block.hpp"

namespace zcraft
{
	class AMapGenerator
	{
	protected :

		u32 m_seed;

	public :

		AMapGenerator(u32 seed = 131183) : m_seed(seed) {}

		virtual ~AMapGenerator() {}

		inline u32 getSeed() const { return m_seed; }

		virtual Block * makeBlock(Vector3i pos) = 0;

	};

} // namespace zcraft

#endif // MAPGENERATOR_HPP_INCLUDED
