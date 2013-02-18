#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

#include "engine/types.hpp"

namespace experimental
{
namespace gl
{
	class ISceneNode
	{
	public :

		engine::u32 ID = -1;

		virtual ~ISceneNode() {}

		virtual void render() = 0;

	};

} // namespace gl
} // namespace experimental

#endif // SCENENODE_HPP_INCLUDED
