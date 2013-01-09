/*
BlockMap.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "zcraft/BlockMap.hpp"
#include "zcraft/face.hpp"

namespace zcraft
{
	BlockMap::BlockMap()
	{
		r_lastAccessed = nullptr;
	}

	BlockMap::~BlockMap()
	{
		clear();
	}

	/* Block access */

	void BlockMap::clear()
	{
		r_lastAccessed = nullptr;
		for(auto & p : m_blocks)
		{
			if(p.second != nullptr)
				delete p.second;
		}
		m_blocks.clear();
	}

	bool BlockMap::isBlock(const Vector3i & bpos)
	{
		return getBlock(bpos) != nullptr;
	}

	Block * BlockMap::getBlock(const Vector3i & bpos)
	{
		if(r_lastAccessed != nullptr && r_lastAccessed->getPosition() == bpos)
			return r_lastAccessed;

		const auto it = m_blocks.find(bpos);
		if(it != m_blocks.end())
		{
			r_lastAccessed = it->second;
			return it->second;
		}
		return nullptr;
	}

	Block * BlockMap::removeBlock(const Vector3i & bpos)
	{
		auto it = m_blocks.find(bpos);
		if(it != m_blocks.end())
		{
			Block * b = it->second;
			m_blocks.erase(it);

			if(r_lastAccessed == b)
				r_lastAccessed = nullptr;

			notifyListenersForBlockRemove(bpos);
			return b;
		}
		return nullptr;
	}

	void BlockMap::setBlock(Block * b)
	{
		if(b != nullptr)
			setBlock(b->getPosition(), b);
		else
			std::cout << "WARNING: BlockMap::setBlock: null block passed" << std::endl;
	}

	void BlockMap::setBlock(const Vector3i & pos, Block * b)
	{
		if(r_lastAccessed != nullptr && r_lastAccessed->getPosition() == pos)
			r_lastAccessed = nullptr;

		auto it = m_blocks.find(pos);
		if(it != m_blocks.end())
		{
			// The block already exists
			if(it->second != nullptr)
			{
				delete it->second;
				if(b != nullptr)
					std::cout << "INFO: BlockMap::setBlock: "
						<< "overwitten at " << b->getPosition() << std::endl;
			}
			if(b != nullptr)
			{
				it->second = b;
				notifyListenersForBlockChange(pos);
			}
			else
			{
				m_blocks.erase(it);
				notifyListenersForBlockRemove(pos);
			}
		}
		else
		{
			m_blocks[b->getPosition()] = b;
			notifyListenersForBlockAdd(pos);
		}
	}

	void BlockMap::eraseBlock(const Vector3i & bpos)
	{
		setBlock(bpos, nullptr);
	}

	void BlockMap::getUnloadedBlockPositions(
			std::list<Vector3i> & plist, Vector3i minPos, Vector3i maxPos)
	{
		Vector3i bpos;
		for(bpos.z = minPos.z; bpos.z <= maxPos.z; bpos.z++)
		for(bpos.y = minPos.y; bpos.y <= maxPos.y; bpos.y++)
		for(bpos.x = minPos.x; bpos.x <= maxPos.x; bpos.x++)
		{
			const auto it = m_blocks.find(bpos);
			if(it == m_blocks.end())
				plist.push_back(bpos);
		}
	}

	void BlockMap::removeBlocksNotInArea(
			std::list<Block*> & blockList,
			const Vector3i centerBlockPos, u32 radiusBlocks)
	{
		const Vector3i min = centerBlockPos - Vector3i(1,1,1) * radiusBlocks;
		const Vector3i max = centerBlockPos + Vector3i(1,1,1) * radiusBlocks;
		std::list<std::map<Vector3i,Block*>::iterator> iterators;

		for(auto it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			if( it->first.z < min.z || it->first.z > max.z ||
				it->first.y < min.y || it->first.y > max.y ||
				it->first.x < min.x || it->first.x > max.x)
			{
				blockList.push_back(it->second);
				iterators.push_back(it);
			}
		}

		for(auto & it : iterators)
		{
			notifyListenersForBlockRemove(it->first);
			m_blocks.erase(it);
		}
	}

	void BlockMap::getNeighboringBlocks(
			const Vector3i blockPos,
			std::list<Block*> & neighbors)
	{
		Block * block = nullptr;
		for(u8 dir = 0; dir < 6; dir++)
		{
			block = getBlock(blockPos + face::toVec3i(dir));
			if(block != nullptr)
				neighbors.push_back(block);
		}
	}

	/* Node access */

	// TODO BlockMap: clarify coordinate systems

	Node BlockMap::getNode(const Vector3i & pos)
	{
		Block * b = getBlock(Vector3i(pos.x >> 4, pos.y >> 4, pos.z >> 4));
		if(b != nullptr)
		{
			return b->get(pos.x & 0x0000000f,
						 pos.y & 0x0000000f,
						 pos.z & 0x0000000f);
		}
		else
			return Node(node::AIR, node::AIR_UNLOADED, 0x02);
	}

	bool BlockMap::setNode(const Vector3i & pos, Node n)
	{
		Block * b = getBlock(Vector3i(pos.x >> 4, pos.y >> 4, pos.z >> 4));
		if(b != nullptr)
		{
			b->set(pos.x & 0x0000000f,
				 pos.y & 0x0000000f,
				 pos.z & 0x0000000f, n);
			notifyListenersForBlockChange(b->getPosition());
		}
		else
			return false;
		return true;
	}

	u32 BlockMap::getBlockCount() const
	{
		return m_blocks.size();
	}

	std::pair<s32, Node> BlockMap::getUpperNode(s32 x, s32 y, s32 minZ, s32 maxZ)
	{
		// TODO BlockMap: optimize getUpperNode()

		std::pair<s32,Node> p;
		Vector3i pos(x, y, maxZ);

		for(; pos.z >= minZ; pos.z--)
		{
			p.second = getNode(pos);
			if(p.second.type != node::AIR)
				break;
		}
		p.first = pos.z;
		return p;
	}

	void BlockMap::addListener(IMapListener * listener)
	{
		m_listeners.push_back(listener);
	}

	void BlockMap::removeListener(IMapListener * listener)
	{
		m_listeners.remove(listener);
	}

	void BlockMap::notifyListenersForBlockAdd(const Vector3i pos)
	{
		for(auto & listener : m_listeners)
			listener->blockAdded(pos, *this);
	}

	void BlockMap::notifyListenersForBlockChange(const Vector3i pos)
	{
		for(auto & listener : m_listeners)
			listener->blockChanged(pos, *this);
	}

	void BlockMap::notifyListenersForBlockRemove(const Vector3i pos)
	{
		for(auto & listener : m_listeners)
			listener->blockRemoved(pos, *this);
	}

} // namespace zcraft





