#include "zcraft/Voxel.hpp"
#include "zcraft/VoxelProperties.hpp"

namespace zcraft
{
	// TODO Voxel: rename Voxel

	Voxel::Voxel(u8 type0, u8 metaType0, u8 light0)
	{
		type = type0;
		meta = ((metaType0 << 4) & 0xf0) | (light0 & 0x0f);
	}

	const VoxelProperties & Voxel::properties() const
	{
		return VoxelProperties::get(type);
	}

	void Voxel::serialize(std::ostream & os) const
	{
        os.put(type);
        os.put(meta);
	}

	void Voxel::unserialize(std::istream & is)
	{
        type = is.get();
        meta = is.get();
	}

} // namespace zcraft

