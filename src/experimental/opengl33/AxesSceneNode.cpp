/*
AxesSceneNode.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

//#include <iostream>
#include "opengl3.hpp"
#include "AxesSceneNode.hpp"

namespace experimental
{
namespace gl
{
	AxesSceneNode::AxesSceneNode() : ISceneNode()
	{
	}

	AxesSceneNode::~AxesSceneNode()
	{
	}

	void AxesSceneNode::render()
	{
		// Immediate rendering in OpenGL 3.1
		gl::drawAxes();
	}

} // namespace gl
} // namespace experimental


