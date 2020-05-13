#pragma once
#include <SFML/Graphics.hpp>
#include "Guard.h"

// this is the time after which a simple guard changes his direction
const float SWITCH_DIRECTION_TIME = 2.0f;

class GameController;

class SimpleGuard :
	public Guard
{
public:
	SimpleGuard(const sf::Vector2f& position, const Board& board);
	virtual void move(float delta) override;
private:
	// compute the offset by which to move from current position
	void computeOffset(float delta);

	// acumulate the time delta received by move to determine when to switch direction
	float m_timeAccumulator;
	move_t m_direction;
	sf::Vector2f m_offset;
};

