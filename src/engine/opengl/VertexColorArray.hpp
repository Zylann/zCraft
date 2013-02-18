/*
VertexColorArray.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_GL_VERTEXCOLORARRAY_HPP_INCLUDED
#define ENGINE_GL_VERTEXCOLORARRAY_HPP_INCLUDED

#include "engine/Array.hpp"
#include "engine/opengl/opengl.hpp"

namespace zn
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
		Array<f32> m_vertices;
		Array<u8> m_colors;

		// Metadata
		GLuint m_bufferID = 0;
		GLenum m_primitiveType = 0;
		u32 m_vertexCount = 0;
		u32 m_valuesPerVertex = 0;
		u32 m_valuesPerColor = 0;
		u32 m_verticesOffset = 0;
		u32 m_colorsOffset = 0;

	public :

		// Creates an empty array
		VertexColorArray();

		// Destroys the array and hosted data
		~VertexColorArray();

		// Transfers vertices from the given array to this array.
		// Returns false if given parameters are wrong.
		bool moveVertices(Array<f32> & vertices, const u32 valuesPerVertex = 3);

		// Transfers colors from the given array to this array
		// Returns false if given parameters are wrong.
		bool moveColors(Array<u8> & colors, const u32 valuesPerColor = 3);

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
} // namespace zn

#endif // ENGINE_GL_VERTEXCOLORARRAY_HPP_INCLUDED


