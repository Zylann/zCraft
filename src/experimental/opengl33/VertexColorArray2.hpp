/*
VertexColorArray.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXPERIMENTAL_GL_VERTEXCOLORARRAY_HPP_INCLUDED
#define EXPERIMENTAL_GL_VERTEXCOLORARRAY_HPP_INCLUDED

#include "engine/core/Array.hpp"
#include "opengl3.hpp"

namespace experimental
{
namespace gl
{
	/*
		Array living on the graphics card that holds vertex and color data.
		It's a basic way to render colored shapes using VBOs.
	*/

	class VertexColorArray
	{
	private :

		// Data to send to the graphics card. Empty once hosted.
		zn::Array<zn::f32> m_vertices;
		zn::Array<zn::u8> m_colors;

		// Metadata
		GLuint m_bufferID = 0;
		GLenum m_primitiveType = 0;
		zn::u32 m_vertexCount = 0;
		zn::u32 m_valuesPerVertex = 0;
		zn::u32 m_valuesPerColor = 0;
		zn::u32 m_verticesOffset = 0;
		zn::u32 m_colorsOffset = 0;

	public :

		// Creates an empty array
		VertexColorArray();

		// Destroys the array and hosted data
		~VertexColorArray();

		// Transfers vertices from the given array to this array.
		// Returns false if given parameters are wrong.
		bool moveVertices(zn::Array<zn::f32> & vertices, const zn::u32 valuesPerVertex = 3);

		// Transfers colors from the given array to this array
		// Returns false if given parameters are wrong.
		bool moveColors(zn::Array<zn::u8> & colors, const zn::u32 valuesPerColor = 3);

		// Clears the array and hosted data
		void clear();

		// Sets the primitive that will be used for drawing.
		// The data must comply with it.
		void setPrimitiveType(GLuint t);

		// Hosts data on the graphics card if not already done, and draws the VBO
		void draw();

		// Tests if the data is hosted on the graphic card
		inline bool isHosted() { return m_bufferID != 0; }

	private :

		// Hosts the data to the graphics card and clears local data
		// (because it would be duplicated and so useless).
		void host();

	};

} // namespace gl
} // namespace experimental

#endif // EXPERIMENTAL_GL_VERTEXCOLORARRAY_HPP_INCLUDED


