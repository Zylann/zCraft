/*
Scene.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_GAME_SCENE_HPP
#define ZN_GAME_SCENE_HPP

#include "Entity.hpp"

namespace zn
{
	class Scene : public Entity
	{
	public:

		Scene();
		~Scene();

		virtual void init() override;
		virtual void update(const Time & delta) override;
		virtual void render() override;
		virtual void dispose() override;

		const Scene * getScene() const override { return this; }

		virtual Entity * addChild(Entity *newEntity) override;

	};

} // namespace zn

#endif // ZN_GAME_SCENE_HPP


