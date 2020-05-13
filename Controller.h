#pragma once

#include "MenuController.h"
#include "GameController.h"
#include "LoadController.h"


class Controller
{
public:
	Controller();
	void run();
private:
	sf::RenderWindow m_window;
	// controller for each screen: menu screen, load screen and game screen
	MenuController m_menuController;
	LoadController m_loadController;
	GameController m_gameController;
};

