#ifndef VOXELBUFFER_HPP_INCLUDED
#define VOXELBUFFER_HPP_INCLUDED

#include "engine/ShiftArray3D.hpp"
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

		virtual void printDataItem(std::ostream & os, Voxel & item) const;

	};

} // namespace zcraft

#endif // VOXELBUFFER_HPP_INCLUDED
