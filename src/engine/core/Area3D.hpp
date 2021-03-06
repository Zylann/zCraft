/*
Area3D.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef AREA3D_HPP_INCLUDED
#define AREA3D_HPP_INCLUDED

#include "engine/core/types.hpp"
#include "engine/core/Vector3.hpp"

namespace zn
{
	/*
		Area3D represents an orthogonal discrete space area
		defined by a size and a position.
	*/

    class Area3D
    {
	public :

		Area3D();

		// constructs the area from a size. Position is (0,0).
		Area3D(const Vector3i & newSize);
		Area3D(u32 sizeX, u32 sizeY, u32 sizeZ);

		// constructs the area from a position and a size.
		Area3D(const Vector3i & newPos, const Vector3i & newSize);

		// get area's size
		inline const Vector3i & getSize() const { return m_size; }

		// get area's position
		inline const Vector3i & getPosition() const { return m_pos; }

		// sets area's position
		void setPosition(const Vector3i & newPos) { m_pos = newPos; }

		// sets area's size, with checking (no negative values)
		void setSize(const Vector3i & newSize);
		void setSize(u32 x, u32 y, u32 z);

		// sets area's size from minimum and maximum edges
		void setBounds(const Vector3i & minEdge, const Vector3i & maxEdge);

		// tells if a point is included in the area
		bool contains(const Vector3i & pos) const;

		// tells if a point is included in the area without look the position
		bool containsRelative(const Vector3i & pos) const;

		// get minimum edge
		Vector3i getMinEdge() const;

		// get maximum edge
		Vector3i getMaxEdge() const;

		inline s32 minX() const { return m_pos.x; }
		inline s32 minY() const { return m_pos.y; }
		inline s32 minZ() const { return m_pos.z; }
		inline s32 maxX() const { return m_pos.x + m_size.x - 1; }
		inline s32 maxY() const { return m_pos.y + m_size.y - 1; }
		inline s32 maxZ() const { return m_pos.z + m_size.z - 1; }

		// resets the area
		void clear();

		// prevents the area to be defined with negative size
		void correct();

		// expands or reduce the area's size
		void expand(int px, int py, int pz);

		// tells if another Area3D is included in the area
		// it will return false if the other is
		bool contains(const Area3D & other) const;

		// converts area's information into a string
		std::string toString() const;

		// get area's volume (always >= 0)
		int getVolume() const;

		inline bool empty() const { return m_size.x == 0 && m_size.y == 0 && m_size.z == 0; }

		/*
			These functions below are used with 3D buffers using linear data storage.
		*/

		// get linear index using the position
		int index(const Vector3i & p_pos) const;
		int index(s32 x, s32 y, s32 z) const;

		// get linear index without use the position
		int relativeIndex(const Vector3i & p_pos) const;
		int relativeIndex(s32 x, s32 y, s32 z) const;

	private :

		Vector3i m_size;
		Vector3i m_pos;

    };

} // namespace zn


#endif // AREA3D_HPP_INCLUDED
