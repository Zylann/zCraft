#include "engine/core/ShiftArray3D.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
    VoxelBuffer::VoxelBuffer() : zn::ShiftArray3D<Voxel>()
    {}

    VoxelBuffer::~VoxelBuffer()
    {}

} // namespace zcraft

