/*
BlockMeshMap.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED
#define ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED

#include <map>
#include "zcraft/common.hpp"
#include "engine/opengl/VertexColorArray.hpp"

namespace zcraft
{
	class BlockMeshMap
	{
	private :

		std::map<Vector3i,engine::gl::VertexColorArray*> m_meshs;

	public :

		BlockMeshMap();

		~BlockMeshMap();

		void clear();

		bool isMesh(const Vector3i pos) const;

		void setMesh(const Vector3i pos, engine::gl::VertexColorArray * mesh);

		void eraseMesh(const Vector3i pos);

		void drawAll();

		inline u32 getCount() const { return m_meshs.size(); }

	};

} // namespace zcraft

#endif // ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED


