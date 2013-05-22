/*
config.hpp
Copyright (C) 2010-2013 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_CONFIG_HPP_INCLUDED
#define ZN_CONFIG_HPP_INCLUDED

#include "system/osdefines.hpp"

// Note : these defines are only used as hints. They may ease some
// particular configurations.

// Hint for SFML compatibility
// Note : if disabled, many multimedia-related things may not compile,
// as SFML is widely used in the framework.
#define ZN_SFML

// Hint for preferred OpenGL version.
// Important : only one of these macros must be enabled !
#define ZN_OPENGL2
//#define ZN_OPENGL3

// Hint to use C++0x instead of C++11
// Warning : this option is temporary and may disappear in the future.
#define ZN_CPP0X

#ifdef ZN_CPP0X
    // Use this [dirty] define to strip-out override keywords
    #define override /*override*/
#endif

#endif // ZN_CONFIG_HPP_INCLUDED

