#ifndef ZCRAFT_HPP_INCLUDED
#define ZCRAFT_HPP_INCLUDED

#include "zcraft/common.hpp"
#include "zcraft/BlockMap.hpp"
#include "zcraft/VoxelProperties.hpp"

namespace zcraft
{
	// Initializes zcraft (called by the shell)
	void init();

	// De-initializes zcraft (called by the shell)
	void free();

	// Runs the zCraft shell
	int shell(int argc, char * argv[]);

} // namespace zcraft

#endif // ZCRAFT_HPP_INCLUDED
