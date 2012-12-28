/*
MapGeneratorCanyons.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPGENERATORCANYONS_HPP_INCLUDED
#define MAPGENERATORCANYONS_HPP_INCLUDED

#include "zcraft/mapgen/MapGenerator.hpp"

namespace zcraft
{
	class MapGeneratorCanyons : public AMapGenerator
	{
	public :

		MapGeneratorCanyons(u32 seed = 131183);

		Block * makeBlock(Vector3i pos) override;

	};

} // namespace zcraft

#endif // MAPGENERATORCANYONS_HPP_INCLUDED
