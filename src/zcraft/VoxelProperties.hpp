#ifndef VOXELPROPERTIES_HPP_INCLUDED
#define VOXELPROPERTIES_HPP_INCLUDED

#include <string>
#include "zcraft/common.hpp"
#include "engine/Color.hpp"

namespace zcraft
{
	class VoxelProperties
	{
	public :

		bool cube; // Is the voxel a cube?
		bool opaque; // Is the voxel opaque?
		bool solid; // Is the voxel solid (collisions) ?
		std::string name; // Technical name
		std::string displayableName; // Player-displayed name
		zn::Color averageColor; // Average color (used for minimap)
		zn::Color color; // Override color

	public :

		// Creates an opaque white cube
		VoxelProperties()
		{
			cube = true;
			opaque = true;
			color.set(255,255,255,255);
			averageColor.set(color);
			name = "undefined";
			displayableName = "undefined";
			solid = false;
		}

		inline bool isOpaqueCube() const
		{
			return cube && opaque;
		}

		static void initList();

		static void freeList();

		static const VoxelProperties & get(u8 type);

	};

} // namespace zcraft

#endif // VOXELPROPERTIES_HPP_INCLUDED
