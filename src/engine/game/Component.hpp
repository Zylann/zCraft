/*
Component.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_ACOMPONENT_HPP
#define ZN_GAME_ACOMPONENT_HPP

#include "GameObject.hpp"
#include "GameObjectList.hpp"
#include "InternalComponentType.hpp"

namespace zn
{
	class AComponent;
	class Entity;

	typedef GameObjectList<AComponent> ComponentList;

	class AComponent : public AGameObject
	{
	public:

		AComponent() : AGameObject() {}
		virtual ~AComponent() {}

		inline const Entity * getOwner() const { return r_owner; }

		virtual u16 getInternalType() const { return BASIC_COMPONENT; }

	protected:

		friend class Entity;

		Entity * r_owner = nullptr;

	};

} // namespace zn

#endif // ZN_GAME_ACOMPONENT_HPP




