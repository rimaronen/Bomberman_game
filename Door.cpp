#include "Door.h"
#include "GameResources.h"
#include "StaticAnimation.h"

// c-tor
Door::Door(const sf::Vector2f & position)
	:BoardItem(new StaticAnimation(GameResources::instance().getDoorTexture(), position))
{
}
