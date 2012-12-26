#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include <string>
#include "engine/types.hpp"

#ifdef SFML_API
	#include <SFML/Graphics.hpp>
#endif

namespace engine
{
	struct Color
	{
		f32 r;
		f32 g;
		f32 b;
		f32 a;

		Color();

		Color(f32 r0, f32 g0, f32 b0, f32 a0 = 1);

		Color(u8 r0, u8 g0, u8 b0, u8 a0 = 255);

		Color(const Color & other);

	#ifdef SFML_API
		Color(const sf::Color & color);
	#endif

	#ifdef SFML_API
		sf::Color toSfColor() const;
	#endif

		void setf(float r0, float g0, float b0, float a0 = 1);

		void set(u8 r0, u8 g0, u8 b0, u8 a0 = 255);

		void normalize();

		void bind() const;

		std::string toString() const;

		Color operator+(const Color & other);

		Color operator-(const Color & other);

		Color operator*(const Color & other);

		Color operator/(const Color & other);

		Color operator*(f32 s);

		Color operator/(f32 s);

		void operator+=(const Color & other);

		void operator-=(const Color & other);

		void operator*=(const Color & other);

		void operator/=(const Color & other);

		void operator*=(f32 s);

		void operator/=(f32 s);

	};

	std::string operator+(std::string const & a, Color const & b);

	std::ostream & operator<<(std::ostream & os, const Color & col);

} // namespace engine

#endif // COLOR_HPP_INCLUDED


