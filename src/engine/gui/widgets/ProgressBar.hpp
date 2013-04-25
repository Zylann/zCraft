/*
ProgressBar.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_UI_PROGRESSBAR_HPP
#define ZN_UI_PROGRESSBAR_HPP

#include "../Widget.hpp"
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	class ProgressBar : public AWidget
	{
	public:

		ProgressBar() { m_blocksInput = false; }
		virtual ~ProgressBar() {}

		void setRatio(float ratio)
		{
			m_ratio = ratio < 0 ? 0 : ratio > 1 ? 1 : ratio;
		}

		inline float getRatio() const { return m_ratio; }

	protected:

		virtual void renderSelf(IRenderer &r) override
		{
			r_skin->drawProgressBar(r, *this, m_ratio);
		}

	private:

		float m_ratio;

	};

} // namespace ui
} // namespace zn

#endif // ZN_UI_PROGRESSBAR_HPP



