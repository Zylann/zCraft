/*
Block.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef BLOCKMESH_HPP_INCLUDED
#define BLOCKMESH_HPP_INCLUDED

#include "engine/opengl/VertexColorArray.hpp"
#include "zcraft/common.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
	class BlockMesh
	{
	private :

		zn::gl::VertexColorArray * m_vbo = nullptr;

	public :

		BlockMesh();

		~BlockMesh();

		// TODO BlockMesh: make non-copyable

		void draw();

		bool isEmpty() const;

		// Reinitializes the mesh and makes it empty
		void clear();

		// Builds the mesh from voxels. This is a CPU expensive task.
		void buildFromVoxelData(const Vector3i bpos, VoxelBuffer & vb);

	};

} // namespace zcraft

#endif // BLOCKMESH_HPP_INCLUDED


