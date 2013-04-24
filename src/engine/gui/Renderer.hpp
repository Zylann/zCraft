/*
IRenderer.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_IRENDERER_HPP_INCLUDED
#define ZENGUI_IRENDERER_HPP_INCLUDED

#include <string>

// Note : these includes are the only dependencies of GUI's core.
// they exist because this GUI is being developped as part of the zCraft project,
// but once copied it is fully independent.
#include "Color.hpp"
#include "Rect.hpp" // also includes Vector2
#include "Texture.hpp"
#include "Font.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief An implementation of this interface must be used for the
	 * GUI to render things.
	 */
	class IRenderer
	{
	public :

		IRenderer() {}
		virtual ~IRenderer() {}

		/*
			Lifecycle
		*/

		/**
		 * @brief Called when the gui rendering starts
		 */
		virtual void begin() = 0;

		/**
		 * @brief Called at the end of gui rendering
		 */
		virtual void end() = 0;

		/*
			Media resources

			The gui doesn't hold resources, but identifiers and some metadata.
			Loading methods require the user to fill the given structs, as they will
			be re-used in rendering code or by the gui.
		*/

		// Called when the gui needs a texture.
		// Return true if success, false if failed.
		virtual bool loadTexture(Texture & texture) = 0;

		// Called when the GUI doesn't needs a texture anymore.
		// Return true if success, false if failed.
		virtual bool freeTexture(Texture & texture) = 0;

		// Called when the gui needs a font.
		// Return true if success, false if failed.
		virtual bool loadFont(Font & font) = 0;

		// Called when the GUI doesn't needs a font anymore.
		// Return true if success, false if failed.
		virtual bool freeFont(Font & font) = 0;

		/*
			Renderer state options
		*/

		// Sets the color that will be used for next drawings.
		virtual void setColor(const Color & color) = 0;

		// Sets the line width that will be used for next drawings.
		virtual void setLineWidth(unsigned int w) = 0;

		// Sets the texture that will be used for next drawings.
		// The specified ID is the one created with loadTexture().
		virtual void setTexture(Texture & texture) = 0;

		// Sets the texture sub-rectangle that will be used for next drawings.
		virtual void setTextureClip(const IntRect clip) = 0;

		// Sets the font that will be used for next text-renderings
		virtual void setFont(Font & font) = 0;

		/*
			Drawing
		*/

		// Draws a line from (xa,ya) to (xb,yb).
		virtual void drawLine(float xa, float ya, float xb, float yb) = 0;

		// Draws a coloured rectangle defined by a top-left corner at (x,y) and a size.
		// If fill is false, only the border must be rendered.
		virtual void drawRect(IntRect r, bool fill) = 0;

		// Draws the given text from the (x,y) position.
		// begin and end refer to the starting and ending index of the string to draw.
		virtual void drawText(const std::string & text, int x, int y, int begin, int end) = 0;

		/*
			Misc
		*/

		/**
		 * @brief Get the size of a text written using the given font.
		 *  Whitespace must be included in the size.
		 * @param font : font used
		 * @param text : text to measure with the font
		 * @param begin : first character
		 * @param end : last character. A negative or greater than text.size() value
		 * means the entire text must be measured.
		 * @return width and height or the measured text.
		 */
		virtual Vector2i getTextSize(
			Font & font, const std::string & text, int begin, int end) const = 0;

		// Get the height of a line written with the given font
		virtual int getFontLineHeight(Font & font) const = 0;

		// Returns the character index at which a text crosses the given max width.
//		virtual unsigned int getCrossCharIndex(
//			Font & font, const std::string & text, int maxWidth, int begin, int end) = 0;

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_IRENDERER_HPP_INCLUDED



