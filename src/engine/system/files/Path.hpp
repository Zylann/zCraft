/*
Path.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_FILESYSTEM_PATH_HPP_INCLUDED
#define ENGINE_FILESYSTEM_PATH_HPP_INCLUDED

#include <string>
#include <vector>
#include "engine/system/osdefines.hpp"
#include "engine/system/files/Node.hpp"

namespace zn
{
namespace fs
{
#if defined(OS_WINDOW)
	static const char DIR_CHAR = '\\';
#else // POSIX
	static const char DIR_CHAR = '/';
#endif

    class Path
    {
    public :

        std::vector<std::string> parts;

        Path() {}

        Path(std::string strPath);

        void create(std::string strPath);

        bool isEmpty() const;

        void append(std::string part);

        void append(Path fsPath);

        void pop();

        std::string toString() const;

    };

} // namespace filesystem
} // namespace zn

#endif // ENGINE_FILESYSTEM_PATH_HPP_INCLUDED
