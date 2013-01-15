#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <iostream>
#include "zcraft/common.hpp"

namespace zcraft
{
	namespace node
	{
		/** Basic types **/

		enum NodeType
		{
			AIR = 0,
			STONE,
			DIRT,
			GRASS,

			TYPE_COUNT // Keep last
		};

		/** Meta-types **/

		enum AirTypes
		{
			AIR_NORMAL = 0,
			AIR_UNLOADED
		};

	}

	struct NodeProperties;

	/// Nodes are the basis of maps.
	/// They consist on voxels.

	struct Node
	{
		// Constants

		static const u8 LIGHT_MIN = 0x2; // Not zero, otherwise we can't see nothing
		static const u8 LIGHT_MAX = 0xf;

		// Attributes

		u8 type; // 8 bits for type
		u8 meta; // 4 higher bits for metadata, 4 lower bits for light

		// Methods

		// Constructs an empty air block.
		Node(u8 type0 = node::AIR, u8 metaType0 = 0x0, u8 light0 = LIGHT_MAX);

		// Gets the common properties of the block
		const NodeProperties & properties() const;

		// Writes the node in a binary stream
		void serialize(std::ostream & os) const;

		// Reads the node from a binary stream
		void unserialize(std::istream & is);

		// Gets the light code of the node, between LIGHT_MIN and LIGHT_MAX.
		// (Must be converted for drawing in 0-255 range)
		inline u8 getLight() const
		{
			return meta & 0x0f;
		}

	};

	struct LocatedNode
	{
		Node node;
		Vector3i pos;
	};

} // namespace zcraft

#endif // NODE_HPP_INCLUDED



