#include "Guard.h"

Guard::Guard(sf::Texture & texture, const Board & board)
	:Player(texture, board)
{
	init();
}

Guard::Guard(sf::Texture & texture, const sf::Vector2f & position, const Board & board)
	:Player(texture, position, board)
{
	init();
	setInitialPosition(position);
}

void Guard::init()
{
	setSpeed({ GUARD_SPEED, GUARD_SPEED });
}
