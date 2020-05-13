#pragma once
#include "BonusItem.h"

const unsigned BOMB_BONUS_AMOUNT = 1;
// the animation will switch frames by this time (in seconds)
const float BOMB_BONUS_SWITCH_TIME = 0.3f;
// the texture will have this many frames in every row
const unsigned BOMB_BONUS_IMAGE_COUNT_X = 9;
// the texture will have this many rows of frames
const unsigned BOMB_BONUS_IMAGE_COUNT_Y = 1;

class Robot;

class BombBonus :
	public BonusItem
{
public:
	//constractor get position
	BombBonus(const sf::Vector2f& position);
	////play the animation
	virtual void play(float deltaTime, sf::RenderWindow &window);
	//effect the robot by bomb
	virtual void affectRobot(Robot& robot) override;
};

