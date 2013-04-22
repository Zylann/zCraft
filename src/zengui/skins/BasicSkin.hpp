#ifndef ZENGUI_BASICSKIN_HPP
#define ZENGUI_BASICSKIN_HPP

#include <string>
#include "../Skin.hpp"

namespace zn
{
namespace ui
{
	/**
	 * @brief This is a simple skin that doesn't use textures.
	 * It can also be used as an example or base for custom skins.
	 */
	class BasicSkin : public zn::ui::ISkin
	{
	private :

		zn::ui::Font m_defaultFont;
		std::string m_name;

	public :

		/**
		 * @brief Constructs the skin.
		 * @name name of the skin to be used for identification (usually "Basic").
		 * @param globalFontFilepath : path to the global font.
		 * It will be named "global" for the renderer.
		 */
		BasicSkin(std::string name, std::string globalFontFilepath);
		virtual ~BasicSkin() {}

		virtual bool load(zn::ui::IRenderer & r) override;
		virtual bool unload(zn::ui::IRenderer & r) override;

		virtual zn::ui::Font & getDefaultFont() override;
		virtual std::string getName() override { return m_name; }

		virtual void drawDummyWidget(zn::ui::IRenderer & r, const zn::ui::AWidget & w) override;
		virtual void drawPanel(zn::ui::IRenderer & r, const zn::ui::AWidget & panel) override;
		virtual void drawPushButton(IRenderer &r, const AWidget &btn) override;

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_BASICSKIN_HPP
