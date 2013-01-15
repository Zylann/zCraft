/*
BlockMap.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef BLOCKMAP_HPP_INCLUDED
#define BLOCKMAP_HPP_INCLUDED

#include <map>
#include <list>

#include "zcraft/Block.hpp"
#include "zcraft/IMapListener.hpp"

namespace zcraft
{
	struct RayCastResult
	{
		bool collision;
		float distanceCrossed;
		LocatedNode hit;
		LocatedNode hitPrevious;

		RayCastResult()
		{
			collision = false;
			distanceCrossed = 0;
		}
	};

	class BlockMap
	{
	private :

		// Blocks are dynamically allocated and managed here.
		// TODO BlockMap: use a hash map to store blocks
		std::map<Vector3i, Block*> m_blocks;

		// Reference to the last accessed block (optimisation)
		Block * r_lastAccessed;

		std::list<IMapListener*> m_listeners;

	public :

		// Constructs an empty infinite map with no blocks inside it
		BlockMap();

		// Destroys the map and all of its content.
		~BlockMap();

		/* Block access */

		// Clears all of map content.
		void clear();

		// Tests if there is a block at the specified block pos.
		bool isBlock(const Vector3i & bpos);

		// Finds and return a pointer to the block at the specified pos.
		// Returns 0 if there is no block.
		Block * getBlock(const Vector3i & bpos);

		// Sets a block on the map at the position specified in this block.
		// Overwrites previous block if found.
		// Will do nothing if the passed block is null.
		void setBlock(Block * b);

		// Erases the block at the specified pos.
		// Returns true if success, false if there was no block.
		void eraseBlock(const Vector3i & bpos);

		// remove a block from map without deleting it and return a pointer on it.
		// (Then you must delete the block yourself after use)
		Block * removeBlock(const Vector3i & bpos);

		// Tests all block positions in the given range that are not occupied by a Block
		// and return them in a list.
		void getUnloadedBlockPositions(
			std::list<Vector3i> & plist, Vector3i minPos, Vector3i maxPos);

		// Removes blocks that are not in the area defined by
		// centerBlockPos and radiusBlocks and adds them to the given list.
		// (You must delete the blocks yourself after use)
		void removeBlocksNotInArea(
			std::list<Block*> & blockList,
			const Vector3i centerBlockPos, u32 radiusBlocks);

		// Gets blocks around the given block position
		void getNeighboringBlocks(
			const Vector3i blockPos,
			std::list<Block*> & neighbors);

		/* Node access */

		// Gets the node at the specified pos.
		// Returns AIR:UNLOADED if there is no nodes loaded here.
		Node getNode(const Vector3i & pos);

		// Sets the node at the specified pos.
		// Returns true if success, false if there was no nodes loaded here.
		bool setNode(const Vector3i & pos, Node n);

		// Get how many blocks contains the map
		u32 getBlockCount() const;

		// Finds the upper non-AIR node Z-wise on (x, y).
		// Search will begin at maxZ and end at minZ if not found.
		std::pair<s32, Node> getUpperNode(s32 x, s32 y, s32 minZ, s32 maxZ);

		// Casts a vector-oriented ray from the given position until it reaches a solid node.
		RayCastResult raycastToSolidNode(Vector3f start, Vector3f dir, f32 maxDistance);

		/* Listeners */

		void addListener(IMapListener * listener);

		void removeListener(IMapListener * listener);

	private :

		// Sets a block on the map at the specified position.
		// Overwrites previous block if found.
		// If the passed block is 0, it will have the same effect as eraseBlock.
		void setBlock(const Vector3i & pos, Block * b);

		void notifyListenersForBlockAdd(const Vector3i pos);

		void notifyListenersForBlockChange(const Vector3i pos);

		void notifyListenersForBlockRemove(const Vector3i pos);

	};

} // namespace zcraft


#endif // BLOCKMAP_HPP_INCLUDED
