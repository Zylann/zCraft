/*
GameObjectList.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_GAMEOBJECTLIST_HPP
#define ZN_GAME_GAMEOBJECTLIST_HPP

#include <list>
#include <string>
#include "../core/types.hpp"
#include "../system/Time.hpp"

namespace zn
{
	/**
	 * @brief A generic container for GameObjects,
	 * with some handy methods. Add objects using stage(obj).
	 * remove them by calling their dispose() method, and the next call
	 * to updateAll() or flush() will actually delete them.
	 * the reason for this is to enable modification while iterating,
	 * and appropriately call virtual lifecycle methods of GameObject.
	 * @note It has been designed to be integrated in a main-loop-based
	 * architecture. If you want to save objects, don't forget to call flush()
	 * before.
	 */
	template <class GameObj_T>
	class GameObjectList
	{
	public:

		typedef typename std::list<GameObj_T*>::iterator Iterator;
		typedef typename std::list<GameObj_T*>::const_iterator ConstIterator;

		GameObjectList() {}

		~GameObjectList()
		{
			deleteAll();
		}

		void stage(GameObj_T * obj)
		{
			if(obj != nullptr)
				m_objects.push_back(obj);
		}

		void updateAll(const Time & delta)
		{
			// Stage newly added objects
			for(GameObj_T*& obj : m_stagedObjects)
			{
				obj->init();
				m_objects.push_back(obj);
			}

			// Update objects and pool disposed ones
			std::list<GameObj_T*> disposedObjects;
			for(GameObj_T*& obj : m_objects)
			{
				if(obj->isDisposed())
					disposedObjects.push_back(obj);
				else
				{
					if(obj->isEnabled())
						obj->update(delta);
				}
			}

			// Destroy disposed objects
			for(GameObj_T*& obj : disposedObjects)
			{
				m_objects.remove(obj);
				delete obj;
			}
		}

		void flush()
		{
			// Stage newly added objects
			for(GameObj_T*& obj : m_stagedObjects)
			{
				obj->init();
				m_objects.push_back(obj);
			}

			// Destroy disposed objects
			for(GameObj_T*& obj : m_objects)
			{
				if(obj->isDisposed())
				{
					m_objects.remove(obj);
					delete obj;
				}
			}
		}

		GameObj_T * find(const std::string & name)
		{
			for(GameObj_T*& obj : m_objects)
			{
				if(obj->name == name)
					return obj;
			}
			return nullptr;
		}

		GameObj_T * find(const u32 ID)
		{
			for(GameObj_T*& obj : m_objects)
			{
				if(obj->getID() == ID)
					return obj;
			}
			return nullptr;
		}

		bool contains(GameObj_T * obj1)
		{
			for(GameObj_T*& obj2 : m_objects)
			{
				if(obj1 == obj2)
					return true;
			}
			return false;
		}

		void deleteAll()
		{
			for(GameObj_T*& obj : m_stagedObjects)
			{
				delete obj;
			}
			for(GameObj_T*& obj : m_objects)
			{
				delete obj;
			}
			m_stagedObjects.clear();
			m_objects.clear();
		}

		inline u32 count() const { return m_objects.size(); }
		inline u32 stagedCount() const { return m_stagedObjects.size(); }

		inline Iterator begin() { return m_objects.begin(); }
		inline Iterator end() { return m_objects.begin(); }

		inline ConstIterator cbegin() const { return m_objects.cbegin(); }
		inline ConstIterator cend() const { return m_objects.cend(); }

	private:

		std::list<GameObj_T*> m_stagedObjects;
		std::list<GameObj_T*> m_objects;
	};

} // namespace zn


#endif // ZN_GAME_GAMEOBJECTLIST_HPP


