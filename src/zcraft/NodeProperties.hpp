#ifndef NODEPROPERTIES_HPP_INCLUDED
#define NODEPROPERTIES_HPP_INCLUDED

#include <string>
#include "zcraft/common.hpp"
#include "engine/Color.hpp"

namespace zcraft
{
	class NodeProperties
	{
	public :

		bool cube; // Is the node a cube?
		bool opaque; // Is the node opaque?
		bool solid; // Is the node solid (collisions) ?
		std::string name; // Technical name
		std::string displayableName; // Player-displayed name
		zn::Color averageColor; // Average color (used for minimap)
		zn::Color color; // Override color

	public :

		// Creates an opaque white cube
		NodeProperties()
		{
			cube = true;
			opaque = true;
			color.set(255,255,255,255);
			averageColor.set(color);
			name = "undefined";
			displayableName = "undefined";
			solid = false;
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
