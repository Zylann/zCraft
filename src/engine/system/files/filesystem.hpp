#ifndef ENGINE_FILESYSTEM_HPP_INCLUDED
#define ENGINE_FILESYSTEM_HPP_INCLUDED

#include <string>

#include "engine/system/files/Path.hpp"
#include "engine/system/files/DirContent.hpp"

namespace engine
{
namespace fs
{
	/// Replaces slashes/antislashes by the OS-specific dir char
    void checkSlashes(std::string & path);

    /// Get files and directories of a directory
    bool getDirContent(DirContent& content, std::string dirPath);

    /// Find if a file or directory exists
    bool isPathExists(std::string path);

    /// Creates a directory
    bool makeDir(std::string fsPath);

    /// create all [sub]directories contained in fsPath.
    /// if treatAsFile is set to true, the last part of the path will not be used.
    bool makeAllDirs(const Path & fsPath, bool treatAsFile = false);

    /// create all [sub]directories contained in path (based on the function above)
    /// if treatAsFile is set to true, the last part of the path will not be used.
    bool makeAllDirs(std::string path, bool treatAsFile = false);

    // TODO filesystem: remove files function
    //bool removeFilesRecursive(std::string path);

} // namespace fs
} // namespace util

#endif // ENGINE_FILESYSTEM_HPP_INCLUDED


