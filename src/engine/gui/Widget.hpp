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
#include "WidgetType.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief Defines borders of a rectangle.
	 */
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

	/**
	 * @brief Alignment bits.
	 * Can be combinated with '|' to define a specific alignemnt.
	 */
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

//	struct Identifier // Just a draft. May be in future code.
//	{
//		std::string ID; // Widget identifier (but user-defined, should be unique)
//		std::string group; // Widget group (user-defined)
//		std::string type; // Widget type
//	};

	class Root;
	class AComposite;
	class ISkin;
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
	public :

		AWidget()
		:   m_align(Align::NONE),
            r_skin(nullptr),
            m_visible(true),
            m_enabled(true),
            m_hovered(false),
            m_pressed(false),
            m_focused(false),
            m_blocksInput(true),
            r_parent(nullptr)
		{}

		virtual ~AWidget() {}

		/**
			Geometry & appearance
		**/

		// Sets the fixed bounds of the widget.
		// Should only be used for fixed-size layouts.
		void setBounds(IntRect globalBounds); // Global
		void setLocalBounds(IntRect bounds);

		// Returns widget's bounds including its margin.
		IntRect getBounds() const; // Global
		IntRect getLocalBounds() const;

		// Returns widget's bounds including its margin (convenience).
		IntRect getOuterBounds() const; // Global
		IntRect getLocalOuterBounds() const;

		// Returns widget's bounds including its padding (convenience).
		IntRect getInnerBounds() const; // Global
		IntRect getLocalInnerBounds() const;

		// Get absolute position of the upper-left corner of the widget.
		Vector2i getGlobalPosition() const;

		// Sets the size limit the widget should have.
		void setSizeLimits(const Vector2i & minSize, const Vector2i & maxSize);

		// Sets the margins of the widget.
		void setMargin(const Margin & m);

		// Sets the inner margins of the widget
		void setPadding(const Padding & p);

		inline const Margin & getMargin() const { return m_margin; }
		inline const Padding & getPadding() const { return m_padding; }

		// Sets the theme used by this widget directly from a skin object.
		// If recursive is set to true, the theme will be applied to all of children too.
		// Note : the theme has to be deleted manually after use.
		virtual void setSkin(ISkin & skin, bool recursive = true);

		// Sets the preferred alignment this widget should have.
		// It will be ignored in certain cases depending on the layout of
		// the container.
		void setAlign(unsigned char align);

		inline unsigned char getAlign() const { return m_align; }

		// Updates widget's position and size depending on the given space to occuppy.
		// If called on a composite, the composite will call layout()
		// recursively on its children.
		virtual void layout(IntRect space);

		// Updates widget's position and size depending on parent's space.
//		virtual void layout();

		/**
			State
		**/

		inline bool isVisible() const { return m_visible; }
		inline bool isEnabled() const { return m_enabled; }
		inline bool isHovered() const { return m_hovered; }
		inline bool isPressed() const { return m_pressed; }
		inline bool isFocused() const { return m_focused; }

		inline void setEnabled(bool e) { m_enabled = e; }

		// Sets the widget as focused, and unfocuses the other if there is one.
		virtual void setFocused(bool f);

		// Sets the widget as hovered, and triggers onMouseOver/onMouseQuit
		void setHovered(bool h);

		virtual void show();
		virtual void hide();

		/**
			Hierarchy & appearance
		**/

		// Returns the parent of the widget.
		// If null, the widget is then the top-level (Root).
		inline AComposite * getParent() const { return r_parent; }

		/**
		 * @brief Returns the parent of the widget as read-only.
		 * @return the parent, or nullptr if the widget is on top-level.
		 */
		inline const AComposite * getParentConst() const { return r_parent; }

		// Get top-level widget by recursive search.
		virtual Root * getRoot();

		/**
		 * @brief Brings the widget in front of the others within its container.
		 * @param upwardRecursive : if set to true, the parent will also
		 * be brang to front and so on.
		 */
		void bringToFront(bool upwardRecursive = false);

		// Gets the internal type of this widget.
		// Note : custom types are not supported yet, so you may use IDs in this case.
		virtual WidgetType getType() const { return GENERIC; }

		// Get the user-defined ID of the widget
		inline const std::string & getID() const { return m_ID; }

		// Sets the user-defined ID of the widget (like CSS-HTML IDs).
		// Note : using two same IDs will not cause a GUI error.
		// it's up to the user to dispose of it as a unique ID.
		// (however, future versions of the GUI may implement checking)
		inline void setID(const std::string ID) { m_ID = ID; }

		// This is specifically used when the widget is added to a container.
		// Do NOT use this method outside that case.
		// Will not work if the widget already have a parent.
		void setParent(AComposite * w);

		// Tells if the widget blocks consume events it receives.
		inline bool blocksInput() const { return m_blocksInput; }

		// Gets how many widgets are contained into the widget.
		virtual unsigned int getChildCount() const { return 0; }

		/**
			Main loop
		**/

		// Draws the widget and all of its contents
		virtual void render(IRenderer & r);

		// Animates the widget for a given time delta (in seconds).
		// Implementation is optionnal.
		virtual void animate(float /* dt */) {}

	protected :

		// Draws only the widget (not his children).
		// This method is called only if it is really needed
		// (ie. it's not required to check if the widget is visible or
		// if the skin is defined).
		virtual void renderSelf(IRenderer & r);

		/**
			Input callbacks
		**/

		virtual bool mouseMoved(int oldX, int oldY, int newX, int newY) override;
		virtual bool mousePressed(Mouse::Button button) override;
		virtual bool mouseReleased(Mouse::Button button) override;
		virtual bool mouseWheelMoved(int delta) override;

		virtual bool keyPressed(Keyboard::Key key) override;
		virtual bool keyReleased(Keyboard::Key key) override;
		virtual bool textEntered(unsigned int unicode) override;

		/**
			State change notifications
		**/

		virtual void onSizeChanged() {}

		virtual void onPress() {}
		virtual void onRelease() {}

//		virtual void onMouseEnter() {}
//		virtual void onMouseQuit() {}

//		virtual void onFocusOn() {}
//		virtual void onFocusOff() {}

//		virtual void onShow() {}
//		virtual void onHide() {}

	private :

		// Updates widget's size according to its limits.
		// It does this ONLY for this widget (parent and children are ignored)
		bool applySizeLimit();

	protected :

		/** Geometry & appearance **/

		IntRect m_localBounds; // parent-relative bounds
		IntRect m_sizeLimit;

		Margin m_margin;
		Padding m_padding;

		// How the widget should use the space where it is
		unsigned char m_align;

		ISkin * r_skin;

		/** State **/

		bool m_visible; // Is the widget visible?
		bool m_enabled; // Can we interact with the widget?
		bool m_hovered; // Is the mouse over the widget?
		bool m_pressed; // Are we pressing the widget (i.e. mouseDown) ?
		bool m_focused; // Does this widget has the focus?

		bool m_blocksInput;

		/** Hierarchy & identification **/

		// Note : "r_" means that we use this pointer as a reference.
		// we don't have the right to delete pointed data.
		AComposite * r_parent;

		// This is a user-set identifier that can be used for debug,
		// style or script selection. Empty value is ignored.
		std::string m_ID;

	};

} // ui
} // zn

#endif // ZENGUI_WIDGET_HPP_INCLUDED


