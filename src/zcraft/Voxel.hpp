#ifndef VOXEL_HPP_INCLUDED
#define VOXEL_HPP_INCLUDED

#include <iostream>
#include "zcraft/common.hpp"

namespace zcraft
{
	namespace voxel
	{
		/** Basic types **/

		enum VoxelType
		{
			AIR = 0,
			STONE,
			DIRT,
			GRASS,

			TYPE_COUNT // Keep last
		};

		/** Meta-types **/

		enum AirTypes
		{
			AIR_NORMAL = 0,
			AIR_UNLOADED
		};
	}

	struct VoxelProperties;

	/// Voxels are the basis of maps.
	/// They consist on voxels.

	struct Voxel
	{
		// Constants

		static const u8 LIGHT_MIN = 0x2; // Not zero, otherwise we can't see nothing
		static const u8 LIGHT_MAX = 0xf;

		// Attributes

		u8 type; // 8 bits for type
		u8 meta; // 4 higher bits for metadata, 4 lower bits for light

		// Methods

		// Constructs an empty air block.
		Voxel(u8 type0 = voxel::AIR, u8 metaType0 = 0x0, u8 light0 = LIGHT_MAX);

		// Gets the common properties of the block
		const VoxelProperties & properties() const;

		// Writes the voxel in a binary stream
		void serialize(std::ostream & os) const;

		// Reads the voxel from a binary stream
		void unserialize(std::istream & is);

		// Gets the light code of the voxel, between LIGHT_MIN and LIGHT_MAX.
		// (Must be converted for drawing in 0-255 range)
		inline u8 getLight() const
		{
			return meta & 0x0f;
		}

	};

	struct LocatedVoxel
	{
		Voxel voxel;
		Vector3i pos;
	};

} // namespace zcraft

#endif // VOXEL_HPP_INCLUDED



