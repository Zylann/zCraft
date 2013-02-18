/*
Matrix4.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MATRIX4_HPP_INCLUDED
#define MATRIX4_HPP_INCLUDED

#include "engine/Vector3.hpp"

namespace experimental
{
	class Matrix4
	{
	public :

		Matrix4();

		Matrix4(const Matrix4 & other);

		Matrix4(const float values[16]);

		void set(const Matrix4 & other);

		void set(const float values[16]);

		float getCell(unsigned int row, unsigned int col);

		void setCell(unsigned int row, unsigned int col, float v);

		// Sets the matrix to identity
		void loadIdentity();

		// Sets the matrix to a 3D perspective projection matrix
		void loadPerspectiveProjection(
			const float fov, const float ratio,
			const float near, const float far);

		void loadOrtho2DProjection(
			const float left, const float top,
			const float right, const float bottom);

		void loadLookAt(
			const zn::Vector3f & eye,
			const zn::Vector3f & target,
			const zn::Vector3f & up);

		// Sets the matrix to a translation matrix.
		void loadTranslation(const float vx, const float vy, const float vz);

		// Sets the matrix to a rotation matrix.
		// The rotation is defined from an angle around an axis.
		void loadRotation(const float t, const float x, const float y, const float z);

		// Sets the matrix to a scaling matrix
		void loadScale(const float sx, const float sy, const float sz);

		// Sets the matrix to the result of the product of the given matrices
		void setByProduct(const Matrix4 & a, const Matrix4 & b);

		// Sets the matrix to the result of the product of the given matrices,
		// as if they were 3x3.
		void setByProductAs3(const Matrix4 & a, const Matrix4 & b);

		inline const float * values() const { return m_v; }

		void operator=(const Matrix4 & other);

	private :

		inline const float operator[](const int i) const { return m_v[i]; }

		//  0   1   2   3
		//  4   5   6   7
		//  8   9  10  11
		// 12  13  14  15
		float m_v[16];
	};

} // namespace experimental

#endif // MATRIX4_HPP_INCLUDED
