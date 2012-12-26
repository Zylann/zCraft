#ifndef NODEPROPERTIES_HPP_INCLUDED
#define NODEPROPERTIES_HPP_INCLUDED

#include <string>
#include "zcraft/common.hpp"
#include "engine/opengl/Color.hpp"

namespace zcraft
{
	struct NodeProperties
	{
		bool cube;
		bool opaque;
		std::string name;
		engine::Color color;

		NodeProperties()
		{
			cube = true;
			opaque = true;
		}

		inline bool isOpaqueCube() const
		{
			return cube && opaque;
		}

		static void initList();

		static void freeList();

		static const NodeProperties & get(u8 type);

	};

} // namespace zcraft

#endif // NODEPROPERTIES_HPP_INCLUDED
