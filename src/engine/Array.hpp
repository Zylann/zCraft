/*
Array.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_ARRAY_HPP_INCLUDED
#define ENGINE_ARRAY_HPP_INCLUDED

#include <iostream> // originally for debug
#include "engine/types.hpp"

namespace engine
{
	/*
		Fixed-size dynamic array.
		Fixed-size because it doesn't support resizing and it only allocates
		the amount of memory we want (no "capacity" pre-allocation).
		Dynamic because we can however clear and recreate it without
		having to delete the object.
	*/

	template <typename T>
	class Array
	{
	private :

		T * m_data = nullptr;
		u32 m_size = 0;

	public :

		Array()
		{}

		Array(const u32 size)
		{
			create(size);
		}

		Array(const u32 size, const T fillValue)
		{
			create(size, fillValue);
		}

		Array(const Array & other)
		{
			copyFrom(other);
		}

		// TODO Array: support for initializer lists

		~Array()
		{
			clear();
		}

		void clear()
		{
			if(m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_size = 0;
		}

		void create(const u32 size)
		{
			clear();
			m_size = size;
			m_data = new T[m_size];
		}

		void create(const u32 size, const T fillValue)
		{
			create(size);
			fill(fillValue);
		}

		void copyFrom(const Array & other)
		{
			create(other.size());
			memcpy(m_data, other.m_data, m_size * sizeof(T));
		}

		void moveFrom(Array & other)
		{
			clear();
			m_data = other.m_data;
			m_size = other.m_size;
			other.m_data = nullptr;
			other.m_size = 0;
		}

		void swap(Array & other)
		{
			T * tempData = m_data;
			u32 tempSize = m_size;

			m_data = other.m_data;
			m_size = other.m_size;

			other.m_data = tempData;
			other.m_size = tempSize;
		}

		void fill(const T fillValue)
		{
			// TODO Array: maybe use memset for native number types?
			for(u32 i = 0; i < m_size; i++)
				m_data[i] = fillValue;
		}

		inline T & operator[](const u32 i)
		{
			return m_data[i];
		}

		// TODO Array: operator=

		inline const T & get(const u32 i) const
		{
			return m_data[i];
		}

		inline u32 size() const
		{
			return m_size;
		}

		inline u32 elementSize() const
		{
			return sizeof(T);
		}

		inline u32 dataSize() const
		{
			return size() * elementSize();
		}

		// Provides read-only access to raw array data
		inline const T * raw() const
		{
			return m_data;
		}

	};

} // namespace engine

#endif // ENGINE_ARRAY_HPP_INCLUDED



