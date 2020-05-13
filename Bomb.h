#pragma once
#include "TimedItem.h"

// the bomb will be delayed by this time (in seconds) before exploding
const float BOMB_TIME_OUT = 4.0f;
// the bomb animation will switch frames by this time (in seconds)
const float BOMB_SWITCH_TIME = 0.15f;
// the bomb texture will have this many frames in every row
const unsigned BOMB_IMAGE_COUNT_X = 30;
// the bomb texture will have this many rows of frames
const unsigned BOMB_IMAGE_COUNT_Y = 1;

class Bomb :
	public TimedItem
{
public:
	// c-tor with position, bombs cannot be created without a position (they are always
	// positioned at the robot's last position)
	Bomb(const sf::Vector2f& position);
	// tells if this bomb exists more than it's BOMB_TIME_OUT constant
	virtual bool didTimeOut() const override;
};

