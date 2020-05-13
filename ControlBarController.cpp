#include <iomanip>
#include <sstream>
#include "ControlBarController.h"
#include "consts.h"
#include "Robot.h"
#include "GameResources.h"

// c-tor
ControlBarController::ControlBarController(std::unique_ptr<Robot> & robot)
	:m_robot(robot)
{
	// create sprites for robot lives
	for (int i = 0; i < MAX_LIVES; ++i)
		m_livesSprites.push_back(std::make_unique<sf::Sprite>());

	// init background
	m_controllBarBG->setFillColor(sf::Color(255, 255, 255, 128));
	m_controllBarBG->setSize({ GAME_CONTROL_BAR_WIDTH, GAME_CONTROL_BAR_HEIGHT });
	m_controllBarBG->setOutlineColor(sf::Color::White);
	m_controllBarBG->setOutlineThickness(CB_OUTLINE_THICKNESS);

	// init bomb quantity text
	m_bombQuantityText->setFont(GameResources::instance().getCbFont());
	m_bombQuantityText->setCharacterSize(CHARACTER_SIZE);
	m_bombQuantityText->setFillColor(sf::Color::Black);
	m_bombQuantityText->setOrigin({ CB_ICON_WIDTH / 2.0f, CB_ICON_WIDTH / 2.0f });

	// init time left text
	m_timeLeftText->setFont(GameResources::instance().getCbFont());
	m_timeLeftText->setCharacterSize(CHARACTER_SIZE);
	m_timeLeftText->setFillColor(sf::Color::Black);
	m_timeLeftText->setOrigin({ 0.0f, CB_ICON_WIDTH / 2.0f });

	// init score text
	m_scoreText->setFont(GameResources::instance().getCbFont());
	m_scoreText->setCharacterSize(CHARACTER_SIZE);
	m_scoreText->setFillColor(sf::Color::Black);
	m_scoreText->setOrigin({ 0.0f, CB_ICON_WIDTH / 2.0f });

	// init used bombs text
	m_usedBombsText->setFont(GameResources::instance().getCbFont());
	m_usedBombsText->setCharacterSize(CHARACTER_SIZE);
	m_usedBombsText->setFillColor(sf::Color::Black);
	m_usedBombsText->setOrigin({ 0.0f, CB_ICON_WIDTH / 2.0f });

	// init level text
	m_levelText->setFont(GameResources::instance().getCbFont());
	m_levelText->setCharacterSize(CHARACTER_SIZE);
	m_levelText->setFillColor(sf::Color::Black);
	m_levelText->setOrigin({ 0.0f, CB_ICON_WIDTH / 2.0f });

	m_bombCountIcon->setTexture(GameResources::instance().getBombIconTexture());
	m_usedBombIcon->setTexture(GameResources::instance().getExplosionIconTexture());
}

// draw the control bar
void ControlBarController::draw(sf::RenderWindow & window, int timeLeftMilliseconds, unsigned currentLevelIndex)
{
	window.draw(*m_controllBarBG);
	drawLives(window);
	window.draw(*m_bombCountIcon);
	updateBombQuantity();
	window.draw(*m_bombQuantityText);
	setTimeLeft(timeLeftMilliseconds);
	window.draw(*m_timeLeftText);
	setScore();
	window.draw(*m_scoreText);
	drawUsedBombs(window);
	setCurrentLevel(currentLevelIndex);
	window.draw(*m_levelText);
}

// draw the robot's lives
void ControlBarController::drawLives(sf::RenderWindow & window)
{
	for (unsigned i = 0; i < m_robot->getLives(); ++i) {
		m_livesSprites[i]->setTexture(GameResources::instance().getLifeFullTexture());
		window.draw(*m_livesSprites[i]);
	}
	for (unsigned i = m_robot->getLives(); i < MAX_LIVES; ++i) {
		m_livesSprites[i]->setTexture(GameResources::instance().getLifeEmptyTexture());
		window.draw(*m_livesSprites[i]);
	}
}

// set the position of this control bar
void ControlBarController::setPosition(sf::Vector2f& position)
{
	m_controllBarBG->setPosition(position);
	for (int i = 0; i < MAX_LIVES; ++i)
		m_livesSprites[i]->setPosition(position + sf::Vector2f(CB_ICON_WIDTH * i, 0));
	m_bombCountIcon->setPosition(position + sf::Vector2f(0, CB_ICON_WIDTH * 1));
	m_bombQuantityText->setPosition(position + sf::Vector2f(CB_ICON_WIDTH * 1.5, CB_ICON_WIDTH * 3.0f / 2.0f));
	m_timeLeftText->setPosition(position + sf::Vector2f(0.0f, CB_ICON_WIDTH * 5.0f / 2.0f));
	m_scoreText->setPosition(position + sf::Vector2f(0.0f, CB_ICON_WIDTH * 7.0f / 2.0f));
	m_usedBombIcon->setPosition(position + sf::Vector2f(0.0f, CB_ICON_WIDTH * 4));
	m_usedBombsText->setPosition(position + sf::Vector2f(CB_ICON_WIDTH * 1.5, CB_ICON_WIDTH * 4 + CB_ICON_WIDTH / 2.0f));
	m_levelText->setPosition(position + sf::Vector2f(0.0f, CB_ICON_WIDTH * 5 + CB_ICON_WIDTH / 2.0f));
}

void ControlBarController::updateBombQuantity() {
	if (m_robot->getBombQuantity() != UNLIMITED_BOMBS)
		m_bombQuantityText->setString(std::to_string(m_robot->getBombQuantity()));
	else
		m_bombQuantityText->setString(STR_INFINIT);
}

void ControlBarController::setTimeLeft(int timeLeftMilliseconds)
{
	std::string timeString = "";
	if (timeLeftMilliseconds > 0) {
		sf::Time timeLeft = sf::milliseconds(timeLeftMilliseconds);
		int minutes = (int)timeLeft.asSeconds() / 60;
		timeLeft -= sf::seconds((float)(minutes * 60));
		int seconds = (int)timeLeft.asSeconds();

		// if seconds is less than 10 pad it with a 0
		if (seconds < 10)
			timeString = std::to_string(minutes) + ":" + "0" +
			std::to_string(seconds);
		else
			timeString = std::to_string(minutes) + ":" +
			std::to_string(seconds);
	}
	else if (timeLeftMilliseconds == UNLIMITED_TIME) {
		timeString = STR_INFINIT;
	}
	m_timeLeftText->setString(timeString);
}

void ControlBarController::setScore()
{
	std::string score = "score " + std::to_string(m_robot->getScore());
	m_scoreText->setString(score);
}

void ControlBarController::drawUsedBombs(sf::RenderWindow& window)
{
	m_usedBombsText->setString(std::to_string(m_robot->getUsedBombs()));
	window.draw(*m_usedBombIcon);
	window.draw(*m_usedBombsText);
}

void ControlBarController::setCurrentLevel(unsigned currentLevelIndex)
{
	std::string level = "level " + std::to_string(currentLevelIndex);
	m_levelText->setString(level);
}