/*
MapGeneratorHeightmap.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPGENERATORHEIGHTMAP_HPP_INCLUDED
#define MAPGENERATORHEIGHTMAP_HPP_INCLUDED

#include "zcraft/mapgen/MapGenerator.hpp"

namespace zcraft
{
	class MapGeneratorHeightmap : public AMapGenerator
	{
	public :

		MapGeneratorHeightmap(u32 seed = 131183);

		Block * makeBlock(Vector3i pos) override;

	};

} // namespace zcraft

#endif // MAPGENERATORHEIGHTMAP_HPP_INCLUDED
