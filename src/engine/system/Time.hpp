#ifndef ZN_TIME_HPP_INCLUDED
#define ZN_TIME_HPP_INCLUDED

#include <chrono>
#include "engine/core/types.hpp"

namespace zn
{
	// TODO Time: should be moved to core?
	class Time
	{
	private :

		u32 m_millis;

	public :

		Time(u32 ms) : m_millis(ms)
		{}

		// Returns the time value in seconds
		inline f32 s() const
		{
			return (f32)m_millis / 1000.f;
		}

		// Returns the time value in milliseconds
		inline s32 ms() const
		{
			return m_millis;
		}

		// Returns the time frequency in hertz.
		// Returns -1 if the time is 0.
		inline f32 hz() const
		{
			const float seconds = s();
			if(seconds != 0)
				return 1.f / seconds;
			return -1;
		}

		// NOT USED, because using time spans is better than getting the clock().
//		static inline u32 millis()
//		{
//			std::chrono::time_point_cast<
//					std::chrono::milliseconds>(
//						std::chrono::high_resolution_clock::now().time_point);
//		}

		// TODO Time: create Timer class using <chrono>, and drop sf::Clock
	};

} // namespace zn

#endif // ZN_TIME_HPP_INCLUDED


