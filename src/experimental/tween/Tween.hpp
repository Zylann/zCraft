#ifndef TWEEN_HPP_INCLUDED
#define TWEEN_HPP_INCLUDED

#include "engine/Array.hpp"

namespace experimental
{
	template <unsigned int key_size>
	class Tween
	{
	private :

		engine::Array<std::array<float,key_size>> m_keys;

	public :

		Tween();
		~Tween() {};


	};

} // namespace experimental

#endif // TWEEN_HPP_INCLUDED
