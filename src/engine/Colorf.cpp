/*
Colorf.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/Colorf.hpp"

namespace zn
{
	Colorf::Colorf() : r(0), g(0), b(0), a(1)
	{}

	Colorf::Colorf(f32 r0, f32 g0, f32 b0, f32 a0) : r(r0), g(g0), b(b0), a(a0)
	{}

	Colorf::Colorf(const Colorf & other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}

#if defined ZN_SFML
	Colorf::Colorf(const sf::Color & color)
	{
		set(color.r, color.g, color.b, color.a);
	}
#endif

#if defined ZN_SFML
	sf::Color Colorf::toSfColor() const
	{
		return sf::Color(255.f * r, 255.f * g, 255.f * b, 255.f * a);
	}
#endif

	void Colorf::setf(float r0, float g0, float b0, float a0)
	{
		r = r0;
		g = g0;
		b = b0;
		a = a0;
	}

	void Colorf::set(u8 r0, u8 g0, u8 b0, u8 a0)
	{
		r = (float)r0 / 255.f;
		g = (float)g0 / 255.f;
		b = (float)b0 / 255.f;
		a = (float)a0 / 255.f;
	}

	std::string Colorf::toString() const
	{
		std::stringstream ss;
		ss << "(R=" << (int)(255.f * r)
		  << ", G=" << (int)(255.f * g)
		  << ", B=" << (int)(255.f * b)
		  << ", A=" << (int)(255.f * a) << ")";
		return ss.str();
	}

	void Colorf::normalize()
	{
		if(r < 0) r = 0;
		else if(r > 1) r = 1;

		if(g < 0) g = 0;
		else if(g > 1) g = 1;

		if(b < 0) b = 0;
		else if(b > 1) b = 1;

		if(a < 0) a = 0;
		else if(a > 1) a = 1;
	}

	Colorf Colorf::operator+(const Colorf & other)
	{
		return Colorf(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	Colorf Colorf::operator-(const Colorf & other)
	{
		return Colorf(r - other.r, g - other.g, b - other.b, a - other.a);
	}

	Colorf Colorf::operator*(const Colorf & other)
	{
		return Colorf(r * other.r, g * other.g, b * other.b, a * other.a);
	}

	Colorf Colorf::operator/(const Colorf & other)
	{
		return Colorf(r / other.r, g / other.g, b / other.b, a / other.a);
	}

	Colorf Colorf::operator*(f32 s)
	{
		return Colorf(r*s, g*s, b*s, a*s);
	}

	Colorf Colorf::operator/(f32 s)
	{
		return Colorf(r/s, g/s, b/s, a/s);
	}

	void Colorf::operator+=(const Colorf & other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
	}

	void Colorf::operator-=(const Colorf & other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
	}

	void Colorf::operator*=(const Colorf & other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
	}

	void Colorf::operator/=(const Colorf & other)
	{
		r /= other.r;
		g /= other.g;
		b /= other.b;
		a /= other.a;
	}

	void Colorf::operator*=(f32 s)
	{
		r *= s;
		g *= s;
		b *= s;
		a *= s;
	}

	void Colorf::operator/=(f32 s)
	{
		r /= s;
		g /= s;
		b /= s;
		a /= s;
	}

	std::string operator+(std::string const & a, Colorf const & b)
	{
		return a + b.toString();
	}

	std::ostream & operator<<(std::ostream & os, const Colorf & col)
	{
		return os << col.toString();
	}

} // namespace zn



