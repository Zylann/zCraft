/*
types.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENG_TYPES_HPP_INCLUDED
#define ENG_TYPES_HPP_INCLUDED

// Indicates that we use SFML
#ifndef SFML_API
	#define SFML_API
#endif

namespace engine
{
	typedef unsigned int u32;
	typedef unsigned short u16;
	typedef unsigned char u8;

	typedef int s32;
	typedef short s16;
	typedef char s8;

	typedef float f32;
	typedef double f64;
}

#endif // ENG_TYPES_HPP_INCLUDED
