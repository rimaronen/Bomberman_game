#include "MenuButton.h"
#include "consts.h"


// TODO: work on buttons and controller.!!!

/*menu button constractor*/
MenuButton::MenuButton(const choice_t &button, sf::RenderWindow & window)
	:MenuButtonBase(window), m_button(button)
{
	prepareTextureAndPos(); // prepare button texture

	init();
}

/*this funtion prepares the textures to theire positions files by the type of the button was sent*/
void MenuButton::prepareTextureAndPos()
{
	std::string buttonFileName; // file name for the current button
	// set buttons position at the center of the window
	float xPos = 200.0f;
	float yPos = 125.0f;

	switch (m_button) {
	case start_btn:
		buttonFileName = START_BUTTON;
		setPos({ xPos, (yPos * START_POS) });
		break;
	case load_btn:
		buttonFileName = LOAD_LEVEL;
		setPos({ xPos, (yPos * LOAD_POS) });
		break;
	case exit_btn:
		buttonFileName = EXIT_BUTTON;
		setPos({ xPos, (yPos * EXIT_POS) });
		break;
	default:
		buttonFileName = "";
		setPos({ 0, 0 });
	}

	loadTextureFromFile(buttonFileName);
}

/*return the button was chosen*/
choice_t MenuButton::getChoice() const
{
	return m_button;
}
