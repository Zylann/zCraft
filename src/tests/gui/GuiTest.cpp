#include "GuiTest.hpp"

#include "engine/opengl/opengl.hpp"
#include "engine/system/Time.hpp"

#include "engine/gui/renderers/OGLGuiRenderer.hpp"
#include "engine/gui/skins/BasicSkin.hpp"
#include "engine/gui/widgets/DragZone.hpp"
#include "engine/gui/widgets/PushButton.hpp"
#include "engine/gui/widgets/CheckBox.hpp"
#include "engine/gui/widgets/TextField.hpp"
#include "engine/gui/widgets/Slider.hpp"

using namespace zn;

namespace experimental
{
	GuiTest::GuiTest() : ABasicGame(800, 600, "zENGui - test")
	{}

	GuiTest::~GuiTest()
	{}

	bool GuiTest::init()
	{
		if(!m_shader.load("assets/shaders/basic.vert", "assets/shaders/tvstatic.frag"))
			return false;

		//
		// GUI setup
		//

		m_gui = new ui::Root(m_window.getSize().x, m_window.getSize().y);
		m_gui->setRenderer(new ui::OGLGuiRenderer());
		ui::BasicSkin * skin = new ui::BasicSkin("Basic", "assets/fonts/tahoma16.fnt");
		skin->lightColor = Color(0x00bbffff);
		if(!m_gui->installSkin(skin))
		{
			delete skin;
			return false;
		}
		m_gui->setSkin("Basic");

		//
		// Panel 1
		//

		r_panel = new ui::Panel();
		r_panel->setID("myFirstPanel");
		r_panel->setLocalBounds(IntRect(100, 100, 300, 250));
		r_panel->setAlign(ui::CENTER_H | ui::FILL_H | ui::TOP);

//		ui::PushButton * button = new ui::PushButton();
		ui::PushButton * button = r_panel->add<ui::PushButton>();
		button->setID("myButton");
		button->setText(L"My big button");
		button->setLocalBounds(IntRect(10, 120, 100, 140));
		button->onClickSignal.connect([](){
			std::cout << "Hello world !" << std::endl;
		});
//		r_panel->add(button);

		ui::CheckBox * checkBox = new ui::CheckBox();
		checkBox->setText(L"My lovely checkbox");
		checkBox->setLocalBounds(IntRect(120, 120, 250, 140));
		r_panel->add(checkBox);

		ui::TextField * textField = new ui::TextField();
		textField->setLocalBounds(IntRect(270, 120, 400, 140));
		r_panel->add(textField);

		ui::PushButton * clearTextField = new ui::PushButton();
		clearTextField->setText(L"Clear");
		clearTextField->setLocalBounds(IntRect(410, 120, 450, 140));
		clearTextField->onClickSignal.connect([=](){
			textField->setText(L"");
		});
		r_panel->add(clearTextField);

		r_progressBar = r_panel->add<ui::ProgressBar>();
		r_progressBar->setLocalBounds(IntRect(460, 125, 600, 135));
		r_progressBar->setRatio(0.33f);

		ui::Slider * slider1 = r_panel->add<ui::Slider>();
		slider1->setLocalBounds(IntRect(460, 80, 600, 100));

		ui::Slider * slider2 = r_panel->add<ui::Slider>();
		slider2->setOrientation(ui::Slider::VERTICAL);
		slider2->setLocalBounds(IntRect(610, 50, 630, 140));

		r_text = new ui::Text();
		r_text->setID("myText");
		r_text->setWrap(true);
		r_text->setLocalBounds(IntRect(10, 10, 190, 110));
		r_text->setText(L"This is not a sample text. This is a brand new "
						"testing system involving character strings linked "
						"together in a byte-based dynamic array, also called "
						"std::string.");
		r_panel->add(r_text);

		m_gui->add(r_panel);

		//
		// Panel 2
		//

		ui::Panel * panel2 = new ui::Panel();
		panel2->setID("myPanel2");
		panel2->setLocalBounds(IntRect(300, 200).offset(200, 200));

		ui::DragZone * dragZone1 = new ui::DragZone();
		dragZone1->setLocalBounds(IntRect(300, 30));
		panel2->add(dragZone1);

		ui::DragZone * dragZone2 = new ui::DragZone();
		dragZone2->setLocalBounds(IntRect(300, 30).offset(0, 170));
		panel2->add(dragZone2);

		ui::TextField * tf1 = panel2->add<ui::TextField>();
		tf1->setLocalBounds(IntRect(200, 24).offset(30, 50));

		ui::TextField * tf2 = panel2->add<ui::TextField>();
		tf2->setLocalBounds(IntRect(200, 24).offset(30, 80));
		tf2->setSecret(true);

		m_gui->add(panel2);

		m_gui->layout();

		return true;
	}

	void GuiTest::dispose()
	{
		delete m_gui;
	}

	void GuiTest::resized(const Vector2i & newSize)
	{
		m_gui->setBounds(IntRect(0, 0, newSize.x, newSize.y));
		m_gui->layout();
	}

	void GuiTest::processEvent(const sf::Event & event)
	{
		m_guiInput.forward(event, *m_gui);
	}

	void GuiTest::update(const zn::Time & delta)
	{
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//		{
//			//r_panel->setBounds(IntRect(r_panel->getBounds()).offset(-1, 0));
//			r_text->setLocalBounds(r_text->getLocalBounds().contract(-1, 0));
//		}
//		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//		{
//			//r_panel->setBounds(IntRect(r_panel->getBounds()).offset(1, 0));
//			r_text->setLocalBounds(r_text->getLocalBounds().expand(1, 0));
//		}

		m_gui->animate(delta.hz());
	}

	void GuiTest::renderScene(const Time & /*delta*/)
	{
		glClearColor(0.1f, 0.1f, 0.2f, 1.f);
	}

	void GuiTest::renderGUI(const zn::Time & /*delta*/)
	{
//		m_shader.bind();
//		m_shader.setUniform("time", m_time.getElapsedTime().asSeconds());
		m_gui->render();
//		m_shader.unbind();
	}

} // namespace experimental



