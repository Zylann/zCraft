/*
MapGeneratorGrid.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZCRAFT_MAPGENERATORGRID_HPP_INCLUDED
#define ZCRAFT_MAPGENERATORGRID_HPP_INCLUDED

#include "MapGenerator.hpp"

namespace zcraft
{
	class MapGeneratorGrid : public AMapGenerator
	{
	public :

		MapGeneratorGrid(u32 seed = 131183);

		Block * makeBlock(Vector3i pos) override;

	};

} // namespace zcraft


#endif // ZCRAFT_MAPGENERATORGRID_HPP_INCLUDED
