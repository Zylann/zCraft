/*
BlockMeshMap.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include <list>
#include "zcraft/BlockMap.hpp"
#include "zcraft/BlockMeshMap.hpp"
#include "zcraft/face.hpp"

using namespace zn;

namespace zcraft
{
	BlockMeshMap::BlockMeshMap()
	{}

	BlockMeshMap::~BlockMeshMap()
	{
		clear();
	}

	void BlockMeshMap::clear()
	{
		for(auto & p : m_meshs)
		{
			if(p.second != nullptr)
				delete p.second;
		}
		m_meshs.clear();
	}

	bool BlockMeshMap::isMesh(const Vector3i pos) const
	{
		return m_meshs.find(pos) != m_meshs.end();
	}

	void BlockMeshMap::setMesh(const Vector3i pos, BlockMesh * mesh)
	{
		if(mesh == nullptr)
		{
			eraseMesh(pos);
			return;
		}

		auto it = m_meshs.find(pos);
		if(it != m_meshs.end())
		{
			delete it->second;
			it->second = mesh;
		}
		else
		{
			m_meshs[pos] = mesh;
		}
	}

	void BlockMeshMap::eraseMesh(const Vector3i pos)
	{
		auto it = m_meshs.find(pos);
		if(it != m_meshs.end())
		{
			delete it->second;
			m_meshs.erase(it);
		}
	}

	void BlockMeshMap::drawAll()
	{
		for(auto & p : m_meshs)
		{
			if(p.second != nullptr)
			{
				p.second->draw();

				// Debug : draws mesh AABBs
//				if(!p.second->isEmpty())
//				{
//					glColor3ub(255,255,255);
//					glPushMatrix();
//					glTranslatef(
//						Block::SIZE * p.first.x,
//						Block::SIZE * p.first.y,
//						Block::SIZE * p.first.z);
//					gl::drawCubeLines(Block::SIZE);
//					glPopMatrix();
//				}
			}
			else
			{
				// This should never happen.
				std::cout << "ERROR: BlockMeshMap::drawAll: a mesh is null" << std::endl;
				break;
			}
		}
	}

	void BlockMeshMap::updateMesh(const Vector3i blockPos, BlockMap & map)
	{
		// start block position
		Vector3i startPos = blockPos * Block::SIZE;

		// voxels area including neighbors
		Vector3i minEdge = startPos - Vector3i(1,1,1);
		Vector3i maxEdge = startPos + Vector3i(1,1,1) * Block::SIZE;
		Area3D area;
		area.setBounds(minEdge, maxEdge);

		VoxelBuffer voxels;
		voxels.create(area);

		// copy voxels

		Block * block = map.getBlock(blockPos);
		if(block != nullptr)
		{
			block->copyTo(voxels);
		}

		// copy side neighbors voxels

		std::list<Block*> neighbors;
		map.getNeighboringBlocks(blockPos, neighbors);
		for(auto & neighbor : neighbors)
		{
			neighbor->copyBorderTo(voxels, blockPos - neighbor->getPosition());
		}

		// Make mesh and add it to the map

		BlockMesh * mesh = new BlockMesh();
		mesh->buildFromVoxelData(blockPos, voxels);
		if(mesh->isEmpty())
			delete mesh;
		else
			setMesh(blockPos, mesh);
	}

	void BlockMeshMap::blockAdded(const Vector3i pos, BlockMap & map)
	{
		// Note : in the following code, the newly added block will not be
		// rendered immediately, but only when it will be surrounded by other
		// blocks, so that we don't need to re-update its mesh each time its
		// neighboring changes.
		// Drawback : it reduces the view distance by 1 block, because edge
		// blocks will not be visible. However I don't think its too much annoying
		// with large distances.

		// FIXME some rare blocks are not computed
		// -> a block is always not computed near the spawn

		// Update block's neighbor meshs if they are surrounded
		Vector3i npos;
		for(u8 dir = 0; dir < 6; dir++)
		{
			npos = pos + face::toVec3i(dir);

			if(isMesh(npos))
				continue;

			std::list<Block*> neighbors2;
			map.getNeighboringBlocks(npos, neighbors2);

			if(neighbors2.size() < 6)
				continue;

			// The neighbor is fully surrounded, we can make its mesh
			updateMesh(npos, map);
		}

		// Update block's mesh if it is surrounded
		std::list<Block*> neighbors;
		map.getNeighboringBlocks(pos, neighbors);
		if(neighbors.size() == 6)
		{
			updateMesh(pos, map);
		}
	}

	void BlockMeshMap::blockChanged(const Vector3i pos, BlockMap & map)
	{
		std::list<Block*> neighbors;
		map.getNeighboringBlocks(pos, neighbors);

		if(neighbors.size() < 6)
			return;

		// The neighbor is fully surrounded, we can make its mesh
		updateMesh(pos, map);
	}

	void BlockMeshMap::blockRemoved(const Vector3i pos, BlockMap & map)
	{
		eraseMesh(pos);
	}


} // namespace zcraft




