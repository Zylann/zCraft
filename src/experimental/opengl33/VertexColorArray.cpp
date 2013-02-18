/*
VertexColorArray.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <iostream>
#include "VertexColorArray.hpp"

#define BUFFER_OFFSET(a) ((char*)nullptr + (a))

using namespace engine;

namespace experimental
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
		if(!isHosted()) // Not hosted
			host();
		else if(m_vertices.size() != 0) // Hosted, but updated
			host();

		// Start using our buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

		glEnableVertexAttribArray(ShaderIn::POSITION);
		glEnableVertexAttribArray(ShaderIn::COLOR);

		glVertexAttribPointer(
			ShaderIn::POSITION,
			m_valuesPerVertex,
			GL_FLOAT, // Vertex value type
			GL_FALSE, // Don't normalize
			0, // Stride
			BUFFER_OFFSET(m_verticesOffset));

		glVertexAttribPointer(
			ShaderIn::COLOR,
			m_valuesPerColor,
			GL_UNSIGNED_BYTE, // Color value type
			GL_FALSE, // Don't normalize
			0, // Stride
			BUFFER_OFFSET(m_colorsOffset));

		glDrawArrays(m_primitiveType, 0, m_vertexCount);

		glDisableVertexAttribArray(ShaderIn::POSITION);
		glDisableVertexAttribArray(ShaderIn::COLOR);
	}

	void VertexColorArray::host()
	{
		if(m_vertices.size() == 0 || m_colors.size() == 0)
			return; // Nothing to host

		if(isHosted()) // Already hosted?
			glDeleteBuffers(1, &m_bufferID); // Delete old data

		//std::cout << "Hosting VBO..." << std::endl;

		const u32 verticesDataSize = m_vertices.dataSize();
		const u32 colorsDataSize = m_colors.dataSize();

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
} // namespace experimental



