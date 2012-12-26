#include <sstream>
#include "engine/opengl/glutils.hpp"
#include "engine/opengl/Color.hpp"

namespace engine
{
	Color::Color() : r(0), g(0), b(0), a(1)
	{}

	Color::Color(f32 r0, f32 g0, f32 b0, f32 a0) : r(r0), g(g0), b(b0), a(a0)
	{}

	Color::Color(u8 r0, u8 g0, u8 b0, u8 a0)
	{
		set(r0, g0, b0, a0);
	}

	Color::Color(const Color & other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}

#ifdef SFML_API
	Color::Color(const sf::Color & color)
	{
		set(color.r, color.g, color.b, color.a);
	}
#endif

#ifdef SFML_API
	sf::Color Color::toSfColor() const
	{
		return sf::Color(255.f * r, 255.f * g, 255.f * b, 255.f * a);
	}
#endif

	void Color::setf(float r0, float g0, float b0, float a0)
	{
		r = r0;
		g = g0;
		b = b0;
		a = a0;
	}

	void Color::set(u8 r0, u8 g0, u8 b0, u8 a0)
	{
		r = (float)r0 / 255.f;
		g = (float)g0 / 255.f;
		b = (float)b0 / 255.f;
		a = (float)a0 / 255.f;
	}

	void Color::bind() const
	{
		glColor4f(r, g, b, a);
	}

	std::string Color::toString() const
	{
		std::stringstream ss;
		ss << "(R=" << (int)(255.f * r)
		  << ", G=" << (int)(255.f * g)
		  << ", B=" << (int)(255.f * b)
		  << ", A=" << (int)(255.f * a) << ")";
		return ss.str();
	}

	void Color::normalize()
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

	Color Color::operator+(const Color & other)
	{
		return Color(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	Color Color::operator-(const Color & other)
	{
		return Color(r - other.r, g - other.g, b - other.b, a - other.a);
	}

	Color Color::operator*(const Color & other)
	{
		return Color(r * other.r, g * other.g, b * other.b, a * other.a);
	}

	Color Color::operator/(const Color & other)
	{
		return Color(r / other.r, g / other.g, b / other.b, a / other.a);
	}

	Color Color::operator*(f32 s)
	{
		return Color(r*s, g*s, b*s, a*s);
	}

	Color Color::operator/(f32 s)
	{
		return Color(r/s, g/s, b/s, a/s);
	}

	void Color::operator+=(const Color & other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
	}

	void Color::operator-=(const Color & other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
	}

	void Color::operator*=(const Color & other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
	}

	void Color::operator/=(const Color & other)
	{
		r /= other.r;
		g /= other.g;
		b /= other.b;
		a /= other.a;
	}

	void Color::operator*=(f32 s)
	{
		r *= s;
		g *= s;
		b *= s;
		a *= s;
	}

	void Color::operator/=(f32 s)
	{
		r /= s;
		g /= s;
		b /= s;
		a /= s;
	}

	std::string operator+(std::string const & a, Color const & b)
	{
		return a + b.toString();
	}

	std::ostream & operator<<(std::ostream & os, const Color & col)
	{
		return os << col.toString();
	}

} // namespace engine



