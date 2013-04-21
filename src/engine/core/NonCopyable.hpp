/*
NonCopyable.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_NONCOPYABLE_HPP
#define ZN_NONCOPYABLE_HPP

namespace zn
{
	/**
	 * @brief A non-copyable type.
	 * Classes inheriting NonCopyable cannot be copied.
	 * @note There is a better C++11 way to do this with =delete and =default,
	 * but at the moment I keep this class compatible with C++03.
	 */
	class NonCopyable
	{
	protected :

		/**
		 * @brief Because this class has a copy constructor, the compiler
		 * will not automatically generate the default constructor.
		 * That's why we must define it explicitely.
		 * @note you are not required to call NonCopyable() in the initialization
		 * list of your inheriting class, because NonCopyable has no member to
		 * initialize.
		 */
		NonCopyable() {}
		virtual ~NonCopyable() {}

	private :

		/**
		 * @brief Disabled copy constructor :
		 * By making the copy constructor private, the compiler will
		 * trigger an error if anyone outside tries to use it.
		 * To prevent NonCopyable or friend classes from using it,
		 * we also give no definition, so that the linker will
		 * produce an error if the first protection was inefficient.
		 */
		NonCopyable(const NonCopyable&);

		/**
		 * @brief Disabled operator = :
		 * By making the assignment operator private, the compiler will
		 * trigger an error if anyone outside tries to use it.
		 * To prevent NonCopyable or friend classes from using it,
		 * we also give no definition, so that the linker will
		 * produce an error if the first protection was inefficient.
		 */
		NonCopyable & operator=(const NonCopyable&);

	};

} // namespace zn

#endif // ZN_NONCOPYABLE_HPP



