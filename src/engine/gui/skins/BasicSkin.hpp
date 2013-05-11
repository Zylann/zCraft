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
		zn::ui::Font m_defaultMonoFont;
		std::string m_name;

	public :

		/**
		 * @brief Constructs the skin.
		 * @name name of the skin to be used for identification (usually "Basic").
		 * @param globalFontFilepath : path to the global font.
		 * It will be named "global" for the renderer.
		 * @param globalMonoFontFilepath : path to the global mono font.
		 * It will be named "global_mono" for the renderer.
		 * If not specified, it will be set same as the global font.
		 */
		BasicSkin(std::string name,
			std::string globalFontFilepath,
			std::string globalMonoFontFilepath="");

		virtual ~BasicSkin() {}

		virtual bool load(zn::ui::IRenderer & r) override;
		virtual bool unload(zn::ui::IRenderer & r) override;

		virtual zn::ui::Font & getDefaultFont() override;
		virtual zn::ui::Font & getDefaultMonoFont() override;
		virtual std::string getName() override { return m_name; }

		virtual void drawDummyWidget(zn::ui::IRenderer & r, const zn::ui::AWidget & w) override;
		virtual void drawPanel(zn::ui::IRenderer & r, const zn::ui::AWidget & panel) override;
		virtual void drawPushButton(IRenderer &r, const AWidget &btn) override;
		virtual void drawCheckBox(IRenderer & r, const AWidget & cb, bool checked) override;
		virtual void drawTextField(IRenderer &r, const AWidget &tf) override;
		virtual void drawProgressBar(IRenderer &r, const AWidget &pb, float ratio) override;
		virtual void drawSlider(IRenderer &r, const Slider &s) override;

		virtual void drawDragZone(IRenderer &r, const AWidget &dz) override;

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_BASICSKIN_HPP
