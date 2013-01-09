/*
BlockMeshMap.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED
#define ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED

#include <map>
#include "engine/opengl/VertexColorArray.hpp"
#include "zcraft/common.hpp"
#include "zcraft/IMapListener.hpp"

namespace zcraft
{
	typedef engine::gl::VertexColorArray BlockMesh;

	class BlockMeshMap : public IMapListener
	{
	private :

		std::map<Vector3i,BlockMesh*> m_meshs;

	public :

		BlockMeshMap();

		~BlockMeshMap();

		void clear();

		bool isMesh(const Vector3i pos) const;

		void setMesh(const Vector3i pos, BlockMesh * mesh);

		void eraseMesh(const Vector3i pos);

		void drawAll();

		inline u32 getCount() const { return m_meshs.size(); }

		/* Methods inherited from IMapListener */

		void blockAdded(const Vector3i pos, BlockMap & map) override;

		void blockChanged(const Vector3i pos, BlockMap & map) override;

		void blockRemoved(const Vector3i pos, BlockMap & map) override;

	};

} // namespace zcraft

#endif // ZCRAFT_BLOCKMESHMAP_HPP_INCLUDED


