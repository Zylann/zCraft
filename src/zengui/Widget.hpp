/*
Widget.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_WIDGET_HPP_INCLUDED
#define ZENGUI_WIDGET_HPP_INCLUDED

#include "Signal.hpp"
#include "InputListener.hpp"
#include "Rect.hpp"

namespace zn
{
namespace ui
{
	// Note : coordinates use 2D axes where Y goes down
	struct RectBorder
	{
		short left;
		short right;
		short top;
		short bottom;

		RectBorder() : left(0), right(0), top(0), bottom(0) {}
		RectBorder(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
	};

	typedef RectBorder Margin;
	typedef RectBorder Padding;

	enum Align // Should fit in a byte
	{
		NONE 		= 0,
		LEFT 		= 1,
		RIGHT 		= (1 << 1),
		TOP 		= (1 << 2),
		BOTTOM 		= (1 << 3),
		CENTER_H 	= (1 << 4),
		CENTER_V 	= (1 << 5),
		CENTER 		= CENTER_V | CENTER_H,
		FILL_H 		= (1 << 6),
		FILL_V		= (1 << 7),
		FILL		= FILL_V | FILL_H
	};

	class Root;
	class AContainer;
	class ITheme;
	class IRenderer;

	/*
		This is the base class for all controls and containers.

		+- - - - - - - - - - - - - - - - - +
		| +------------------------------+ |
		  | +- - - - - - - - - - - - - + |
		| | |         Content          | | |
		  | +- - - - - - - - - - - - - + |
		| |           Padding            | |
		  +------------------------------+
		|             Margins              |
		+- - - - - - - - - - - - - - - - - +
	*/
	class AWidget : public IInputListener
	{
	protected :

		/* Style */

		IntRect m_bounds; // parent-relative bounds
		IntRect m_sizeLimit;

		Margin m_margin;
		Padding m_padding;

		Align m_align = Align::NONE;

		ITheme * r_theme = nullptr;

		/* State */

		bool m_visible; // Is the widget visible?
		bool m_enabled; // Can we interact with the widget?
		bool m_hovered; // Is the mouse over the widget?
		bool m_pressed; // Are we pressing the widget (i.e. mouseDown) ?
		bool m_focused; // Does this widget has the focus?

		bool m_blocksInput = true;

		/* Hierarchy */

		// Note : "r_" means that we use this pointer as a reference.
		// we don't have the right to delete pointed data.
		AContainer * r_parent = nullptr;

		// This is a user-set identifier that can be used for debug,
		// style or script selection. Empty value is ignored.
		std::string m_ID;

	public :

		/*
			Ctor/dtor
		*/

		AWidget() {}
		virtual ~AWidget() {}

		/*
			Style
		*/

		// Sets fixed size of the widget.
		// Note : this should be used for fixed-position layouts only.
		void setBounds(IntRect bounds);

		// Returns current bounds of the widget.
		inline const IntRect & getBounds() const { return m_bounds; }

		// Returns parent-relative widget's bounds including its margins
		IntRect getOuterBounds() const;

		// Returns widget's inner bounds including its padding.
		// This is relative to the widget itself.
		IntRect getInnerBounds() const;

		// Get parent-relative X coordinate
		inline int getX() const { return m_bounds.min.x; }

		// Get parent-relative Y coordinate
		inline int getY() const { return m_bounds.min.y; }

		// Get absolute position
		Vector2i getAbsolutePosition() const;

		// Sets the size limit the widget should have.
		void setSizeLimits(const Vector2i & minSize, const Vector2i & maxSize);

		// Sets the margins of the widget.
		void setMargin(const Margin & m);

		// Sets the inner margins of the widget
		void setPadding(const Padding & p);

		inline const Margin & getMargin() const { return m_margin; }
		inline const Padding & getPadding() const { return m_padding; }

		// Sets the theme used by this widget.
		// If recursive is set to true, the theme will be applied to all of children too.
		// Note : the theme has to be deleted manually after use.
		virtual void setTheme(ITheme & theme, bool recursive = true);

		// Sets the preferred alignment this widget should have.
		// It will be ignored in certain cases depending on the layout of
		// the container.
		void setAlign(Align align);

		inline Align getAlign() const { return m_align; }

		// Updates widget's position and size according to align,
		// size and parent constraints.
		// Returns true if the widget changed its geometry, false if not.
		virtual void layout();

		/*
			State
		*/

		inline bool isVisible() const { return m_visible; }
		inline bool isEnabled() const { return m_enabled; }
		inline bool isHovered() const { return m_hovered; }
		inline bool isPressed() const { return m_pressed; }
		inline bool isFocused() const { return m_focused; }

		inline void setEnabled(bool e) { m_enabled = e; }

		// Sets the widget as focused.
		// Warning: this is just a setter, other widgets will not loose focus !
		inline void setFocused(bool f) { m_focused = f; }

		virtual void show();
		virtual void hide();

		// Sets the widget as focused (when available) and removes focus from others
		void requestFocus();

		/*
			Hierarchy
		*/

		// Returns the parent of the widget.
		// If null, the widget is then the top-level (Root).
		inline AContainer * getParent() const { return r_parent; }

		// Get top-level widget by recursive search.
		virtual Root * getRoot();

		void bringToFront();

		inline const std::string & getID() const { return m_ID; }

		// Note : despite no ID unicity check isn't done,
		// the ID we specify have to be set to a unique value,
		// because it should matter in future updates (this is also why I
		// made a getter and a setter instead of putting the ID public).
		// Currently this is just a basic direct get/set attribute.
		inline void setID(const std::string ID) { m_ID = ID; }

		// This is specifically used when the widget is added to a container.
		// Do NOT use this method outside that case.
		// Will not work if the widget already have a parent.
		void setParent(AContainer * w);

		inline bool blocksInput() const { return m_blocksInput; }

		virtual unsigned int getChildCount() const { return 0; }

		/*
			Main loop
		*/

		// Draws the widget
		virtual void render(IRenderer & r);

		// Animates the widget for a given time delta (in seconds)
		virtual void animate(float dt) {};

	protected :

		/*
			Input
		*/

		virtual bool mouseMoved(int oldX, int oldY, int newX, int newY) override;
		virtual bool mousePressed(Mouse::Button button) override;
		virtual bool mouseReleased(Mouse::Button button) override;
		virtual bool mouseWheelMoved(int delta) override;

		virtual bool keyPressed(Keyboard::Key key, int unicode) override;
		virtual bool keyReleased(Keyboard::Key key) override;

		/*
			Basic state changes
			These methods are called from input methods.
		*/

		virtual void onPress() {}
		virtual void onRelease() {}

		virtual void onMouseEnter() {}
		virtual void onMouseQuit() {}

		virtual void onFocusOn() {}
		virtual void onFocusOff() {}

		virtual void onShow() {}
		virtual void onHide() {}

	private :

		// Updates widget's size according to its limits.
		// It does this ONLY for this widget (parent and children are ignored)
		bool applySizeLimit();

	};

} // ui
} // zn

#endif // ZENGUI_WIDGET_HPP_INCLUDED


