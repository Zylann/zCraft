/*
MapLoader.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPLOADER_HPP_INCLUDED
#define MAPLOADER_HPP_INCLUDED

#include <set>
#include <list>
#include "zcraft/Block.hpp"

namespace zcraft
{
	class MapLoader
	{
	public :

		static const std::string SAVES_DIR;
		static const std::string EXT;

	private :

		std::string m_dir;

	public :

		/// Constructs a map loader binded to a world directory.
		/// If not specified, the directory will be set to default.
		MapLoader(const std::string dir = "default");

		Block * loadBlock(const Vector3i pos);

		bool saveBlock(const Block * block);

		std::string getBlockPath(const Vector3i pos);

		bool isBlockOnHardDrive(const Vector3i pos);

		void getAllBlockPositions(std::set<Vector3i> & positions);

	};

} // namespace zcraft


#endif // MAPLOADER_HPP_INCLUDED
