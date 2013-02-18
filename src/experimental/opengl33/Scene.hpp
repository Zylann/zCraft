#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <unordered_map>
#include "SceneNode.hpp"

namespace experimental
{
namespace gl
{
	class Scene
	{
	public :

		// Constructs an empty scene
		Scene();

		// Destroys the scene and all of its nodes
		~Scene();

		// Adds a node to the scene and sets its ID.
		// Returns the ID.
		engine::u32 addNode(ISceneNode * sceneNode);

		// Gets a node from its ID
		ISceneNode * getNode(engine::u32 ID);

		// Removes a node from the scene without destroy it.
		// ID: the ID of the node
		ISceneNode * removeNode(engine::u32 ID);

		// Removes and destroys a node from the scene
		// ID: the ID of the node
		bool eraseNode(engine::u32 ID);

		// Draws everything
		void renderAll();

		inline engine::u32 getNodeCount() const { return m_nodes.size(); }

	private :

		void clear();

		engine::u32 makeID();

		std::unordered_map<engine::u32, ISceneNode*> m_nodes;
		engine::u32 m_counterID = 0;

	};

} // namespace gl
} // namespace experimental

#endif // SCENE_HPP_INCLUDED


