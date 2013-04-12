/*
Root.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Root.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	Root::Root(unsigned int width, unsigned int height) : AComposite()
	{
		m_localBounds.set(0, 0, width, height);
		m_blocksInput = false;
		setID("root");

		static int s_instanceCount = 0;
		++s_instanceCount;
		if(s_instanceCount > 1)
		{
			std::cout << "WARNING: GUI Root should only be created once !" << std::endl;
		}
	}

	Root::~Root()
	{
		// Release skins
		std::cout << "INFO: Releasing GUI skins..." << std::endl;
		for(auto & p : m_skins)
		{
			if(p.second != nullptr)
			{
				delete p.second;
			}
		}

		// Free renderer
		std::cout << "INFO: Releasing GUI renderer..." << std::endl;
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
			std::cout << "ERROR: Root::setRenderer: "
					  << " a renderer is already set."
					  << "switching renderer is not supported yet ! " << std::endl;
			delete m_renderer;
		}
		m_renderer = r;
	}

	bool Root::installSkin(ISkin *newSkin)
	{
		if(newSkin == nullptr)
		{
			std::cout << "ERROR: Root::installSkin: "
					  << "nullptr skin given." << std::endl;
			return false;
		}
		if(m_renderer == nullptr)
		{
			std::cout << "ERROR: Root::installSkin: "
					  << "a renderer must be setup before installing a skin." << std::endl;
			return false;
		}

		std::string name = newSkin->getName();
		auto it = m_skins.find(name);
		if(it != m_skins.end())
		{
			std::cout << "ERROR: Root::installSkin: "
					  << "can't install C++class-coded-skin. Cause : "
					  << "name is already used by an installed skin : "
					  << '"' << name << '"' << std::endl;
			return false;
		}
		else
		{
			if(!newSkin->load(*m_renderer))
			{
				std::cout << "ERROR: Root::installskin: "
						  << "an problem occurred while loading the skin." << std::endl;
				return false;
			}
			m_skins[name] = newSkin;
		}
		return true; // Success
	}

	void Root::render()
	{
		if(m_renderer != nullptr)
		{
			m_renderer->begin();
			AComposite::render(*m_renderer);
			m_renderer->end();
		}
	}

	void Root::setSkin(const std::string &name, bool recursive)
	{
		auto it = m_skins.find(name);
		if(it != m_skins.end())
		{
			//this->setSkin(*it->second, recursive);
			std::cout << "INFO: Set GUI skin : " << it->second->getName() << std::endl;
			AComposite::setSkin(*it->second, recursive);
		}
		else
		{
			std::cout << "ERROR: Root::setSkin: "
					  << "skin not found \"" << name << "\"" << std::endl;
		}
	}

} // namespace ui
} // namespace zn



