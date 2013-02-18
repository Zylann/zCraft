#include "zcraft/zcraft.hpp"

namespace zcraft
{
	bool s_initialized = false;

	void init()
	{
		if(!s_initialized)
		{
			std::cout << "zcraft::init..." << std::endl;
			VoxelProperties::initList();
			s_initialized = true;
		}
		else
		{
			std::cout << "WARNING: zcraft::init called twice."
				<< " Second call is ignored." << std::endl;
		}
	}

	void free()
	{
		if(s_initialized)
		{
			std::cout << "zcraft::free..." << std::endl;
			VoxelProperties::freeList();
			s_initialized = false;
		}
		else
		{
			std::cout << "WARNING: zcraft::free called twice."
				<< " Second call is ignored." << std::endl;
		}
	}

} // namespace zcraft

