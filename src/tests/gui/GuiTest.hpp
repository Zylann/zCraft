#ifndef EXPERIMENTAL_TESTGUI_H_INCLUDED
#define EXPERIMENTAL_TESTGUI_H_INCLUDED

#include "engine/game/BasicGame.hpp"
#include "engine/opengl/ShaderProgram.hpp"
#include "engine/gui/Root.hpp"
#include "engine/gui/inputs/SFMLInputAdapter.hpp"
#include "engine/gui/widgets/Panel.hpp"
#include "engine/gui/widgets/Text.hpp"
#include "engine/gui/widgets/ProgressBar.hpp"

namespace experimental
{
	class GuiTest : public zn::ABasicGame
	{
	private :

		zn::ui::Root * m_gui;
		zn::ui::Panel * r_panel;
		zn::ui::Text * r_text;
		zn::ui::ProgressBar * r_progressBar;
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
