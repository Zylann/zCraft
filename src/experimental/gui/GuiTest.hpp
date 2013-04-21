#ifndef EXPERIMENTAL_TESTGUI_H_INCLUDED
#define EXPERIMENTAL_TESTGUI_H_INCLUDED

#include "engine/game/BasicGame.hpp"
#include "zengui/Root.hpp"
#include "zengui/plugin/SFMLInputAdapter.hpp"
#include "zengui/Panel.hpp"
#include "zengui/Text.hpp"
#include "engine/opengl/ShaderProgram.hpp"

namespace experimental
{
	class GuiTest : public zn::ABasicGame
	{
	private :

		zn::ui::Root * m_gui;
		zn::ui::Panel * r_panel;
		zn::ui::Text * r_text;
		zn::ui::SFMLInputAdapter m_guiInput;
		zn::gl::ShaderProgram m_shader;

	public :

		GuiTest();

		virtual ~GuiTest();

	protected :

		bool init() override;

		void resized(const zn::Vector2i & newSize) override;

		void processEvent(const sf::Event & event) override;

		void update(const zn::Time & delta) override;

		void renderScene(const zn::Time & delta) override;

		void renderGUI(const zn::Time & delta) override;

		void dispose() override;

	};

} // namespace experimental

#endif // EXPERIMENTAL_TESTGUI_H_INCLUDED
