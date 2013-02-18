#include "engine/Color.hpp"
#include "zcraft/NodeProperties.hpp"
#include "zcraft/cartographer/Cartographer.hpp"
#include "zcraft/MapLoader.hpp"

using namespace engine;

namespace zcraft
{
	/*
		static
	*/

	sf::Image Cartographer::renderChunkTopDown(
			BlockMap & map, s32 bx, s32 by, s32 minZ, s32 maxZ)
	{
		s32 offX = bx * Block::SIZE;
		s32 offY = by * Block::SIZE;

		sf::Image img;
		img.create(Block::SIZE, Block::SIZE);
		Color color;

		// For each Z-wise node line
		for(u8 y = 0; y < Block::SIZE; y++)
		for(u8 x = 0; x < Block::SIZE; x++)
		{
			// Get color of the top node
			std::pair<s32, Node> topNode = map.getUpperNode(offX + x, offY + y, minZ, maxZ);
			color = topNode.second.properties().averageColor;

			// Apply some height gradient
			float k = 0.5f;
			if(topNode.first >= minZ)
				k = 0.1f + 0.9f * (float)(topNode.first - minZ) / (float)(maxZ - minZ);

			color.multiplyRGB(k);

			img.setPixel(x, y, color.toSfColor());
		}

		return img;
	}

	void Cartographer::renderTopDown(
			BlockMap & map, Cartography & cart,
			Vector2i min, Vector2i max, s32 minZ, s32 maxZ)
	{
		Vector2i pos;
		for(pos.y = min.y; pos.y <= max.y; pos.y++)
		for(pos.x = min.x; pos.x <= max.x; pos.x++)
		{
			sf::Image img = renderChunkTopDown(map, pos.x, pos.y, minZ, maxZ);
			cart.setPictureFromImage(pos, img);
		}
	}

	void Cartographer::renderWorldToFile(
			const std::string worldDir, const std::string filename)
	{
		std::cout << "Cartographer: fetching world files..." << std::endl;
		MapLoader loader(worldDir);
		std::set<Vector3i> blockPositions;
		loader.getAllBlockPositions(blockPositions);
		std::cout << "| Found "
			<< blockPositions.size() << " block files." << std::endl;

		if(blockPositions.size() == 0)
		{
			std::cout << "Cartographer: the world is empty : aborted" << std::endl;
			return;
		}

		std::cout << "Cartographer: Computing world edges... " << std::endl;
		Vector3i min, max;
		for(auto & pos : blockPositions)
		{
			if(pos.x < min.x) min.x = pos.x;
			if(pos.x > max.x) max.x = pos.x;

			if(pos.y < min.y) min.y = pos.y;
			if(pos.y > max.y) max.y = pos.y;

			if(pos.z < min.z) min.z = pos.z;
			if(pos.z > max.z) max.z = pos.z;
		}
		std::cout << "| min=" << min << ", max=" << max << std::endl;

		const Vector3i area = max - min;
		if( area.x >= MAX_SIZE_BLOCKS ||
			area.y >= MAX_SIZE_BLOCKS ||
			area.z >= MAX_SIZE_BLOCKS)
		{
			std::cout << "ERROR: Cartographer: cannot perform a full one-picture "
				<< "rendering, the world is too big." << std::endl;
			return;
		}

		std::cout << "| Done." << std::endl;

		std::cout << "Cartographer: rendering..." << std::endl;

		BlockMap map;
		Vector3i pos;
		Cartography cartography;

		for(pos.x = min.x; pos.x <= max.x; pos.x++)
		{
			for(pos.y = min.y; pos.y <= max.y; pos.y++)
			{
				// Load a Z-wise chunk
				for(pos.z = min.z; pos.z <= max.z; pos.z++)
				{
					if(loader.isBlockOnHardDrive(pos))
					{
						Block * b = loader.loadBlock(pos);
						if(b != 0)
							map.setBlock(b);
					}
				}

				// Render the chunk
				sf::Image pic = renderChunkTopDown(
					map, pos.x, pos.y, Block::SIZE * min.z, Block::SIZE * (max.z+1));

				// Add it to the cartography
				cartography.setPictureFromImage(Vector2i(pos.x, pos.y), pic);

				// Clear map
				map.clear();
			}

			// Progress
			int p = 100.f * (float)(pos.x - min.x) / (float)(max.x - min.x);
			std::cout << "| Progress : " << p << "%" << std::endl;
		}

		std::cout << "| Done." << std::endl;

		std::cout << "Cartographer: Saving cartography..." << std::endl;
		cartography.saveAsBigImage(filename);
		std::cout << "Cartographer: Finished." << std::endl;
	}

} // namespace zcraft




