/*
Array3D.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_ARRAY3D_HPP_INCLUDED
#define ENGINE_ARRAY3D_HPP_INCLUDED

#include <ostream>
#include <cstring>
#include <iostream>

#include "engine/Area3D.hpp"
#include "engine/Exception.hpp"

namespace engine
{
    /*
        3D data defined by a width, a height, a depth and a position (Area3D).
        Note : this is not a basic array because positions can be offset.
    */

    template <typename T>
    class Array3D
    {
	private :

		T * m_data = nullptr;	// linear data storage (NULL if empty)
		Area3D m_area;	// size and position

	public :

		// creates an empty buffer
		Array3D()
		{}

		// creates a buffer with the specified area
		Array3D(const Area3D & area)
		{
			create(area);
		}

		// creates a buffer from another (copy)
		Array3D(const Array3D & other)
		{
			clear();
			m_area = other.m_area;
			create(m_area);
			memcpy(m_data, other.m_data, m_area.getVolume() * sizeof(T));
		}

		~Array3D()
		{
			clear();
		}

		// creates the buffer from the specified area.
		// old data is cleared.
		// Note : data values are not initialized, use the fill() function is necessary.
		void create(const Area3D & area)
		{
			// Check if the given area is correct
			if(area.getVolume() <= 0)
				std::cout << "WARNING: Array3D::create received empty area ("
						<< area.getVolume() << ")" << std::endl;

			// Delete old data
			if(m_data != nullptr)
				delete[] m_data;

			// Allocate memory
			m_area = area;
			m_data = new T[m_area.getVolume()];
		}

		// same as create(Area3D), with an additionnal parameter for default values
		void create(const Area3D & area, const T & defaultValue)
		{
			create(area);
			fill(defaultValue);
		}

		// clears the buffer
		void clear()
		{
			if(m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
				m_area.clear();
			}
		}

		// fills the buffer with the same value
		void fill(const T & val)
		{
			const int vol = m_area.getVolume();
			for(int i = 0; i < vol; i++)
				m_data[i] = val;
			// TODO Array3D: maybe use memset?
		}

		const Area3D & getArea() const
		{
			return m_area;
		}

		/*
			3D-data copy optimization :
			In copyTo and copyFrom, we do iteration on Z and Y dimensions.
			For X, we just have a linear copy to do, so for performance improvement
			we use memcpy to do a binary copy from an index to another,
			because data is stored in a linear buffer.
			It's faster than do a classic for.
		*/

		// Copy data from a source buffer bounded by an area.
		// The source area must be included in the destination area.
		void copyFrom(const T srcData[], const Area3D & srcArea)
				throw(Exception)
		{
			if(!m_area.contains(srcArea))
				throw Exception(
					"Array3D::copyFrom m_area=" + m_area.toString() +
					" srcArea=" + srcArea.toString());

			Vector3i pos;
			int i_src, i_dst;

			for(pos.z = 0; pos.z < srcArea.getSize().z; pos.z++)
			for(pos.y = 0; pos.y < srcArea.getSize().y; pos.y++)
			{
				i_src = srcArea.relativeIndex(pos);
				i_dst = m_area.index(pos + srcArea.getPosition());
				memcpy(&m_data[i_dst], &srcData[i_src], srcArea.getSize().x * sizeof(T));
			}
		}

		// Copy data from the buffer to a destination buffer bounded by an area.
		// The source area must be included in the destination area.
		void copyTo(const T dstData[], const Area3D & dstArea) const
				throw(Exception)
		{
			if(!dstArea.contains(m_area))
				throw Exception(
					"Array3D::copyTo m_area=" + m_area.toString() +
					" dstArea=" + dstArea.toString());

			Vector3i pos;
			int i_src, i_dst;

			for(pos.z = 0; pos.z < m_area.getSize().z; pos.z++)
			for(pos.y = 0; pos.y < m_area.getSize().y; pos.y++)
			{
				i_dst = dstArea.index(pos + m_area.getPosition());
				i_src = m_area.relativeIndex(pos);
				memcpy(&dstData[i_dst], &m_data[i_src], m_area.getSize().x * sizeof(T));
			}
		}

		// get an element without position validation (it must be valid !)
		inline T getNoEx(const Vector3i & pos) const
		{
			return m_data[m_area.index(pos)];
		}

		// get an element
		T get(const Vector3i & pos) const
				throw(Exception)
		{
			if(m_area.contains(pos))
				return getNoEx(pos);
			else
				throw Exception("Array3D::get " + pos);
		}

		// set an element without position validation (it must be valid !)
		inline void setNoEx(const Vector3i & pos, const T & value)
		{
			m_data[m_area.index(pos)] = value;
		}

		// set an element
		void set(const Vector3i & pos, const T & value)
				throw(Exception)
		{
			if(m_area.contains(pos))
				setNoEx(pos, value);
			else
				throw Exception("Array3D::set " + pos);
		}

		// Prints buffer description in an output stream (for debug purposes).
		// Note : very large buffers should not be printed, it would create
		// lines and lines of data (not very useful).
		void print(std::ostream & os) const
		{
			os << "=========== Array3D ==========" << std::endl;
			os << "m_area = " << m_area.toString() << std::endl;
			os << "m_data =" << std::endl;

			Vector3i pos;
			int i;

			for(pos.z = 0; pos.z < m_area.getSize().z; pos.z++)
			{
				os << "Layer Z=" << pos.z << " :" << std::endl;

				for(pos.y = 0; pos.y < m_area.getSize().y; pos.y++)
				{
					os << " ";
					for(pos.x = 0; pos.x < m_area.getSize().x; pos.x++)
					{
						i = m_area.index(pos);
						printDataItem(os, m_data[i]);
					}
					os << std::endl;
				}
			}
			os << "===============================" << std::endl;
		}

		// defines the way an item must be printed
		virtual void printDataItem(std::ostream & os, T & item) const
		{
			//os << item;
			os << "O";
		}

    }; // class Array3D

} // namespace util

#endif // ENGINE_ARRAY3D_HPP_INCLUDED
