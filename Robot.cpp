#include "Robot.h"
#include "Board.h"
#include "GameResources.h"
#include "LoopSound.h"

// c-tor
Robot::Robot(const Board & board)
	:Player(GameResources::instance().getRobotTexture(), board),
	m_moveSound(new LoopSound(GameResources::instance().getRunBuffer())),
	m_robotDieSound(new Sound(GameResources::instance().getRobotDieBuffer()))
{
	// set initial speed to walking speed
	walk();
}

// d-tor: releases sounds
Robot::~Robot()
{
	delete m_moveSound;
	delete m_robotDieSound;
}

// change speed to running speed
void Robot::run()
{
	// restart the clock to check the time a run bonus is active
	m_runBonusClock->restart();
	setSpeed({ RUN_SPEED, RUN_SPEED });
}

// change speed to walking speed
void Robot::walk()
{
	setSpeed({ WALK_SPEED, WALK_SPEED });
}

// tells how many extra lives are left to the robot
unsigned Robot::getLives() const
{
	return m_lives;
}

// set extra lives
void Robot::setLives(unsigned lives)
{
	m_lives = lives;
}

int Robot::getBombQuantity() const
{
	return m_bombQuantity;
}

int Robot::getScore() const
{
	return m_score;
}

void Robot::resetScore()
{
	m_score = 0;
}

void Robot::setBombQuantity(unsigned bombQuantity)
{
	m_bombQuantity = bombQuantity;
}

void Robot::increaseBombQuantity(unsigned amount)
{
	if (m_bombQuantity != UNLIMITED_BOMBS)
		m_bombQuantity += amount;
}

void Robot::increaseLifeQuantity(unsigned amount)
{
	if (m_lives < MAX_LIVES)
		m_lives += amount;
}

void Robot::increaseScoreBy(unsigned amount)
{
	m_score += amount;
}

bool Robot::useBomb()
{
	// increase used bombs in case we use a bomb
	++m_usedBombs;
	if (m_bombQuantity == UNLIMITED_BOMBS)
		return true;
	if (m_bombQuantity > 0) {
		--m_bombQuantity;
		return true;
	}
	// decrease used bombs if we didn't use a bomb
	--m_usedBombs;
	return false;
}

bool Robot::die()
{
	if (m_lives) {
		--m_lives;
		m_robotDieSound->play();
	}
	else {
		m_isAlive = false;
	}
	resetPosition();
	return m_isAlive;
}

// moves the robot on the board according to keys pressed.
void Robot::move(float delta)
{
	if (m_runBonusClock->getElapsedTime().asSeconds() > RUN_BONUS_TIME)
		walk();
	// positive speed.x means moving right, negative means left
	// positive speed.y means moving down, negative means up
	// speed is amount of pixels to move per second.
	// multiply it by delta to get the amount to move since the
	// last clock restart (which is what delta is supposed to be)
	PlayerAnimation *pa = dynamic_cast<PlayerAnimation *>(getAnimation());
	
	if (pa != nullptr) {
		sf::Vector2f offset;
		m_moveSound->play();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			offset = { 0.0f, -getSpeed().y * delta };
			pa->up();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			offset = { getSpeed().x * delta, 0.0f };
			pa->right();
		}	
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			offset = { 0.0f, getSpeed().y * delta };
			pa->down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			offset = { -getSpeed().x * delta, 0.0f };
			pa->left();
		}
		else {
			offset = { 0.0f, 0.0f };
			pa->idle();
			m_moveSound->stop();
		}
		attemptMove(pa, offset);
	}
}

void Robot::playSound()
{
	m_moveSound->play();
}

void Robot::pauseSound()
{
	m_moveSound->pause();
}

void Robot::stopSound()
{
	m_moveSound->stop();
}

// reset the robot on game over or on time out
void Robot::reset()
{
	m_bombQuantity = m_initialBombQuantity;
	m_isAlive = true;
	m_lives = MAX_LIVES;
	setSpeed({ WALK_SPEED, WALK_SPEED });
	m_moveSound->stop();
	m_usedBombs = 0;
}

unsigned Robot::getUsedBombs() const
{
	return m_usedBombs;
}



