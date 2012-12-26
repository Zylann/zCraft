/*
Mutex.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_MUTEX_HPP_INCLUDED
#define ENGINE_MUTEX_HPP_INCLUDED

/* Header-only */

#include <SFML/System.hpp>

namespace engine
{
	/**
		Wrapper class for mutexes.
		SFML backend.
	**/

	class Mutex : private sf::Mutex
	{
	private :

		bool m_locked; // tells if the mutex is locked

	public :

		Mutex() : sf::Mutex()
		{
			m_locked = false;
		}

		void lock()
		{
			sf::Mutex::lock();
			m_locked = true;
		}

		void unlock()
		{
			m_locked = false;
			sf::Mutex::unlock();
		}

		bool isLocked() const
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

} // namespace engine

#endif // ENGINE_MUTEX_HPP_INCLUDED
