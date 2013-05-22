#include <iostream>

#include "engine/system/files/filesystem.hpp"

#if defined(OS_WINDOWS)
    #include <windows.h>
#else // POSIX
    #include <sys/stat.h>
#endif

namespace zn
{
namespace fs
{
    void checkSlashes(std::string & path)
    {
        for(unsigned int i = 0; i < path.size(); i++)
        {
            if(path[i] == '/' || path[i] == '\\')
                path[i] = DIR_CHAR;
        }
    }

#if defined(OS_WINDOWS)

    bool isPathExists(std::string path)
	{
		return (GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES);
    }

    bool makeDir(std::string path)
    {
        if(path.empty())
            return false;
		bool success = CreateDirectoryA(path.c_str(), NULL);
        if(success)
            return true;
        if(GetLastError() == ERROR_ALREADY_EXISTS)
            return true;
        else
            std::cout << "ERROR: WIN makeDir: can't create folder '"
				<< path << "'" << std::endl;
        return false;
    }

    bool getDirContent(DirContent & content, std::string dirPath)
    {
        std::string nodeName, fileName;
        bool searchResult;
		WIN32_FIND_DATAA findData;

        content.dirPath = dirPath;
        std::string path = dirPath + "\\*.*";
		HANDLE l_searchHandle = FindFirstFileA(path.c_str(), & findData);

        if(l_searchHandle == INVALID_HANDLE_VALUE)
        {
            std::cout << "ERROR: WIN getDirContent: INVALID_HANDLE_VALUE" << std::endl;
            return false;
        }

		while( (searchResult = FindNextFileA(l_searchHandle, &findData)) == true )
        {
            bool isDirectory = false;
            if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                isDirectory = true;

            fileName = findData.cFileName;
            // not include '.' and '..' folders (current and parent)
            if(fileName != "." && fileName != "..")
            {
                nodeName = fileName;
                content.nodes.push_back(Node(nodeName.c_str(), isDirectory));
            }
        }
        FindClose(l_searchHandle);
        return true;
    }

#else // POSIX

    bool isPathExists(std::string path)
    {
        struct stat st;
        return (stat(path.c_str(), &st) == 0);
    }

    bool makeDir(std::string path)
    {
        if(path.empty())
            return false;
        // options : user : rwx searchable, group : rwx searchable, others : r-x searchable
        int result = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(result == 0)
            return true;
        if(errno == EEXIST)
            return true;
        else
            std::cout << "ERROR: makeDir: can't create folder '"
				<< path << "'" << std::endl;
        return false;
    }

    bool getDirContent(DirContent & content, std::string dirPath)
    {
    	std::cout << "ERROR: UNIX getDirContent: not implemented yet" << std::endl;
        // TODO filesystem: getDirContent for Linux POSIX
        return false;
    }

#endif

    bool makeAllDirs(const Path & fsPath, bool treatAsFile)
    {
        if(fsPath.isEmpty())
            return false;
        std::string path = "";

        int end = fsPath.parts.size();
        if(treatAsFile)
			end--;

        for(int i = 0; i < end; i++)
        {
			path += fsPath.parts[i];
			if(!makeDir(path)) // create dir
				return false; // something went wrong
			path += DIR_CHAR;
        }
        return true;
    }

    bool makeAllDirs(std::string path, bool treatAsFile)
    {
        if(path.empty())
            return false;
        const Path fsPath(path);
        return makeAllDirs(fsPath, treatAsFile);
    }

} // namespace fs
} // namespace zn



