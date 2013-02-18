/*
Area3D.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/Area3D.hpp"
#include "engine/stringutils.hpp"

namespace zn
{
    Area3D::Area3D()
    {
    }

    Area3D::Area3D(const Vector3i & newSize)
    {
        setSize(newSize);
    }

    Area3D::Area3D(const Vector3i & newPos, const Vector3i & newSize)
    {
        setPosition(newPos);
        setSize(newSize);
    }

    void Area3D::setSize(const Vector3i & newSize)
    {
        m_size.x = newSize.x >= 0 ? newSize.x : 0;
        m_size.y = newSize.y >= 0 ? newSize.y : 0;
        m_size.z = newSize.z >= 0 ? newSize.z : 0;
    }

    void Area3D::setBounds(const Vector3i & minEdge, const Vector3i & maxEdge)
    {
        setSize(maxEdge - minEdge + Vector3i(1,1,1));
        setPosition(minEdge);
    }

    bool Area3D::contains(const Vector3i & pos) const
    {
        return containsRelative(pos - m_pos);
    }

    bool Area3D::containsRelative(const Vector3i & pos) const
    {
        return pos.x >= 0 &&
               pos.y >= 0 &&
               pos.z >= 0 &&
               pos.x < m_size.x &&
               pos.y < m_size.y &&
               pos.z < m_size.z;
    }

    Vector3i Area3D::getMinEdge() const
    {
        return m_pos;
    }

    Vector3i Area3D::getMaxEdge() const
    {
        return m_pos + m_size - Vector3i(1,1,1);
    }

    void Area3D::clear()
    {
        m_size.x = 0;
        m_size.y = 0;
        m_size.z = 0;

        m_pos.x = 0;
        m_pos.y = 0;
        m_pos.z = 0;
    }

    void Area3D::correct()
    {
        if(m_size.x < 0) m_size.x = 0;
        if(m_size.y < 0) m_size.y = 0;
        if(m_size.z < 0) m_size.z = 0;
    }

    void Area3D::expand(int px, int py, int pz)
    {
        m_size.x += 2 * px;
        m_size.y += 2 * py;
        m_size.z += 2 * pz;

        m_pos.x -= px;
        m_pos.y -= py;
        m_pos.z -= pz;

        correct();
    }

    bool Area3D::contains(const Area3D & other) const
    {
        return m_pos.x <= other.m_pos.x &&
               m_pos.y <= other.m_pos.y &&
               m_pos.z <= other.m_pos.z &&
               m_pos.x + m_size.x >= other.m_pos.x + other.m_size.x &&
               m_pos.y + m_size.y >= other.m_pos.y + other.m_size.y &&
               m_pos.z + m_size.z >= other.m_pos.z + other.m_size.z ;
    }

    std::string Area3D::toString() const
    {
    	std::stringstream ss;
    	ss << "{size=" << m_size.toString() << " pos=" << m_pos << "}";
    	return ss.str();
    }

    int Area3D::getVolume() const
    {
        return m_size.x * m_size.y * m_size.z;
    }

    int Area3D::index(const Vector3i & p_pos) const
    {
        return relativeIndex(p_pos - m_pos);
    }

    int Area3D::relativeIndex(const Vector3i & p_pos) const
    {
        return p_pos.z * m_size.y * m_size.x +
               p_pos.y * m_size.x +
               p_pos.x;
    }

} // namespace zn

