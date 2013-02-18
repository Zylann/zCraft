/*
MapGeneratorCanyons.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/noise.hpp"
#include "zcraft/mapgen/MapGeneratorCanyons.hpp"

using namespace zn;

namespace zcraft
{
	MapGeneratorCanyons::MapGeneratorCanyons(u32 seed)
	: AMapGenerator(seed)
	{}

	Block * MapGeneratorCanyons::makeBlock(Vector3i pos)
	{
		Block * block = nullptr;
		Vector3i org = pos * Block::SIZE;

		block = new Block(pos);

		float n, n2;
		float nr = 0.5f;
		u8 x, y, z;

		// Generates a gorgeous cave world
		for(z = 0; z < Block::SIZE; z++)
		{
			if(org.z + z < 0)
				nr = 0.5f;
			else if(org.z + z > 256)
				nr = 0;
			else
			{
				nr = 1.f - static_cast<float>(org.z + z) / 256.f;
				nr = nr * nr * nr * nr;
				nr /= 0.5f;
				if(nr < 0.025f)
					nr = 0.025f;
			}

			for(y = 0; y < Block::SIZE; y++)
			for(x = 0; x < Block::SIZE; x++)
			{
				n = noise3dPerlin(org.x + x, org.y + y, org.z + z, m_seed, 5, 0.5f, 64);
				if(n > 0.5f-nr && n < 0.5f+nr)
				{
					u8 type = node::DIRT;
					n2 = noise3dPerlin(org.x + x, org.y + y, org.z + z, m_seed+1, 5, 0.5f, 64);
					if(n2 < 0.5f)
						type = node::STONE;
					block->set(x, y, z, Node(type));
				}
			}
		}

		if(block != nullptr)
			block->dirty = true; // To make it saved even if not modified yet

		return block;
	}

} // namespace zcraft




