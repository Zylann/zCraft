/*
BlockMeshMap.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include "zcraft/BlockMeshMap.hpp"

using namespace engine;

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

	void BlockMeshMap::setMesh(const Vector3i pos, gl::VertexColorArray * mesh)
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
				p.second->draw();
			else
			{
				// This should never happen.
				std::cout << "ERROR: BlockMeshMap::drawAll: a mesh is null" << std::endl;
				break;
			}
		}
	}

} // namespace zcraft




