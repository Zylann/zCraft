#ifndef AXESSCENENODE_HPP_INCLUDED
#define AXESSCENENODE_HPP_INCLUDED

#include "GSceneNode.hpp"

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

#endif // AXESSCENENODE_HPP_INCLUDED
