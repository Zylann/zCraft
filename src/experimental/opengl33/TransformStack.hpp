#ifndef ENGINE_TRANSFORMSTACK_HPP_INCLUDED
#define ENGINE_TRANSFORMSTACK_HPP_INCLUDED

#include <stack>
#include "Matrix4.hpp"

namespace experimental
{
	class TransformStack
	{
	public :

		void push();

		void pop();

		void reset();

		void set(const Matrix4 & m);

		void translate(const float x, const float y, const float z);

		void scale(const float sxyz);

		void scale(const float sx, const float sy, const float sz);

		void rotate(const float a, float ax, float ay, float az);

		inline const Matrix4 & getMatrix() const { return m_matrix; }

	private :

		Matrix4 m_op1; // Used for operations
		Matrix4 m_op2; // Used for operations
		Matrix4 m_matrix; // Transformation matrix
		std::stack<Matrix4> m_stack;

	};

} // namespace experimental

#endif // ENGINE_TRANSFORMSTACK_HPP_INCLUDED
