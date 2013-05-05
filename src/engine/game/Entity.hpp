/*
Entity.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_ENTITY_HPP
#define ZN_GAME_ENTITY_HPP

#include "GameObject.hpp"
#include "GameObjectList.hpp"
#include "Component.hpp"
#include "InternalEntityType.hpp"
#include "Drawable.hpp"
#include "EntityRenderer.hpp"

namespace zn
{
	class Entity;
	class Scene;

	typedef GameObjectList<Entity> EntityList;

	/**
	 * @brief Entities are the base of every gameplay-involved object
	 * in a scene. They contain components defining how they are rendered,
	 * how they sound and behave.
	 */
	class Entity : public AGameObject, IDrawable
	{
	public:

		Entity();
		~Entity();

		const Entity * getParent() const { return r_parent; }

		virtual const Scene * getScene() const;

		template <class Cmp_T>
		AComponent * add()
		{
			Cmp_T * cmp = new Cmp_T();
			// Note : if compilation fails here, that means you didn't
			// specified an AComponent-derivated type.
			if(addComponentCheck(cmp))
			{
				cmp.r_owner = this;
				return cmp;
			}
			else
			{
				std::cout << "ERROR: Entity::add<Cmp_T>: "
						  << "Couldn't add component." << std::endl;
				delete cmp;
				return nullptr;
			}
		}

		virtual Entity * addChild(Entity * newEntity);

		Entity * findChild(u32 ID);
		Entity * findChild(const std::string & name);

		virtual void update(const Time &delta) override;
		virtual void render() override;

		virtual u16 getInternalType() const { return BASIC_ENTITY; }

	protected:

		ComponentList m_components;
		EntityList m_children;
		Entity * r_parent;

		ARenderer * m_renderer;

	private:

		bool addComponentCheck(ARenderer * newRenderer)
		{
			if(m_renderer == nullptr)
			{
				m_renderer = newRenderer;
				return true;
			}
			else
			{
				std::cout << "ERROR: Entity::addComponentCheck: "
							"cannot override already set renderer !" << std::endl;
				return false;
			}
		}

		bool addComponentCheck(AComponent * newCmp)
		{
			m_components.stage(newCmp);
			return true;
		}

	};

} // namespace zn

#endif // ZN_GAME_ENTITY_HPP


