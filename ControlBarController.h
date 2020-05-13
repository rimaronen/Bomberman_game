#pragma once
#include <SFML/Graphics.hpp>
#include "consts.h"

// width of control bar icon (cb icons are sqare so this is also the height)
const float CB_ICON_WIDTH = 64;
// number of lives the robot receives each new level
const std::string STR_INFINIT = "Infinity";
const unsigned CB_OUTLINE_THICKNESS = 5;

class GameResources;
class Fonts;
class Robot;

class ControlBarController
{
public:
	// c-tor with referemce to unique_ptr to robot
	ControlBarController(std::unique_ptr<Robot>& robot);
	// draw the convtrol bar
	void draw(sf::RenderWindow& window, int timeLeftMilliseconds, unsigned currentLevelIndex);
	void drawLives(sf::RenderWindow & window);
	// set the position of the control bar - the position of the top left corner
	void setPosition(sf::Vector2f& position);
	void updateBombQuantity();
	void setTimeLeft(int timeLeftMilliseconds);
	void setScore();
	void drawUsedBombs(sf::RenderWindow & window);
	void setCurrentLevel(unsigned currentLevelIndex);
private:
	// background of the control bar
	std::unique_ptr<sf::RectangleShape> m_controllBarBG = std::make_unique<sf::RectangleShape>();
	std::unique_ptr<Robot>& m_robot;
	// sprites for displaying the lives of the robot (red heart for extra life, black heart for used extra life)
	std::vector<std::unique_ptr<sf::Sprite>> m_livesSprites;
	std::unique_ptr<sf::Sprite> m_bombCountIcon = std::make_unique<sf::Sprite>();
	// will display number of remaining bombs or inf if not limited
	std::unique_ptr<sf::Text> m_bombQuantityText = std::make_unique<sf::Text>();
	// will display time left
	std::unique_ptr<sf::Text> m_timeLeftText = std::make_unique<sf::Text>();
	// will display score
	std::unique_ptr<sf::Text> m_scoreText = std::make_unique<sf::Text>();
	// will display used bombs this level
	std::unique_ptr<sf::Sprite> m_usedBombIcon = std::make_unique<sf::Sprite>();
	std::unique_ptr<sf::Text> m_usedBombsText = std::make_unique<sf::Text>();
	// will display current level
	std::unique_ptr<sf::Text> m_levelText = std::make_unique<sf::Text>();
};

