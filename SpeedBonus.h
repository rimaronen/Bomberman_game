#pragma once
#include "BonusItem.h"
// the animation will switch frames by this time (in seconds)
const float SPEED_BONUS_SWITCH_TIME = 0.3f;
// the texture will have this many frames in every row
const unsigned SPEED_BONUS_IMAGE_COUNT_X = 20;
// the texture will have this many rows of frames
const unsigned SPEED_BONUS_IMAGE_COUNT_Y = 1;

class SpeedBonus:
	public BonusItem
{
	public:
		//constractor get position
		SpeedBonus(const sf::Vector2f& position);
		//play the animation
		virtual void play(float deltaTime, sf::RenderWindow &window);
		//effect the robot by speed
		virtual void affectRobot(Robot& robot) override;
};

