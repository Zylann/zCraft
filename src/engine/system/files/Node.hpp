/*
Node.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_FILESYSTEM_NODE_HPP_INCLUDED
#define ENGINE_FILESYSTEM_NODE_HPP_INCLUDED

#include <string>

namespace engine
{
namespace fs
{
    struct Node
    {
        std::string name;
        bool isDirectory;

        Node() { isDirectory = false; }

        Node(std::string p_name, bool dir)
        : name(p_name), isDirectory(dir)
        {}
    };

} // namespace fs
} // namespace engine

#endif // ENGINE_FILESYSTEM_NODE_HPP_INCLUDED
