/*
Slider.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_UI_SLIDER_HPP
#define ZN_UI_SLIDER_HPP

#include "../Widget.hpp"
#include "../Signal.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief A basic slider (without arrows).
	 */
	class Slider : public AWidget
	{
	public:

		enum Orientation
		{
			HORIZONTAL,
			VERTICAL
		};

		Slider();
		virtual ~Slider() {}

		WidgetType getType() const override { return SLIDER; }

		void setRatio(float ratio);
		inline float getRatio() const { return m_ratio; }

		inline void setOrientation(Orientation orient) { m_orientation = orient; }
		inline Orientation getOrientation() const { return m_orientation; }

		Signal1<float> onValueChangedSignal;

	protected:

		virtual void renderSelf(IRenderer &r) override;

		virtual bool mouseMoved(int oldX, int oldY, int newX, int newY) override;
		virtual bool keyPressed(Keyboard::Key key) override;

	private:

		float m_ratio;
		Orientation m_orientation;
	};

} // namespace ui
} // namespace zn

#endif // ZN_UI_SLIDER_HPP



