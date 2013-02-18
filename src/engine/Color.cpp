/*
Color.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/Color.hpp"
#include "engine/math.hpp"

namespace zn
{
	Color::Color() : r(0), g(0), b(0), a(1)
	{}

	Color::Color(u8 r0, u8 g0, u8 b0, u8 a0) : r(r0), g(g0), b(b0), a(a0)
	{}

	Color::Color(const Color & other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}

#if defined ZN_SFML
	Color::Color(const sf::Color & color)
	{
		set(color.r, color.g, color.b, color.a);
	}
#endif

#if defined ZN_SFML
	sf::Color Color::toSfColor() const
	{
		return sf::Color(r, g, b, a);
	}
#endif

	void Color::setf(float r0, float g0, float b0, float a0)
	{
		r = 255.f * r0;
		g = 255.f * g0;
		b = 255.f * b0;
		a = 255.f * a0;
	}

	void Color::set(u8 r0, u8 g0, u8 b0, u8 a0)
	{
		r = r0;
		g = g0;
		b = b0;
		a = a0;
	}

	void Color::set(Color other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}

	void Color::multiplyRGB(float s)
	{
		r = math::min((f32)r * s, 255.f);
		g = math::min((f32)g * s, 255.f);
		b = math::min((f32)b * s, 255.f);
		a = math::min((f32)a * s, 255.f);
	}

	void Color::multiplyU8(u8 ku)
	{
		const float kf = static_cast<float>(ku) / 255.f;
		r = (u8)((float)r * kf);
		g = (u8)((float)g * kf);
		b = (u8)((float)b * kf);
		a = (u8)((float)a * kf);
	}

	std::string Color::toString() const
	{
		std::stringstream ss;
		ss << "(R=" << (int)r
		  << ", G=" << (int)g
		  << ", B=" << (int)b
		  << ", A=" << (int)a << ")";
		return ss.str();
	}

	Color Color::operator+(const Color & other)
	{
		return Color(
			math::min((u32)r + (u32)other.r, 255u),
			math::min((u32)g + (u32)other.g, 255u),
			math::min((u32)b + (u32)other.b, 255u),
			math::min((u32)a + (u32)other.a, 255u));
	}

	Color Color::operator-(const Color & other)
	{
		return Color(
			r > other.r ? r - other.r : 0,
			g > other.g ? g - other.g : 0,
			b > other.b ? b - other.b : 0,
			a > other.a ? a - other.a : 0);
	}

	void Color::operator+=(const Color & other)
	{
		r = math::min((u32)r + (u32)other.r, 255u);
		g = math::min((u32)g + (u32)other.g, 255u);
		b = math::min((u32)b + (u32)other.b, 255u);
		a = math::min((u32)a + (u32)other.a, 255u);
	}

	void Color::operator-=(const Color & other)
	{
		r = r > other.r ? r - other.r : 0;
		r = g > other.g ? g - other.g : 0;
		r = b > other.b ? b - other.b : 0;
		r = a > other.a ? a - other.a : 0;
	}

	std::string operator+(std::string const & a, Color const & b)
	{
		return a + b.toString();
	}

	std::ostream & operator<<(std::ostream & os, const Color & col)
	{
		return os << col.toString();
	}

} // namespace zn



