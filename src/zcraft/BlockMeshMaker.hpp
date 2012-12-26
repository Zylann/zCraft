/*
BlockMeshMaker.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZCRAFT_BLOCKMESHMAKER_HPP_INCLUDED
#define ZCRAFT_BLOCKMESHMAKER_HPP_INCLUDED

#include "engine/opengl/VertexColorArray.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
	/*
		A BlockMeshMaker constructs displayable and optimized meshes
		out of map nodes blocks.
	*/

	class BlockMeshMaker
	{
		struct FastFace
		{
			Vector3f vertices[4];
			u8 colors[16] = {255}; // r, g, b, a
			sf::Texture * texture = nullptr;
		};

	public :

		engine::gl::VertexColorArray * makeMesh(
			const Vector3i bpos, VoxelBuffer & vb);

	private :

		// fetch a row of blocks on a voxel stamp to convert them into fastfaces
		// Note : tessellation algorithm is here
		void updateFastFacesRow(
			Vector3i startPos, // absolute start position
			Vector3i transDir, // iteration translation
			Vector3i vFaceDir, // face direction vector, ex : (0,0,1) for back face (z+)
			const u8 dir, // direction constant
			const u16 length, // usually CHUNK_SIZE
			VoxelBuffer & vb, // voxels to analyse (may contain neighboring)
			std::list<FastFace> & faces);

		// sets parameters of a FastFace.
		// light in [0,255] (not a lightCode)
		// shift : if true, the face will be shifted of (-vFaceDir).
		void updateFastFace(
			FastFace & ff, // the fastface to set
			sf::Texture * tex,
			u8 light, // light shade (for differenciating sides)
			Vector3f pos, // face absolute origin
			Vector3i vFaceDir, // direction vector
			bool shift,
			Vector3f scale); // scale of the face (integer)

		// get light shading of a face (to make differences between sides)
		u8 getFaceLight(const Vector3i & vdir, u8 lightCode);

		u8 compareFaces(const Node a, const Node b);

		void getFaceVerticesFromDirVector(
			Vector3i vDir, Vector3f vertices[4]);

	};

} // namespace zcraft

#endif // ZCRAFT_BLOCKMESHMAKER_HPP_INCLUDED





