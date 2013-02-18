#ifndef NODEBUFFER_HPP_INCLUDED
#define NODEBUFFER_HPP_INCLUDED

#include "engine/Array3D.hpp"
#include "zcraft/Node.hpp"

namespace zcraft
{
	/*
		3D buffer specialized in Node manipulation
	*/

	class VoxelBuffer : public zn::Array3D<Node>
	{
	public :

		VoxelBuffer();
		~VoxelBuffer();

		virtual void printDataItem(std::ostream & os, Node & item) const;

	};

} // namespace zcraft

#endif // NODEBUFFER_HPP_INCLUDED
