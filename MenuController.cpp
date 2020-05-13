#include "MenuController.h"
#include "consts.h"
#include "GameResources.h"

// TODO LIST: finish handling button. load levels by adding level controller, handle start button to send the controller start
// handle save button to save the currrent lavel playing
// keep level name files in menu controller


/*MenuController constractor*/
MenuController::MenuController(sf::RenderWindow &menuWindow)
	:m_menuWindow(menuWindow), m_menu(menuWindow, m_menuButtons)
{
	//m_menu.prepareTextureBG(m_menuWindow);
	for (int button = start_btn; button < no_btn; ++button)
		m_menuButtons.push_back(std::make_unique<MenuButton>((choice_t)button, m_menuWindow));

}
/*handle events function, will return the wanted user's choice*/
choice_t MenuController::handleEvents()
{
	sf::Event event;

	while (m_menuWindow.pollEvent(event)); {

		if (m_pressedButton != no_btn) // if a button was pressed, declare menu window closed, to move to controller 
										// window for handling the buttons
			m_buttonWasPressed = true;

		handleEvent(event);
	}
	return m_pressedButton;
}

void MenuController::handleEvent(sf::Event &event)
{
	sf::Vector2f coords;
	switch (event.type)
	{
	case sf::Event::Closed:
		close();
	case sf::Event::KeyReleased: // if asked to close window
		if (event.key.code == sf::Keyboard::Escape)
			close();
	case sf::Event::TextEntered:
		m_pressedButton = m_menu.getKeyPressedEvent(event);
		break;
	case sf::Event::MouseButtonReleased:
		coords = m_menuWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
		m_pressedButton = m_menu.getMouseButtonPressed(coords); // get button pressed from mouse
	}
}

void MenuController::close()
{
	m_menuWindow.close();
	m_buttonWasPressed = true;
}

/*this function will run the menu screen. the user choice will be returned to the controller, and will be handled there.
If the user will choose start- start_btn choice will be return and the controller will start game controller with the first level.
If ths user will choose load- load_btn will be returned and the controller will run the load contrller to choose level.
If the user will choose save- save_btn will be return and the controller will save the current level playing.
If the user will choose exit- the game will end, and the windoe will close.*/
choice_t MenuController::run()
{
	m_menu.windowIsOpen();
	m_buttonWasPressed = false;
	m_pressedButton = no_btn;
	m_sound->play();
	m_sound->loop();

	while (m_menuWindow.isOpen() && !m_buttonWasPressed) {// as long menu window is open
		draw();
		m_pressedButton = handleEvents();
	}

	m_menuWindow.clear();
	resetMembers();
	m_sound->stop();
	return m_pressedButton;
}

void MenuController::draw()
{
	m_menuWindow.clear();
	m_menu.draw();
	m_menuWindow.display();
}

void MenuController::resetMembers()
{
	m_button = no_btn;
	m_buttonWasPressed = false;
}


