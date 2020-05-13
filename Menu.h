#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "MenuButton.h"
#include "types.h"
#include "consts.h"
#include "MenuWindowManager.h"
#include "Sound.h"

class Menu :
	public MenuWindowManager
{
public:
	Menu(sf::RenderWindow &window, std::vector<std::unique_ptr<MenuButton>> &buttons);
	virtual void draw() override;
	// prepare menu window background 
	void prepareTextureBG();
	// get type of pressed button from mouse press in menu window
	choice_t getMouseButtonPressed(const sf::Vector2f &position) const;
	// get type of pressed button from keyboard press in menu winow
	choice_t getKeyPressedEvent(const sf::Event &event) const;

private:
	// vector for buttons on the menu window
	std::vector<std::unique_ptr<MenuButton>> &m_buttons;
};

