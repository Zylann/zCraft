/*
Signal.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_SIGNAL_HPP_INCLUDED
#define ZENGUI_SIGNAL_HPP_INCLUDED

#include <functional>
#include <list>
#include <unordered_map>

namespace zn
{
namespace ui
{
	/**
	 * @file This is an implementation of events/signals/callbacks-like system,
	 * designed to be non-intrusive. However, it doesn't automatically detects
	 * when objects get destroyed, but you can disconnect them manually.
	 *
	 * @note It currently exist one version per argument count. Each version is
	 * roughly a copy of each other, but I don't know how to do it in one class.
	 *
	 * @example Signal1<std::string> sig;
	 * sig.connect(textField, &MyTextField::changeText);
	 * sig("New text"); // Changes the text
	 * sig.disconnect(textField);
	 * sig("Foo"); // Does nothing
	 *
	 * @warning Signals currently use default copy behavior, it's not recommended to
	 * copy them unless you know what you are doing.
	 */

	/**
	 * @brief A signal that takes no arguments.
	 */
	class Signal0
	{
	private:

		std::list<std::function<void(void)> > m_f0;
		std::unordered_multimap<void*, std::function<void(void)> > m_mf0;

	public:

		void connect(std::function<void(void)> f)
		{
			m_f0.push_back(f);
		}

		template <class T>
		void connect(T & obj, void(T::*rmf)(void))
		{
			std::function<void(void)> mf = std::bind(rmf, std::ref(obj));
			m_mf0.insert(std::make_pair(&obj, mf));
		}

		template <class T>
		void disconnect(T & obj)
		{
			m_mf0.erase(&obj);
		}

		void disconnect()
		{
			m_mf0.clear();
			m_f0.clear();
		}

		void operator()()
		{
			for(auto & f : m_f0)
			{
				f();
			}
			for(auto & p : m_mf0)
			{
				p.second();
			}
		}
	};

	/**
	 * @brief A signal that takes one argument
	 */
	template <typename A>
	class Signal1
	{
	private:

		std::list<std::function<void(A)> > m_f0;
		std::unordered_multimap<void*, std::function<void(A)> > m_mf0;

	public:

		void connect(std::function<void(A)> f)
		{
			m_f0.push_back(f);
		}

		template <class T>
		void connect(T & obj, void(T::*rmf)(A))
		{
			std::function<void(A)> mf = std::bind(rmf, std::ref(obj), std::placeholders::_1);
			m_mf0.insert(std::make_pair(&obj, mf));
		}

		template <class T>
		void disconnect(T & obj)
		{
			m_mf0.erase(&obj);
		}

		void disconnect()
		{
			m_mf0.clear();
			m_f0.clear();
		}

		void operator()(A a)
		{
			for(auto & f : m_f0)
			{
				f(a);
			}
			for(auto & p : m_mf0)
			{
				p.second(a);
			}
		}
	};

	// TODO find a way to not have a class copy-paste for every parameter count
	// TODO study the signal copy case

} // namespace ui
} // namespace zn

#endif // ZENGUI_SIGNAL_HPP_INCLUDED




