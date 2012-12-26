#ifndef TIME_HPP_INCLUDED
#define TIME_HPP_INCLUDED

namespace engine
{
	class Time
	{
	private :

		u32 m_millis;

	public :

		Time(u32 ms)
		{
			m_millis = ms;
		}

		inline f32 s() const
		{
			return (f32)m_millis / 1000.f;
		}

		inline s32 ms() const
		{
			return m_millis;
		}

		inline f32 hz() const
		{
			const float seconds = s();
			if(seconds != 0)
				return 1.f / seconds;
			return -1;
		}

	};

} // namespace engine

#endif // TIME_HPP_INCLUDED
