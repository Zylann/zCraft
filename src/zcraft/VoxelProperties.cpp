#include "zcraft/VoxelProperties.hpp"
#include "zcraft/Voxel.hpp"

namespace zcraft
{
	/* Static */

	VoxelProperties s_list[voxel::TYPE_COUNT];

	void VoxelProperties::initList()
	{
		VoxelProperties np;

		// AIR
		np.opaque = false;
		np.cube = true;
		np.solid = false;
		np.name = "air";
		np.color.set(0,0,0,0);
		np.averageColor.set(0,0,0,0);
		s_list[voxel::AIR] = np;

		// STONE
		np.opaque = true;
		np.cube = true;
		np.solid = true;
		np.name = "stone";
		np.color.set(127, 127, 127);
		np.averageColor.set(127, 127, 127);
		s_list[voxel::STONE] = np;

		// DIRT
		np.opaque = true;
		np.cube = true;
		np.solid = true;
		np.name = "dirt";
		np.color.set(128, 64, 0);
		np.averageColor.set(128, 64, 0);
		s_list[voxel::DIRT] = np;

		// GRASS
		np.opaque = true;
		np.cube = true;
		np.solid = true;
		np.name = "grass";
		np.color.set(64, 192, 32);
		np.averageColor.set(64, 192, 32);
		s_list[voxel::GRASS] = np;

	}

	void VoxelProperties::freeList()
	{
		// Nothing to free for now,
		// because voxel properties are stored in a static array
	}

	const VoxelProperties & VoxelProperties::get(u8 type)
	{
		return s_list[type];
	}

} // namespace zcraft

