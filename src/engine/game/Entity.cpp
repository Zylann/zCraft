#include "Entity.hpp"
#include "Scene.hpp"

namespace zn
{
	Entity::Entity() : AGameObject()
	{
		r_parent = nullptr;
	}

	Entity::~Entity()
	{
		m_children.deleteAll();
		m_components.deleteAll();
		if(m_renderer != nullptr)
			delete m_renderer;
	}

	const Scene * Entity::getScene() const
	{
		if(r_parent != nullptr)
			return r_parent->getScene();
		return nullptr;
	}

	Entity *Entity::addChild(Entity *newEntity)
	{
		if(newEntity == nullptr)
		{
			std::cout << "ERROR: Entity::addChild: received nullptr." << std::endl;
			return nullptr;
		}
		m_children.stage(newEntity);
		newEntity->r_parent = this;
		return newEntity;
	}

	Entity * Entity::findChild(u32 ID)
	{
		return m_children.find(ID);
	}

	Entity * Entity::findChild(const std::string & name)
	{
		return m_children.find(name);
	}

	void Entity::update(const Time &delta)
	{
		m_components.updateAll(delta);

		for(Entity *& e : m_children)
			e->update(delta);

		if(m_renderer != nullptr)
			m_renderer->update(delta);
	}

	void Entity::render()
	{
		if(m_renderer != nullptr)
			m_renderer->render();
	}

} // namespace zn




