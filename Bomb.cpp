#include "Bomb.h"
#include "TimedItemAnimation.h"
#include "GameResources.h"
#include "Sound.h"

// c-tor
Bomb::Bomb(const sf::Vector2f & position)
	:TimedItem(new TimedItemAnimation(GameResources::instance().getBombTexture(),
		sf::Vector2u(BOMB_IMAGE_COUNT_X, BOMB_IMAGE_COUNT_Y), position, BOMB_SWITCH_TIME),
		new Sound(GameResources::instance().getBombBuffer()))
{
}

// tells if this bomb timed out (outlived it's duration)
bool Bomb::didTimeOut() const
{
	return getElapsedTime().asSeconds() - getPauseTime() >= BOMB_TIME_OUT;
}
