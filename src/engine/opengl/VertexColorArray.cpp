/*
VertexColorArray.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include "engine/opengl/VertexColorArray.hpp"
#include "engine/opengl/opengl.hpp"

#define BUFFER_OFFSET(a) ((char*)nullptr + (a))

namespace zn
{
namespace gl
{
	VertexColorArray::VertexColorArray()
	{}

	VertexColorArray::~VertexColorArray()
	{
		clear();
	}

	bool VertexColorArray::moveVertices(
			Array<f32> & vertices, const u32 valuesPerVertex)
	{
		if(valuesPerVertex < 2 || valuesPerVertex > 3)
		{
			std::cout << "ERROR: VertexColorArray::moveVertices: "
				<< "invalid value : valuesPerVertex=" << valuesPerVertex << std::endl;
			return false;
		}

		if(vertices.size() % valuesPerVertex != 0)
		{
			std::cout << "ERROR: VertexColorArray::moveVertices: "
				<< "array size (" << vertices.size() << ") "
				<< "is not multiple of " << valuesPerVertex << std::endl;
			return false;
		}

		m_vertices.moveFrom(vertices);
		m_valuesPerVertex = valuesPerVertex;
		m_vertexCount = m_vertices.size() / m_valuesPerVertex;
		return true;
	}

	bool VertexColorArray::moveColors(
			Array<u8> & colors, const u32 valuesPerColor)
	{
		if(valuesPerColor == 0 || valuesPerColor > 4)
		{
			std::cout << "ERROR: VertexColorArray::moveColors: "
				<< "invalid value : valuesPerColor=" << valuesPerColor << std::endl;
			return false;
		}

		if(colors.size() % valuesPerColor != 0)
		{
			std::cout << "ERROR: VertexColorArray::moveColors: "
				<< "array size (" << colors.size() << ") "
				<< "is not multiple of " << valuesPerColor << std::endl;
			return false;
		}

		m_colors.moveFrom(colors);
		m_valuesPerColor = valuesPerColor;
		return true;
	}

	void VertexColorArray::clear()
	{
		m_vertices.clear();
		m_colors.clear();

		if(isHosted())
		{
			glDeleteBuffers(1, &m_bufferID);
		}
	}

	void VertexColorArray::setPrimitiveType(GLuint t)
	{
		m_primitiveType = t;
	}

	void VertexColorArray::draw()
	{
	#if defined ZN_OPENGL2 //{

		if(!isHosted()) // Not hosted
			host();
		else if(m_vertices.size() != 0) // Hosted, but updated
			host();

		// Start using our buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

		// Use vertex data
		glVertexPointer(
			m_valuesPerVertex, // How many values per vertex
			GL_FLOAT, // Vertex value type
			0, // Stride
			BUFFER_OFFSET(m_verticesOffset));

		// Use color data
		glColorPointer(
			m_valuesPerColor, // How many values per color
			GL_UNSIGNED_BYTE, // Color value type
			0, // Stride
			BUFFER_OFFSET(m_colorsOffset));

		// Start using VBOs
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// Draw stuff
		glDrawArrays(m_primitiveType, 0, m_vertexCount);

		// End using VBOs
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	//} ZN_OPENGL2
	#elif defined ZN_OPENGL3

		#error "This file doesn't supports OpenGL 3"

	#endif // ZN_OPENGL3
	}

	void VertexColorArray::host()
	{
		// Note : this code is the same for OpenGL 2 and 3

		if(m_vertices.size() == 0 || m_colors.size() == 0)
			return; // Nothing to host

		if(isHosted()) // Already hosted?
			glDeleteBuffers(1, &m_bufferID); // Delete old data

		//std::cout << "Hosting VBO..." << std::endl;

		const u32 verticesDataSize = m_vertices.byteCount();
		const u32 colorsDataSize = m_colors.byteCount();

		m_verticesOffset = 0; // At the beginning
		m_colorsOffset = verticesDataSize; // After vertices

		// Create VBO
		glGenBuffers(1, &m_bufferID);

		// Start using our VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

		// Allocate memory
		glBufferData(
			GL_ARRAY_BUFFER,
			verticesDataSize + colorsDataSize,
			nullptr,
			GL_STREAM_DRAW);

		// Store vertex data
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0, // VBO's data start adress
			verticesDataSize, // data size
			m_vertices.raw()); // data address

		// Store color data
		glBufferSubData(
			GL_ARRAY_BUFFER,
			verticesDataSize, // After vertices
			colorsDataSize,
			m_colors.raw());

		// Unbind the buffer as we finished to host data
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Now local data is useless
		m_vertices.clear();
		m_colors.clear();
	}

} // namespace gl
} // namespace zn



