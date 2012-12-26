#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include "zcraft/common.hpp"
#include "zcraft/Node.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
	/// A block is a fixed-size cubic array of nodes

	class Block
	{
	public :

		static const u32 SIZE = 16;
		static const u32 NODE_COUNT = SIZE * SIZE * SIZE;

	private :

		/// access is done using the index(x,y,z) function
		// TODO Block: optimize for empty blocks
		Node m_nodes[NODE_COUNT];

		/// must not be modified after creation/loading/generation
		Vector3i m_pos;

	public :

		/// Indicates wether the block has been modified or not
		bool dirty;

		/// Constructs an empty block at the given block pos
		Block(const Vector3i pos)
		{
			m_pos = pos;
			dirty = false;
		}

		/// Constructs an empty block at the given block pos
		Block(s16 cx, s16 cy, s16 cz)
		{
			m_pos.set(cx, cy, cz);
			dirty = false;
		}

		~Block();

		/* Nodes access and modification */

		/// Node index from relative coordinates
		/// x, y and z must be in [0,15]
		inline u16 index(s32 x, s32 y, s32 z) const
		{
			// equivalent to (x + 16*y + 16*16*z)
			// Convention : [z][y][x]
			return (z << 8) | (y << 4) | x;
		}

		/// get node at (x,y,z). Use relatives coordinates (in [0,15])
		inline Node get(s32 x, s32 y, s32 z) const
		{
			return m_nodes[index(x, y, z)];
		}

		/// Modifies a node and rises the dirty flag
		inline void set(s32 x, s32 y, s32 z, Node b)
		{
			dirty = true;
			m_nodes[index(x,y,z)] = b;
		}

		/// fill with one kind of node
		void fill(Node nodeValue);

		/// copy nodes to a VoxelBuffer
		void copyTo(VoxelBuffer & vb) const;

		/// copy voxels from one side only to a VoxelBuffer
		void copyBorderTo(VoxelBuffer & vb, u8 dir) const;

		/// fill with empty nodes
		void clear();

		/// Tests if the block contains only empty nodes
		bool containsOnlyEmptyNodes() const;

		/// Tests if all edges are fully made of opaque cubes
		bool areEdgesFullyOpaque() const;

		/// Get upper block position on Y axis
		/// return relative position, -1 if no nodes
		s32 getUpperBlockPosition(u8 x, u8 z) const;

		/// Makes a dynamically allocated copy of this object.
		Block * clone() const;

		/* Metadata */

		/// Get block position in block coordinates
		const Vector3i & getPosition() const;

		/// Makes a string containing basic informations about this object
		std::string toString() const;

		/* serialization */

		void serialize(std::ostream & os) const;
		void unserialize(std::istream & is);

	};

} // namespace zcraft

#endif // BLOCK_HPP_INCLUDED

