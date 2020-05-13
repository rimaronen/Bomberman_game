#pragma once
#include "BoardItem.h"
class Wall :
	public BoardItem
{
public:
	Wall(const sf::Vector2f& position);
};

