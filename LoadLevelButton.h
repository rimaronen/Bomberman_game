#pragma once
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include "types.h"
#include "MenuButtonBase.h"

const std::string LEVEL_1_BUTTON = "img/level_buttons/level_1_bt.png";
const std::string LEVEL_2_BUTTON = "img/level_buttons/level_2_bt.png";
const std::string LEVEL_3_BUTTON = "img/level_buttons/level_3_bt.png";
const std::string LEVEL_4_BUTTON = "img/level_buttons/level_4_bt.png";
const std::string LEVEL_5_BUTTON = "img/level_buttons/level_5_bt.png";
const std::string LEVEL_6_BUTTON = "img/level_buttons/level_6_bt.png";

class LoadLevelButton
	: public MenuButtonBase
{
public:
	LoadLevelButton(const level_t &levelButton, sf::RenderWindow &window);
	// prepare the texture and position for the load buttons
	void prepareTextureAndPos();
	// return the current level was pressed
	level_t getLevel() const;

private:
	level_t m_levelButton = no_level_lv;
};

