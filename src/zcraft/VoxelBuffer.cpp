#include "engine/core/ShiftArray3D.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
    VoxelBuffer::VoxelBuffer() : zn::ShiftArray3D<Voxel>()
    {}

    VoxelBuffer::~VoxelBuffer()
    {}

    void VoxelBuffer::printDataItem(std::ostream & os, Voxel & item) const
    {
        os << 0;
    }

} // namespace zcraft

