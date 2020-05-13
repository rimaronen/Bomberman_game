#include "Menu.h"
#include "GameResources.h"
Menu::Menu(sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>> &buttons)
	:MenuWindowManager(window), m_buttons(buttons)
	
{
	
	prepareTextureBG();
}

/*prepare menu background texture*/
void Menu::prepareTextureBG()
{
	loadTextureFromFile(MENU_BACKGROUND);
	MenuWindowManager::prepareTextureBG();
}

void Menu::draw()
{
	MenuWindowManager::draw();
	for (size_t i = 0; i < m_buttons.size(); ++i)
		m_buttons[i]->draw(); // draw all menu buttons on window
}

/*this function checks if the mousde button was pressed is one of the button in the menu. if yes, return the button type to menu controller*/
choice_t Menu::getMouseButtonPressed(const sf::Vector2f & position) const
{
	for (size_t i = 0; i < m_buttons.size(); ++i)
		if (m_buttons[i]->isPressed(position)) 
			return m_buttons[i]->getChoice();
		
	return no_btn;
}
/*this function return the pressed key button from the menu, non const- changing m_menuWindowClosed if exit was pressed*/
choice_t Menu::getKeyPressedEvent(const sf::Event & event) const
{
	if (sf::Keyboard::Key::S == event.text.unicode) // S - pressed start button
		return start_btn;
	
	else if (sf::Keyboard::Key::L == event.text.unicode) // L - pressed load button
		return load_btn;
	else if (sf::Keyboard::Key::E == event.text.unicode)  // E - pressed exit button
		return exit_btn;
	else
		return no_btn;
}

