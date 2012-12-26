#ifndef MAPGENERATOR_HPP_INCLUDED
#define MAPGENERATOR_HPP_INCLUDED

#include "zcraft/Block.hpp"

namespace zcraft
{
	class MapGenerator
	{
	private :

		u32 m_seed;

	public :

		MapGenerator(u32 seed = 131183);

		Block * makeBlock(Vector3i pos);

	};

} // namespace zcraft

#endif // MAPGENERATOR_HPP_INCLUDED
