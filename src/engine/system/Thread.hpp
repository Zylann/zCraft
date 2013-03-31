/*
Thread.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_THREAD_HPP_INCLUDED
#define ZN_THREAD_HPP_INCLUDED

#include <iostream>
#include <SFML/System.hpp>

namespace zn
{
	/**
		Simple thread class wrapper.
		Currently uses SFML backend.
	**/

    class AThread
    {
	private :

		sf::Thread m_thread;
		bool m_isRunning;           // externally viewed flag
		std::string m_name;   // Thread's name
		// TODO Thread: make non-copyable

	protected :

		/// intern flag that must be checked in implementing classes
		/// in order to stop cleanly if set to false
		/// (may be useful for constantly running threads).
		bool m_runFlag;

		/// Constructs an inactive thread. The name is useful for debug
		/// (and probably for system naming in the future)
		AThread(const std::string & name) : m_thread(&AThread::_run, this)
		{
			m_isRunning = false;
			m_runFlag = false;
			m_name = name;
		}

		~AThread()
		{
			if(isRunning())
			{
				std::cout << "WARNING: ~Thread: the thread is still running !"
					<< "object destruction may lead to undetermined behavior "
					<< "(better stop the thread before destroying it)" << std::endl;
				stop();
				wait();
			}
		}

	public :

		/// starts the thread.
		void start()
		{
			if(!m_isRunning)
			{
				m_isRunning = true;
				std::cout << "Started thread " << m_name << std::endl;
				m_thread.launch();
			}
			else
				std::cout << "WARNING: AThread::run: already running "
					<< m_name << std::endl;
		}

		/// tells the thread to stop :
		/// despite being not immediate, it's a mean for the thread to know when it must end,
		/// and let it free allocated resources.
		void stop()
		{
			std::cout << "Asked thread " << m_name << " to stop." << std::endl;
			m_runFlag = false;
		}

		/// Tests if the thread is running.
		bool isRunning() const
		{
			return m_isRunning;
		}

		/// Blocks and wait until the thread ends
		void wait()
		{
			std::cout << "Waiting for thread " << m_name << " to finish..." << std::endl;
			m_thread.wait();
		}

		/// Terminates the thread BUT without any warranty
		/// about the state of work data
		void terminate()
		{
			m_thread.terminate();
			m_isRunning = false;
		}

	protected :

		/// the thread function that will be run.
		/// must be implemented in subclasses.
		virtual void run() = 0;

	private :

		/// run() wrapper (used internally)
		void _run()
		{
			m_runFlag = true;
			run();
			m_isRunning = false;
			std::cout << "Thread " << m_name << " finished" << std::endl;
		}

	public :

    };

	/// Suspends the current thread for a certain time
	inline void sleep(unsigned int milliseconds)
	{
		sf::sleep(sf::milliseconds(milliseconds));
	}

} // namespace zn

#endif // ZN_THREAD_HPP_INCLUDED


