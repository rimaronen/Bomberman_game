#include "Wall.h"
#include "GameResources.h"
#include "StaticAnimation.h"

// c-tor
Wall::Wall(const sf::Vector2f & position)
	:BoardItem(new StaticAnimation(GameResources::instance().getWallTexture(), position))
{
}
