#ifndef CARTOGRAPHER_HPP_INCLUDED
#define CARTOGRAPHER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "zcraft/common.hpp"
#include "zcraft/BlockMap.hpp"
#include "zcraft/cartographer/Cartography.hpp"

namespace zcraft
{
	class Cartographer
	{
	public :

		static const s32 MAX_SIZE_BLOCKS = 256;

	public :

		static void renderTopDown(
			BlockMap & map, Cartography & cart,
			Vector2i min, Vector2i max, s32 minZ, s32 maxZ);

		static sf::Image renderChunkTopDown(
			BlockMap & map, s32 bx, s32 by, s32 minZ, s32 maxZ);

		static void renderWorldToFile(
			const std::string worldDir, const std::string filename);

	};

} // namespace zcraft


#endif // CARTOGRAPHER_HPP_INCLUDED
