#include "engine/Array3D.hpp"
#include "zcraft/VoxelBuffer.hpp"

namespace zcraft
{
    VoxelBuffer::VoxelBuffer() : zn::Array3D<Node>()
    {}

    VoxelBuffer::~VoxelBuffer()
    {}

    void VoxelBuffer::printDataItem(std::ostream & os, Node & item) const
    {
        os << 0;
    }

} // namespace zcraft

