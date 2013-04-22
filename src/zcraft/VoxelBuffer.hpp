#ifndef VOXELBUFFER_HPP_INCLUDED
#define VOXELBUFFER_HPP_INCLUDED

#include "engine/core/ShiftArray3D.hpp"
#include "zcraft/Voxel.hpp"

namespace zcraft
{
	/*
		3D buffer specialized in Voxel manipulation
	*/

	class VoxelBuffer : public zn::ShiftArray3D<Voxel>
	{
	public :

		VoxelBuffer();
		~VoxelBuffer();
	};

} // namespace zcraft

#endif // VOXELBUFFER_HPP_INCLUDED
