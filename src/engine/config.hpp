#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include "engine/system/osdefines.hpp"

// Indicates that we use SFML
// Note : if disabled, the engine may not compile : some files are using
// to ease SFML interfacing.
#define ZN_SFML

// Maximal OpenGL version.
// Important : only one of these macros must be enabled !
// TODO : opengl: design a generic renderer
#define ZN_OPENGL2
//#define ZN_OPENGL3

#endif // CONFIG_HPP_INCLUDED
