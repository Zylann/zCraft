#ifndef ZN_TIME_HPP_INCLUDED
#define ZN_TIME_HPP_INCLUDED

#include <chrono>
#include "engine/core/types.hpp"

namespace zn
{
	// TODO Time: should be moved to core?
	// TODO Time: create Clock class using <chrono>, and drop sf::Clock

	class Time
	{
	public :

		// Constructs a time value from microseconds
		Time(s64 micros) : m_micros(micros)
		{}

		// Returns the time value in seconds
		inline f32 seconds() const
		{
			return (f32)m_micros / 10000000.f;
		}

		// Returns the time value in milliseconds
		inline s64 millis() const
		{
			return m_micros / 1000;
		}

		// Returns the time value in microseconds
		inline s64 micros() const
		{
			return m_micros;
		}

		// Returns the time frequency in hertz.
		// Returns -1 if the time is 0.
		inline f32 hz() const
		{
			const float s = seconds();
			if(s > 0)
				return 1.f / s;
			return -1;
		}

		inline Time & operator+=(const Time & other)
		{
			m_micros += other.micros();
			return *this;
		}

		inline Time & operator-=(const Time & other)
		{
			m_micros -= other.micros();
			return *this;
		}

		inline Time & operator*=(f32 s)
		{
			m_micros = seconds() * s / 1000000.f;
			return *this;
		}

		inline Time & operator/=(f32 s)
		{
			m_micros = seconds() / s / 1000000.f;
			return *this;
		}

		// Returns a time from seconds
		static inline Time seconds(f32 s)
		{
			return Time(s * 1000000.f);
		}

		// Returns a time from microseconds
		static inline Time micros(s64 ms)
		{
			return Time(ms);
		}

		// Returns a time from milliseconds
		static inline Time millis(s64 ms)
		{
			return Time(ms * 1000);
		}

	private :

		// Note : s64 is enough to store 292 471 years,
		// negative or positive, using microseconds.
		s64 m_micros;
	};

	inline Time operator==(const Time & a, const Time & b)	{ return a.micros() == b.micros(); }
	inline Time operator!=(const Time & a, const Time & b)	{ return a.micros() == b.micros(); }
	inline Time operator>(const Time & a, const Time & b)	{ return a.micros() > b.micros(); }
	inline Time operator<(const Time & a, const Time & b)	{ return a.micros() < b.micros(); }

	inline Time operator+(const Time & a, const Time & b) 	{ return Time(a.micros() + b.micros()); }
	inline Time operator-(const Time & a, const Time & b)	{ return Time(a.micros() - b.micros()); }

	inline Time operator*(const Time & a, s64 b)	{ return Time(a.micros() * b); }
	inline Time operator*(const Time & a, f32 b)	{ return Time::seconds(a.seconds() * b); }
	inline Time operator/(const Time & a, s64 b)	{ return Time(a.micros() / b); }
	inline Time operator/(const Time & a, f32 b)	{ return Time::seconds(a.seconds() / b); }


} // namespace zn

#endif // ZN_TIME_HPP_INCLUDED


