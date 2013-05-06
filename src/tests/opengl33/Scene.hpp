#ifndef TEST_SCENE_HPP_INCLUDED
#define TEST_SCENE_HPP_INCLUDED

#include <unordered_map>
#include "SceneNode.hpp"

// TODO GSceneNode: rename when QBS will allow two files with same name

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
		zn::u32 addNode(ISceneNode * sceneNode);

		// Gets a node from its ID
		ISceneNode * getNode(zn::u32 ID);

		// Removes a node from the scene without destroy it.
		// ID: the ID of the node
		ISceneNode * removeNode(zn::u32 ID);

		// Removes and destroys a node from the scene
		// ID: the ID of the node
		bool eraseNode(zn::u32 ID);

		// Draws everything
		void renderAll();

		inline zn::u32 getNodeCount() const { return m_nodes.size(); }

	private :

		void clear();

		zn::u32 makeID();

		std::unordered_map<zn::u32, ISceneNode*> m_nodes;
		zn::u32 m_counterID = 0;

	};

} // namespace gl
} // namespace experimental

#endif // TEST_SCENE_HPP_INCLUDED


