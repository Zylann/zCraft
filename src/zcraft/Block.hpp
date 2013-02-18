/*
Block.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include "zcraft/common.hpp"
#include "zcraft/Voxel.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
	// A block is a fixed-size cubic array of voxels

	class Block
	{
	public :

		static const u32 SIZE = 16;
		static const u32 VOXEL_COUNT = SIZE * SIZE * SIZE;

	private :

		// access is done using the index(x,y,z) function
		// TODO Block: optimize for empty blocks
		Voxel m_voxels[VOXEL_COUNT];

		// must not be modified after creation/loading/generation
		Vector3i m_pos;

	public :

		// Indicates wether the block has been modified or not
		bool dirty;

		// Constructs an empty block at the given block pos
		Block(const Vector3i pos)
		{
			m_pos = pos;
			dirty = false;
		}

		// Constructs an empty block at the given block pos
		Block(s16 cx, s16 cy, s16 cz)
		{
			m_pos.set(cx, cy, cz);
			dirty = false;
		}

		~Block();

		/* Voxels access and modification */

		// Voxel index from relative coordinates
		// x, y and z must be in [0,15]
		inline u16 index(s32 x, s32 y, s32 z) const
		{
			// equivalent to (x + 16*y + 16*16*z)
			// Convention : [z][y][x]
			return (z << 8) | (y << 4) | x;
		}

		// get voxel at (x,y,z). Use relatives coordinates (in [0,15])
		inline Voxel get(s32 x, s32 y, s32 z) const
		{
			return m_voxels[index(x, y, z)];
		}

		// Modifies a voxel and rises the dirty flag
		inline void set(s32 x, s32 y, s32 z, Voxel b)
		{
			dirty = true;
			m_voxels[index(x,y,z)] = b;
		}

		// fill with one kind of voxel
		void fill(Voxel voxelValue);

		// copy voxels to a VoxelBuffer
		void copyTo(VoxelBuffer & vb) const;

		// copy voxels from one side only to a VoxelBuffer
		void copyBorderTo(VoxelBuffer & vb, u8 dir) const;

		// copy voxels from one side only to a VoxelBuffer
		void copyBorderTo(VoxelBuffer & vb, const Vector3i vdir) const;

		// fill with empty voxels
		void clear();

		// Calculates if the block contains only one kind of voxel
		bool computeIsUniform(const Voxel voxelValue) const;

		// Tests if all edges are fully made of opaque cubes
		bool areEdgesFullyOpaque() const;

		// Get upper block position on Y axis
		// return relative position, -1 if no voxels
		s32 getUpperBlockPosition(u8 x, u8 z) const;

		// Makes a dynamically allocated copy of this object.
		Block * clone() const;

		/* Metadata */

		// Get block position in block coordinates
		const Vector3i & getPosition() const;

		// Makes a string containing basic informations about this object
		std::string toString() const;

		/* serialization */

		void serialize(std::ostream & os) const;
		void unserialize(std::istream & is);

	};

} // namespace zcraft

#endif // BLOCK_HPP_INCLUDED

