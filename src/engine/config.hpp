/*
config.hpp
Copyright (C) 2010-2013 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_CONFIG_HPP_INCLUDED
#define ZN_CONFIG_HPP_INCLUDED

#include "system/osdefines.hpp"

// Indicates that we use SFML
// Note : if disabled, the engine may not compile : some files are using it
// to ease SFML interfacing.
#define ZN_SFML

// Maximal OpenGL version.
// Important : only one of these macros must be enabled !
// TODO : opengl: design a generic renderer
#define ZN_OPENGL2
//#define ZN_OPENGL3

#endif // ZN_CONFIG_HPP_INCLUDED
