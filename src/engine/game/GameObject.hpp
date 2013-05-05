/*
GameObject.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_AGAMEOBJECT_HPP
#define ZN_GAME_AGAMEOBJECT_HPP

#include <string>
#include <iostream>
#include "../core/types.hpp"
#include "../system/Time.hpp"
//#include "../core/serialization.hpp"

namespace zn
{
	class AGameObject
	{
	public:

		static const u32 NULL_ID = 0;

		enum FlagBits
		{
			INITIALIZED =	1,
			DISPOSED =		1 << 1,
			ENABLED =		1 << 2
		};

		AGameObject() {}
		virtual ~AGameObject() {}

		virtual void init() { onInit(); }
		virtual void update(const Time & delta) { onUpdate(delta); }
		virtual void dispose() { m_flags |= DISPOSED; onDispose(); }

		inline bool isInitialized() const { return m_flags & INITIALIZED; }
		inline bool isDisposed() const { return m_flags & DISPOSED; }
		inline bool isEnabled() const { return m_flags & ENABLED; }

		inline void enable() { m_flags |= ENABLED; }
		inline void disable() { m_flags &= ~ENABLED; }

		inline u32 getID() const { return m_ID; }

		void setID(u32 ID)
		{
			if(m_ID == NULL_ID)
				m_ID = ID;
			else
			{
				std::cout << "ERROR: AGameObject::setID: "
							 "cannot override an already set ID !" << std::endl;
			}
		}

//		virtual void writeToBinary(std::ostream & os) const
//		{
//			serialize(os, name);
//			serialize(os, m_ID);
//			serialize(os, m_flags);
//		}

//		virtual void readFromBinary(std::istream & is)
//		{
//			unserialize(os, name);
//			unserialize(os, m_ID);
//			unserialize(os, m_flags);
//		}

		std::string name;

	protected:

		/**
		 * The methods below are reserved to the game layer,
		 * and shouldn't have an implementation in the engine layer.
		 */

		virtual void onInit() {}
		virtual void onUpdate(const Time & /*delta*/) {}
		virtual void onDispose() {}

	private:

		u32 m_ID = NULL_ID;
		u8 m_flags = 0;

	};

} // namespace zn

#endif // ZN_GAME_AGAMEOBJECT_HPP


