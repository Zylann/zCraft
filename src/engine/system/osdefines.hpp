#ifndef OSDEFINES_HPP_INCLUDED
#define OSDEFINES_HPP_INCLUDED

// Identify the operating system

#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)

    // Windows
    #define OS_WINDOWS

#elif defined(linux) || defined(__linux)

    // Linux
    #define OS_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    // MacOS
    #define OS_MACOS

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    // FreeBSD
    #define OS_FREEBSD

#else

    // Unsupported system
    #error This operating system (or compiler) is not supported for this project

#endif

#endif // OSDEFINES_HPP_INCLUDED
