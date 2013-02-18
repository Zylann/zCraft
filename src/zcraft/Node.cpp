#include "zcraft/Node.hpp"
#include "zcraft/NodeProperties.hpp"

namespace zcraft
{
	// TODO Node: rename Voxel

	Node::Node(u8 type0, u8 metaType0, u8 light0)
	{
		type = type0;
		meta = ((metaType0 << 4) & 0xf0) | (light0 & 0x0f);
	}

	const NodeProperties & Node::properties() const
	{
		return NodeProperties::get(type);
	}

	void Node::serialize(std::ostream & os) const
	{
        os.put(type);
        os.put(meta);
	}

	void Node::unserialize(std::istream & is)
	{
        type = is.get();
        meta = is.get();
	}

} // namespace zcraft

