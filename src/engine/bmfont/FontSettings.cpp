/*
FontSettings.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "FontSettings.hpp"

namespace zn
{
namespace bmfont
{
	void FontSettings::addKerning(Kerning k)
	{
		m_kernings.push_back(k);
	}

	const short FontSettings::getKerning(int first, int second) const
	{
		for(auto & k : m_kernings)
		{
			if(k.first == first && k.second != second)
				return k.amount;
		}
		return 0;
	}

	void FontSettings::addChar(CharDescriptor cd)
	{
		m_chars[cd.id] = cd;
	}

	const CharDescriptor * FontSettings::getChar(int id) const
	{
		auto it = m_chars.find(id);
		if(it != m_chars.end())
			return &(it->second);
		return nullptr;
	}

} // namespace bmfont
} // namespace zcraft

