#pragma once
#include "TimedItem.h"

// this is the time an explosion will last
const float EXPLOSION_TIME_OUT = 1.0f;
// explosion goes up, down, left and right
const unsigned NUM_OF_SIDES = 4;
// time between switching frames in the texture
const float switchTime = 0.002f;
// number of frames in a row in the texture
const unsigned EXPLOSION_IMAGE_COUNT_X = 8;
// number of rows of frames in the texture
const unsigned EXPLOSION_IMAGE_COUNT_Y = 6;

class TimedItemAnimation;

class Explosion :
	public TimedItem
{
public:
	Explosion(const sf::Vector2f& position);
	// tells if this explosion lasted more than it's timeout.
	virtual bool didTimeOut() const override;
	// tells if an item is near this explosion (used to determine if item will explode)
	bool intersects(BoardItem& item);
	// draw this explosion on the window
	virtual void draw(float deltaTime, sf::RenderWindow &window) override;
private:
	// the sides of the explosion - it goes up, down, left and right
	std::vector<std::unique_ptr<TimedItemAnimation>> m_sides;
};

