#pragma once
#include "Player.h"
#include "types.h"
#include "consts.h"

// walk and run speeds speed for robot - in terms of sfml coordinates per seconds
const float WALK_SPEED = 150.0f;
const float RUN_SPEED = 200.0f;
// the time a run bonus lasts
const float RUN_BONUS_TIME = 10.0f;
const int UNLIMITED_BOMBS = -1;

class LoopSound;
class Sound;

class Robot :
	public Player
{
public:
	Robot(const Board& board);
	~Robot();
	// sets movement speed
	void run();
	void walk();
	unsigned getLives() const;
	void setLives(unsigned lives);
	int getBombQuantity() const;
	int getScore() const;
	void resetScore();
	void setBombQuantity(unsigned bombQuantity);
	void increaseBombQuantity(unsigned amount);
	void increaseLifeQuantity(unsigned amount);
	void increaseScoreBy(unsigned amount);
	bool useBomb();
	bool die();
	virtual void move(float delta) override;
	void playSound();
	void pauseSound();
	void stopSound();
	void reset();
	unsigned getUsedBombs() const;
	
private:
	unsigned m_initialBombQuantity = UNLIMITED_BOMBS;
	unsigned m_bombQuantity = UNLIMITED_BOMBS;
	unsigned m_lives = MAX_LIVES; // defaults to 3 lives
	unsigned m_score = 0;
	unsigned m_usedBombs = 0;
	bool m_isAlive = true;
	LoopSound * m_moveSound;
	std::unique_ptr<sf::Clock> m_runBonusClock = std::make_unique<sf::Clock>();
	Sound * m_robotDieSound;

};

