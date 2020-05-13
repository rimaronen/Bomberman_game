#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "types.h"
#include "MenuButtonBase.h"

// menu button const types
const std::string START_BUTTON = "img/menu_buttons/start-button2.png";
const std::string LOAD_LEVEL = "img/menu_buttons/load-button2.png";
const std::string SAVE_BUTTON = "img/menu_buttons/save-button2.png";
const std::string EXIT_BUTTON = "img/menu_buttons/exit-button.png";
const std::string MENU_BACKGROUND = "img/menu_buttons/bombBG.png";

const int START_POS = 1;
const int LOAD_POS = 2;
const int EXIT_POS = 3;

class MenuButton
	:public MenuButtonBase
{
public:
	MenuButton(const choice_t &button, sf::RenderWindow & window); // init all menut item on the board
	void prepareTextureAndPos(); // prepare the menu button texture for draw
	// return the button the user pressed on menu
	choice_t getChoice() const;

private:
	choice_t m_button = no_btn;
};

