/*
Scene.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Scene.hpp"

namespace zn
{
	Scene::Scene() : Entity()
	{
		name = "Scene";
	}

	Scene::~Scene()
	{
	}

	void Scene::init()
	{
		Entity::init();
	}

	void Scene::update(const Time & delta)
	{
		Entity::update(delta);
	}

	void Scene::dispose()
	{
		Entity::dispose();
	}

	Entity *Scene::addChild(Entity *newEntity)
	{
		return Entity::addChild(newEntity);
	}

	void Scene::render()
	{
		Entity::render();
	}

} // namespace zn



