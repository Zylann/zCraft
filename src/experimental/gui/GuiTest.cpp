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



