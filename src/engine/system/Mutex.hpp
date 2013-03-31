/*
Mutex.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_MUTEX_HPP_INCLUDED
#define ZN_MUTEX_HPP_INCLUDED

/* Header-only */

#include <SFML/System.hpp>

namespace zn
{
	/**
		Wrapper class for mutexes.
		SFML backend.
	**/

	class Mutex
	{
	private :

		sf::Mutex m_mutex;
		bool m_locked; // tells if the mutex is locked

	public :

		Mutex()
		{
			m_locked = false;
		}

		void lock()
		{
			m_mutex.lock();
			m_locked = true;
		}

		void unlock()
		{
			m_mutex.unlock();
			m_locked = false;
		}

		inline bool isLocked() const
		{
			return m_locked;
		}
	};

	class MutexLocker : public sf::NonCopyable
	{
	private :

		Mutex * m_mutex;

	public :

		MutexLocker(Mutex & m)
		{
			m.lock();
			m_mutex = &m;
		}

		~MutexLocker()
		{
			m_mutex->unlock();
		}
	};

} // namespace zn

#endif // ZN_MUTEX_HPP_INCLUDED


