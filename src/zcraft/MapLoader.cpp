/*
MapLoader.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <fstream>
#include <cstdlib>
#include "zcraft/MapLoader.hpp"
#include "engine/system/files/filesystem.hpp"
#include "engine/stringutils.hpp"

using namespace engine;

namespace zcraft
{
	/*
		Constants
	*/

	const std::string MapLoader::SAVES_DIR = "worlds";
	const std::string MapLoader::EXT = "block";

	/*
		Uility
	*/

	std::string coordToStringAlnum(s32 c)
	{
		return (c >= 0 ? 'p' : 'n') + toString(abs(c));
	}

	s32 stringAlnumToCoord(const std::string str)
	{
        if(str[0] == 'p')
            return toInt(str.substr(1));
        else if(str[0] == 'n')
            return - toInt(str.substr(1));
        else
            return 0;
	}

	/*
		MapLoader

		zcraft file structure spec 1.0 (2012/12/10)

		Blocks represent the files unit in binary format
		(see Block.cpp for serialization format).
		Each block can be accessed through the following pattern :

			../<worldName>/<x>/<y>/<z>.block

		coordinates x, y and z are written using their absolute value
		prepended by 'n' if negative, 'p' if positive. 0 is assumed positive.

		Examples :
			4 => p4
			-32 => n32
			0 => p0
		The block at (-42, 6, 0) of the world 'world0' has the following path :
			../world0/n42/p6/p0.block
	*/

	MapLoader::MapLoader(const std::string dir)
	{
		m_dir = dir;
	}

	Block * MapLoader::loadBlock(const Vector3i pos)
	{
		// Get block path from its coordinates
		const std::string path = getBlockPath(pos);

		// Open the block file
		std::ifstream ifs(path, std::ios::in|std::ios::binary);
		if(!ifs.good())
		{
			std::cout << "WARNING: MapLoader::loadBlock: \""
				<< path << "\" does not exist for block " << pos << std::endl;
			return nullptr;
		}

		// Create the block, load it and close the file
		Block * block = new Block(pos);
		block->unserialize(ifs);
		block->dirty = false; // The block will not be saved if not modified
		ifs.close();

		// Debug
		if(pos != block->getPosition() && pos.x == 26 && pos.y == -28 && pos.z == -4)
		{
			std::cout << "WARNING: MapLoader::loadBlock: "
				<< "block position and path-deduced position differ."
				<< " path=" << path
				<< ", read=" << block->getPosition() << std::endl;
		}

		//std::cout << "Loaded block " << block->getPosition() << std::endl;
		return block;
	}

	bool MapLoader::saveBlock(const Block * block)
	{
		// Check if the block is null
		if(block == nullptr)
		{
			std::cout << "ERROR: MapLoader::saveBlock: "
				<< "given block is null" << std::endl;
			return false;
		}

		// Get block file path from its coordinates
		const std::string path = getBlockPath(block->getPosition());

		// if the path not exists
        if(!fs::isPathExists(path))
        {
            // create directories
            if(!fs::makeAllDirs(path, true))
            {
                std::cout << "ERROR: MapLoader::saveBlock: "
					<< "an error occurred while creating directories of path '"
                    << path << "'" << std::endl;
                return false;
            }
        }

		// Open the output file
		std::ofstream ofs(path, std::ios::out|std::ios::trunc|std::ios::binary);
		if(!ofs.good())
		{
			std::cout << "ERROR: MapLoader::saveBlock: "
				<< "couldn't write block " << block->getPosition()
				<< "at \"" << path << "\"" << std::endl;
			return false;
		}

		// Write block and close the file
		block->serialize(ofs);
		ofs.close();

		//std::cout << "Saved block " << block->getPosition() << std::endl;
		return true;
	}

	std::string MapLoader::getBlockPath(const Vector3i pos)
	{
		fs::Path path(SAVES_DIR);

		path.append(m_dir);
		path.append(coordToStringAlnum(pos.x));
		path.append(coordToStringAlnum(pos.y));
		path.append(coordToStringAlnum(pos.z) + "." + EXT);

		return path.toString();
	}

	bool MapLoader::isBlockOnHardDrive(const Vector3i pos)
	{
		return fs::isPathExists(getBlockPath(pos));
	}

	void MapLoader::getAllBlockPositions(std::set<Vector3i> & positions)
	{
		// TODO MapLoader: rename m_dir -> m_worldDir
		fs::Path path(SAVES_DIR);
		Vector3i pos;

		path.append(m_dir);
		fs::DirContent xdir;
		fs::getDirContent(xdir, path.toString());

		for(auto & xnode : xdir.nodes) // X
		{
			if(!xnode.isDirectory)
				continue;

			pos.x = stringAlnumToCoord(xnode.name);
			path.append(xnode.name);
			fs::DirContent ydir;
			fs::getDirContent(ydir, path.toString());

			for(auto & ynode : ydir.nodes) // Y
			{
				if(!ynode.isDirectory)
					continue;

				pos.y = stringAlnumToCoord(ynode.name);
				path.append(ynode.name);
				fs::DirContent zdir;
				fs::getDirContent(zdir, path.toString());

				for(auto & znode : zdir.nodes) // Z
				{
					if(znode.isDirectory)
						continue; // znodes are files

					pos.z = stringAlnumToCoord(znode.name);
					if(!positions.insert(pos).second)
						std::cout << "WARNING: MapLoader::getAllBlockPositions: "
							<< "found twice the same pos " << pos << std::endl;
					//std::cout << pos << ", ";
				}
				path.pop();
			}
			path.pop();
		}
	}

} // namespace zcraft


