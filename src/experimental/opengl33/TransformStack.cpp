/*
TransformStack.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <cmath>
#include "TransformStack.hpp"
#include "engine/types.hpp"

using namespace engine;

namespace experimental
{
	void TransformStack::push()
	{
		m_stack.push(m_matrix);
	}

	void TransformStack::pop()
	{
		if(!m_stack.empty())
		{
			m_matrix = m_stack.top();
			m_stack.pop();
		}
	}

	void TransformStack::reset()
	{
		m_matrix.loadIdentity();
	}

	void TransformStack::set(const Matrix4 & m)
	{
		m_matrix.set(m);
	}

	void TransformStack::translate(const float x, const float y, const float z)
	{
		m_op1.loadTranslation(x, y, z);
		m_op2.set(m_matrix);
		m_matrix.setByProduct(m_op1, m_op2);
	}

	void TransformStack::scale(const float sxyz)
	{
		m_op1.loadScale(sxyz, sxyz, sxyz);
		m_op2.set(m_matrix);
		m_matrix.setByProduct(m_op1, m_op2);
	}

	void TransformStack::scale(const float sx, const float sy, const float sz)
	{
		m_op1.loadScale(sx, sy, sz);
		m_op2.set(m_matrix);
		m_matrix.setByProduct(m_op1, m_op2);
	}

	void TransformStack::rotate(const float a, float ax, float ay, float az)
	{
		const f32 r = sqrt(ax*ax + ay*ay + az*az);
		ax /= r;
		ay /= r;
		az /= r;
		m_op1.loadRotation(a, ax, ay, az);
		m_op2.set(m_matrix);
		m_matrix.setByProduct(m_op1, m_op2);
	}

} // namespace experimental

