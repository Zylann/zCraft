/*
Vertex.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GL_VERTEX_HPP_INCLUDED
#define ZN_GL_VERTEX_HPP_INCLUDED

#include "engine/core/types.hpp"

namespace zn
{
namespace gl
{
	struct VertexType
	{
		struct Attrib
		{
			u32 offset;
			u32 count;
			u32 size;

			Attrib()
			{
				count = 0;
			}

			inline void set(u32 off, u32 cnt, u32 sz)
			{
				offset = off;
				size = sz;
				count = cnt;
			}
		};

		Attrib position;
		Attrib color;
		Attrib normal;
		Attrib texcoord;
	};

	struct Vertex_P3F_C1I_N3F_T2F
	{
		f32 x;
		f32 y;
		f32 z;
		u32 rgba;
		f32 nx;
		f32 ny;
		f32 nz;
		f32 u;
		f32 v;
	};

	struct Vertex_P3B_C1S_N3B
	{
		u8 x;
		u8 y;
		u8 z;
		u16 rgba; // rrrrgggg bbbbaaaa
		u8 nx;
		u8 ny;
		u8 nz;
	};

	struct Vertex_P2F_C1I_T2F
	{
		f32 x;
		f32 y;
		f32 z;
		u32 rgba;
		f32 u;
		f32 v;
	};

	typedef Vertex_P2F_C1I_T2F		Vertex2D;
	typedef Vertex_P3F_C1I_N3F_T2F 	Vertex3D;
	typedef Vertex_P3B_C1S_N3B 		VoxelVertex;

} // namespace gl
} // namespace zn

#endif // ZN_GL_VERTEX_HPP_INCLUDED


