#pragma once
#include <SFML/Graphics.hpp>
#include "LoadLevelButton.h"
#include "MenuWindowManager.h"
#include "consts.h"

const std::string LEVEL_LOAD_BACKGROUND = "img/level_buttons/levelBG3.jpg";

class LevelLoad:
	public MenuWindowManager
{
public:
	LevelLoad(sf::RenderWindow &window, std::vector<std::unique_ptr<LoadLevelButton>> &buttons);
	void draw() override;
	// prepare load window background
	void prepareLoadLevelBG();
	// get type of button was pressed from mouse press in load window
	level_t getMouseButtonPressed(const sf::Vector2f &position) const;
	// get type of button was pressed from keyboard in load window
	level_t getKeyPressedEvent(const sf::Event &event) const;

private:
	// vector holds the buttons of load level window
	std::vector<std::unique_ptr<LoadLevelButton>> &m_buttons;
};

