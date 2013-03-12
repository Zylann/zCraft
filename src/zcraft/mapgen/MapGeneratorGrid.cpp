/*
MapGeneratorGrid.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "zcraft/mapgen/MapGeneratorGrid.hpp"

using namespace zn;

namespace zcraft
{
	MapGeneratorGrid::MapGeneratorGrid(u32 seed)
	{
		m_seed = seed;
	}

	Block * MapGeneratorGrid::makeBlock(Vector3i pos)
	{
		Block * block = nullptr;
		//Vector3i org = pos * Block::SIZE;
		Voxel v1 = Voxel(voxel::VoxelType::STONE);

		block = new Block(pos);
		for(unsigned int i = 0; i < Block::SIZE; ++i)
		{
			block->set(i, 0, 0, v1);
			block->set(0, i, 0, v1);
			block->set(0, 0, i, v1);

			block->set(i, Block::SIZE-1, 0, v1);
			block->set(Block::SIZE-1, i, 0, v1);
			block->set(Block::SIZE-1, 0, i, v1);

			block->set(i, 0, Block::SIZE-1, v1);
			block->set(0, i, Block::SIZE-1, v1);
			block->set(0, Block::SIZE-1, i, v1);

			block->set(i, 1, 0, v1);
			block->set(i, 0, 1, v1);

			block->set(1, i, 0, v1);
			block->set(0, i, 1, v1);

			block->set(1, 0, i, v1);
			block->set(0, 1, i, v1);
		}

		return block;
	}

} // namespace zcraft



