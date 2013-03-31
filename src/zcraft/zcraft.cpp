#include "zcraft/demos/FlatMapViewer.hpp"
#include "zcraft/demos/PerspectiveMapViewer.hpp"
#include "zcraft/cartographer/Cartographer.hpp"
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

	int launchFlatMapViewer()
	{
		return runGame(new zcraft::FlatMapViewer(800, 600));
	}

	int launchPerspectiveMapViewer()
	{
		return runGame(new zcraft::PerspectiveMapViewer(800, 600));
	}

	struct ScopedInit
	{
		ScopedInit() { zcraft::init(); }
		~ScopedInit() { zcraft::free(); }
	};

	int shell(int argc, char * argv[])
	{
		ScopedInit zci;

		if(argc < 2)
		{
			std::cout << "No commands given, default program will be executed." << std::endl;
			return launchPerspectiveMapViewer();
		}

		std::string args[argc];
		for(int i = 0; i < argc; i++)
			args[i] = argv[i];

		if(args[1] == "-cart") // Cartographer
		{
			std::string worldDir;
			if(argc == 2)
			{
				std::cout << "World dir: ";
				std::cin >> worldDir;
			}
			else if(argc == 3)
				worldDir = args[2];
			else
			{
				std::cout << "Too much arguments." << std::endl;
				return 0;
			}

			if(!worldDir.empty())
			{
				zcraft::Cartographer::renderWorldToFile(worldDir, "world.png");
			}
			else
				std::cout << "Dir name is empty : abort." << std::endl;
		}
		else if(args[1] == "-fmv") // FlatMapViewer
		{
			return launchFlatMapViewer();
		}

		return 0;
	}

} // namespace zcraft

