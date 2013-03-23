#include "GuiTest.hpp"
#include "GuiRenderer.hpp"
#include "engine/opengl/opengl.hpp"
#include "engine/system/Time.hpp"

using namespace zn;

namespace experimental
{
	GuiTest::GuiTest() : ABasicGame(800, 600, "zENGui - test")
	{}

	GuiTest::~GuiTest()
	{}

	bool GuiTest::init()
	{
		m_gui = new ui::Root(m_window.getSize().x, m_window.getSize().y);
		m_gui->setRenderer(new GuiRenderer());
		m_guiTheme = new BasicTheme();
		m_gui->setTheme(*m_guiTheme);

		r_panel = new ui::Panel();
		r_panel->setBounds(IntRect(100, 100, 300, 250));
		m_gui->add(r_panel);

		ui::Panel * panel2 = new ui::Panel();
		panel2->setBounds(IntRect(400, 200, 600, 300));
		m_gui->add(panel2);

		return true;
	}

	void GuiTest::dispose()
	{
		delete m_gui;
		delete m_guiTheme;
	}

	void GuiTest::resized(const Vector2i & newSize)
	{
	}

	void GuiTest::processEvent(const sf::Event & event)
	{
		m_guiInput.forward(event, *m_gui);
	}

	void GuiTest::update(const zn::Time & delta)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			r_panel->setBounds(IntRect(r_panel->getBounds()).offset(-1, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			r_panel->setBounds(IntRect(r_panel->getBounds()).offset(1, 0));
		}

		m_gui->animate(delta.hz());
	}

	void GuiTest::renderScene(const Time & delta)
	{

	}

	void GuiTest::renderGUI(const zn::Time & delta)
	{
		m_gui->render();
	}

} // namespace experimental



