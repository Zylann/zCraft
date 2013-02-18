/*
DirContent.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef DIRCONTENT_HPP_INCLUDED
#define DIRCONTENT_HPP_INCLUDED

namespace zn
{
namespace fs
{
    struct DirContent
    {
        std::vector<Node> nodes;
        std::string dirPath;

        void print()
        {
            std::cout << dirPath << " :" << std::endl;
            for(unsigned int i = 0; i < nodes.size(); i++)
            {
                if(nodes[i].isDirectory)
                    std::cout << "dir  ";
                else
                    std::cout << "file ";
                std::cout << nodes[i].name << std::endl;
            }
        }
    };

} // namespace fs
} // namespace zn

#endif // DIRCONTENT_HPP_INCLUDED


