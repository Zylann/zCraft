/*
Root.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Root.hpp"

namespace zn
{
namespace ui
{
	unsigned int g_instanceCount = 0;

	Root::Root(unsigned int width, unsigned int height) : AContainer()
	{
		m_bounds.set(0, 0, width, height);
		g_instanceCount++;

		m_blocksInput = false;

		if(g_instanceCount > 1)
		{
			std::cout << "WARNING: GUI Root should only be created once !" << std::endl;
		}
	}

	Root::~Root()
	{
		if(m_renderer != nullptr)
			delete m_renderer;
	}

	void Root::setRenderer(IRenderer * r)
	{
		if(r == nullptr)
		{
			std::cout << "ERROR: Root::setRenderer: "
				<< "cannot set null renderer." << std::endl;
			return;
		}
		if(r == m_renderer)
		{
			std::cout << "WARNING: Root::setRenderer: "
				<< "same renderer set twice" << std::endl;
			return;
		}
		if(m_renderer != nullptr)
		{
			std::cout << "INFO: Switching GUI renderer" << std::endl;
			delete m_renderer;
		}
		m_renderer = r;
	}

	void Root::render()
	{
		if(m_renderer != nullptr)
		{
			m_renderer->begin();
			AContainer::render(*m_renderer);
			m_renderer->end();
		}
	}


} // namespace ui
} // namespace zn
