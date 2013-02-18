/*
Colorf.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_COLORF_HPP_INCLUDED
#define ENGINE_COLORF_HPP_INCLUDED

#include <string>
#include "engine/types.hpp"

#ifdef ZN_SFML
	#include <SFML/Graphics.hpp>
#endif

namespace engine
{
	/*
		Stores a color using 4 float values for red, green, blue and alpha.
		This version is well suited for calculations.
		Note : methods of Colorf don't call normalize() to keep values in [0,1].
	*/

	struct Colorf
	{
		f32 r;
		f32 g;
		f32 b;
		f32 a;

		// Constructs an opaque black color.
		Colorf();

		// Constructs a color using float values in [0,1]
		Colorf(f32 r0, f32 g0, f32 b0, f32 a0 = 1);

		// Constructs a color from another color
		Colorf(const Colorf & other);

	#ifdef ZN_SFML
		// Constructs a color from a SFML color
		Colorf(const sf::Color & color);
	#endif

	#ifdef ZN_SFML
		// Converts this color to a SFML color
		sf::Color toSfColor() const;
	#endif

		// Assigns [0,1] float values to this color
		void setf(float r0, float g0, float b0, float a0 = 1);

		// Assigns [0,255] integer values to this color
		void set(u8 r0, u8 g0, u8 b0, u8 a0 = 255);

		// Clamps color values in [0,1]
		void normalize();

		// Converts the object to a human-readable form
		std::string toString() const;

		// Multiplies RGB values by a scalar (alpha is ignored)
		void multiplyRGB(float s);

		Colorf operator+(const Colorf & other);

		Colorf operator-(const Colorf & other);

		Colorf operator*(const Colorf & other);

		Colorf operator/(const Colorf & other);

		Colorf operator*(f32 s);

		Colorf operator/(f32 s);

		void operator+=(const Colorf & other);

		void operator-=(const Colorf & other);

		void operator*=(const Colorf & other);

		void operator/=(const Colorf & other);

		void operator*=(f32 s);

		void operator/=(f32 s);

	};

	std::string operator+(std::string const & a, Colorf const & b);

	std::ostream & operator<<(std::ostream & os, const Colorf & col);

} // namespace engine

#endif // ENGINE_COLORF_HPP_INCLUDED


