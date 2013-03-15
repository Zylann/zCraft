/*
Singleton.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_SINGLETON_HPP_INCLUDED
#define ZN_SINGLETON_HPP_INCLUDED

/* Header-only */

namespace zn
{
	/**
		Singleton pattern is used for classes that must have only one instance.
		it must be inherited using "friend class util::Singleton<UniqueObject>;",
		and accessed using "UniqueObject * obj = UniqueObject::get();"

		[!] Destruction must be done using the kill() method.

		Constructors with arguments are not supported.
	**/

	template <typename T>
	class Singleton // TODO Singleton: make non-copyable
	{
	private :

		static T * s_instance;

	protected :

		Singleton() {}

	public :

		/// Get the unique instance of T.
		/// It is created on first call.
		static T * instance()
		{
			if(s_instance == nullptr)
			{
				s_instance = new T;
			}
			// s_instance must never be NULL here
			return s_instance;
		}

		/// kill must be called manually to destroy the unique instance.
		static void kill()
		{
			if(s_instance != nullptr)
			{
				delete s_instance;
				s_instance = nullptr;
			}
		}
	};

	// initialize instance
	template <typename T>
	T * Singleton<T>::s_instance = 0;

} // namespace zn

#endif // ZN_SINGLETON_HPP_INCLUDED


