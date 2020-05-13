#pragma once
#include "Player.h"
#include "types.h"

const float GUARD_SPEED = 100.0f;

class Guard :
	public Player
{
public:
	Guard(sf::Texture & texture, const Board & board);
	Guard(sf::Texture & texture, const sf::Vector2f & position, const Board & board);
private:
	void init();
};

