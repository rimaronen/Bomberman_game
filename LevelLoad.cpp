#include "LevelLoad.h"


/*level load constractor- init level button vector and window. prepare backround texture*/
LevelLoad::LevelLoad(sf::RenderWindow & window, std::vector<std::unique_ptr<LoadLevelButton>>& buttons)
	:MenuWindowManager(window), m_buttons(buttons)
{
	prepareLoadLevelBG();
}

/*this function prepares the texture for the background level choices*/
void LevelLoad::prepareLoadLevelBG()
{
	loadTextureFromFile(LEVEL_LOAD_BACKGROUND);
	MenuWindowManager::prepareTextureBG();
}

/*this function handles key press from the user to pick the wanted level*/
level_t LevelLoad::getKeyPressedEvent(const sf::Event & event) const
{
	if (sf::Keyboard::Key::Num1 == event.key.code || sf::Keyboard::Key::Numpad1 == event.key.code)
		return level_1_lv;
	else if (sf::Keyboard::Key::Num2 == event.key.code || sf::Keyboard::Key::Numpad2 == event.key.code)
		return level_2_lv;
	else if (sf::Keyboard::Key::Num3 == event.text.unicode || sf::Keyboard::Key::Numpad3 == event.key.code)
		return level_3_lv;
	else if (sf::Keyboard::Key::Num4 == event.text.unicode || sf::Keyboard::Key::Numpad4 == event.key.code)
		return level_4_lv;
	else if (sf::Keyboard::Key::Num5 == event.text.unicode ||sf::Keyboard::Key::Numpad5 == event.key.code)
		return level_5_lv;
	else if (sf::Keyboard::Key::Num6 == event.text.unicode || sf::Keyboard::Key::Numpad6 == event.key.code)
		return level_6_lv;
	else
		return no_level_lv;
}

/*this function draws background of menu levels and the buttons of the level choices*/
void LevelLoad::draw()
{
	MenuWindowManager::draw();
	for (size_t i = 0; i < m_buttons.size(); ++i)
		m_buttons[i]->draw();
}

/*this function returns the level the user chose by the the position of mouse click*/
level_t LevelLoad::getMouseButtonPressed(const sf::Vector2f & position) const
{
	for (size_t i = 0; i < m_buttons.size(); ++i)
		if (m_buttons[i]->isPressed(position))
			return m_buttons[i]->getLevel();

	return no_level_lv; // if non of the buttons is pressed.
}
