#include "engine/noise.hpp"
#include "zcraft/MapGenerator.hpp"

using namespace engine;

namespace zcraft
{
	MapGenerator::MapGenerator(u32 seed)
	{
		m_seed = seed;
	}

	Block * MapGenerator::makeBlock(Vector3i pos)
	{
		Block * block = nullptr;
		Vector3i org = pos * Block::SIZE;

		block = new Block(pos);

		/*
		float n;
		float nr = 0.5f;
		u8 x, y, z;

		for(z = 0; z < Block::SIZE; z++)
		{
			if(org.z + z < 0)
				nr = 0.5f;
			else if(org.z + z > 256)
				nr = 0;
			else
			{
				nr = 1.f - static_cast<float>(org.z + z) / 256.f;
				nr = nr * nr * nr;
				nr /= 0.5f;
			}

			for(y = 0; y < Block::SIZE; y++)
			for(x = 0; x < Block::SIZE; x++)
			{
				n = noise3dPerlin(org.x + x, org.y + y, org.z + z, m_seed, 5, 0.5f, 64);
				if(n > 0.5f-nr && n < 0.5f+nr)
					block->set(x, y, z, Node(node::STONE));
			}
		}
		*/

		if(org.z >= 0 && org.z < 128)
		{
			for(u8 y = 0; y < Block::SIZE; y++)
			for(u8 x = 0; x < Block::SIZE; x++)
			{
				u16 h = (u16)(128.f * (float)noise2dPerlin(
							x + org.x, y + org.y, m_seed, 5, 0.5, 128));

				if(h >= org.z)
					h -= org.z;
				else
					h = 0;

				if(h >= Block::SIZE)
					h = Block::SIZE - 1;

				if(h != 0)
				{
					for(u16 z = 0; z <= h; z++)
						block->set(x, y, z, Node(node::STONE));
				}
			}
		}
		else if(org.z < 0)
		{
			block->fill(Node(node::STONE));
		}

		if(block != nullptr)
			block->dirty = true; // To make it saved even if not modified yet

		return block;
	}

} // namespace zcraft




