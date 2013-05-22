/*
Text.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_TEXT_HPP_INCLUDED
#define ZENGUI_TEXT_HPP_INCLUDED

#include <vector>
#include "../Widget.hpp"
#include "../Font.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief A basic widget for displaying text.
	 */
	class Text : public AWidget
	{
	public :

		struct Pos
		{
			unsigned int line;
			unsigned int col;

			Pos() : line(0), col(0) {}

			Pos(unsigned int line0, unsigned int col0)
				: line(line0), col(col0)
			{}
		};

		Text();
		virtual ~Text();

		WidgetType getType() const override { return TEXT; }

		void setWrap(bool enable);

		void setFont(Font & font);
		inline Font * getFont() { return r_font; }

		void setText(const std::wstring & text);
		inline const std::wstring & getText() const { return m_sourceText; }

		const std::wstring & getLine(unsigned int index) const;
		inline unsigned int getLineCount() const { return m_lines.size(); }

		Vector2i getCharacterPos(unsigned int col, unsigned int line=0);
		Pos getColumnAndLine(int x, int y);

		void setSecret(bool s);
		inline bool isSecret() const { return m_secret; }

	protected :

		void renderSelf(IRenderer & r) override;

		virtual void onSizeChanged() override;

	private :

		struct Line
		{
			std::wstring str;
			IntRect bounds;
		};

		void updateText(const IRenderer * renderer = nullptr);

		std::wstring m_sourceText;
		std::vector<Line> m_lines;
		Font * r_font;
		bool m_textNeedUpdate;
		bool m_wrap;
		bool m_secret;

	};

} // namespace ui
} // namespace zn


#endif // ZENGUI_TEXT_HPP_INCLUDED
