/*
Path.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/system/files/Path.hpp"

namespace engine
{
namespace fs
{
	Path::Path(std::string strPath)
	{
		create(strPath);
	}

	void Path::create(std::string strPath)
	{
		parts.clear();

		if(strPath.empty())
			return;

		std::string part;
		for(unsigned int i = 0; i < strPath.size(); i++)
		{
			if((strPath[i] == '/' || strPath[i] == '\\') && !part.empty())
			{
				parts.push_back(part);
				part.clear();
			}
			else
			{
				part += strPath[i];
			}
		}
		if(!part.empty())
			parts.push_back(part);
	}

	bool Path::isEmpty() const
	{
		return parts.empty();
	}

	void Path::append(std::string part)
	{
		parts.push_back(part);
	}

	void Path::append(Path fsPath)
	{
		for(unsigned int i = 0; i < fsPath.parts.size(); i++)
			append(fsPath.parts[i]);
	}

	void Path::pop()
	{
		parts.pop_back();
	}

	std::string Path::toString() const
	{
		std::string path;
		for(unsigned int i = 0; i < parts.size(); i++)
		{
			if(i != 0)
				path += DIR_CHAR;
			path += parts[i];
		}
		return path;
	}

} // namespace fs
} // namespace engine


