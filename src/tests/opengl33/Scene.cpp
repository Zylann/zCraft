/*
Scene.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Scene.hpp"
#include "engine/core/types.hpp"

// TODO GScene: rename when QBS will allow two files with same name

using namespace zn;

namespace experimental
{
namespace gl
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		clear();
	}

	u32 Scene::makeID()
	{
		++m_counterID;
		return m_counterID;
	}

	void Scene::clear()
	{
		for(auto it = m_nodes.begin(); it != m_nodes.end(); it++)
		{
			delete it->second;
		}
	}

	u32 Scene::addNode(ISceneNode * sceneNode)
	{
		const u32 ID = makeID();
		sceneNode->ID = ID;
		m_nodes[ID] = sceneNode;
		return ID;
	}

	ISceneNode * Scene::getNode(u32 ID)
	{
		auto it = m_nodes.find(ID);
		if(it == m_nodes.end())
			return nullptr;
		return it->second;
	}

	ISceneNode * Scene::removeNode(u32 ID)
	{
		auto it = m_nodes.find(ID);
		if(it == m_nodes.end())
			return nullptr;
		ISceneNode * node = it->second;
		m_nodes.erase(it);
		return node;
	}

	bool Scene::eraseNode(u32 ID)
	{
		ISceneNode * node = removeNode(ID);
		if(node == nullptr)
			return false;
		delete node;
		return true;
	}

	void Scene::renderAll()
	{
		for(auto & p : m_nodes)
			p.second->render();
	}

} // namespace gl
} // namespace experimental



