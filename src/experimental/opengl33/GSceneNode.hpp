#ifndef SCENENODE_HPP_INCLUDED
#define SCENENODE_HPP_INCLUDED

#include "engine/core/types.hpp"

// TODO GSceneNode: rename when QBS will allow two files with same name

namespace experimental
{
namespace gl
{
	class ISceneNode
	{
	public :

		zn::u32 ID = -1;

		virtual ~ISceneNode() {}

		virtual void render() = 0;

	};

} // namespace gl
} // namespace experimental

#endif // SCENENODE_HPP_INCLUDED