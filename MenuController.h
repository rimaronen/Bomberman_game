#pragma once
#include "Menu.h"
#include "types.h"
#include "consts.h"
#include "MenuButton.h"
#include <vector>
#include <memory>


class MenuController
{
public:
	MenuController(sf::RenderWindow &menuWindow);
	

	choice_t handleEvents();
	void handleEvent(sf::Event &event);
	void close();
	choice_t run();

	void draw();

	void resetMembers();

private:
	//void prepareTextureBG();

	sf::RenderWindow &m_menuWindow; 
	Menu m_menu;
	choice_t m_button;
	choice_t m_pressedButton = no_btn; // will keep the pressed button the user chose
	bool m_buttonWasPressed = false;
	sf::Texture m_menuTexture;

	sf::Texture m_bgMenuTexure;
	sf::RectangleShape m_rectTexture;
	std::unique_ptr<Sound> m_sound = std::make_unique<Sound>(GameResources::instance().getMenuMusicBuffer());
	sf::Sprite m_manuSprite;
	std::vector<std::unique_ptr<MenuButton>> m_menuButtons; // allocate vector for buttons
};

