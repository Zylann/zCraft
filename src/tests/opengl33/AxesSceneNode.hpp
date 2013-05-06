#ifndef TEST_AXESSCENENODE_HPP_INCLUDED
#define TEST_AXESSCENENODE_HPP_INCLUDED

#include "SceneNode.hpp"

namespace experimental
{
namespace gl
{
	class AxesSceneNode : public ISceneNode
	{
	public :

		AxesSceneNode();

		virtual ~AxesSceneNode();

		void render() override;

	};

} // namespace gl
} // namespace experimental

#endif // TEST_AXESSCENENODE_HPP_INCLUDED
