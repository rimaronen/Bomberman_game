#include "Rock.h"
#include "StaticAnimation.h"
#include "GameResources.h"

// c-tor
Rock::Rock(const sf::Vector2f & position)
	:RemovableItem(new StaticAnimation(GameResources::instance().getRockTexture()), position)
{
}
