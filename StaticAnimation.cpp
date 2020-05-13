#include "StaticAnimation.h"
#include <limits>

StaticAnimation::StaticAnimation(sf::Texture & texture)
	:Animation(texture, { STATICA_IMAGE_COUNT_X, STATICA_IMAGE_COUNT_Y }, NO_SWITCH_TIME)
{
	init();
}

StaticAnimation::StaticAnimation(sf::Texture & texture, const sf::Vector2f & position)
	:Animation(texture, { STATICA_IMAGE_COUNT_X, STATICA_IMAGE_COUNT_Y }, position, NO_SWITCH_TIME)
{
	init();
}

void StaticAnimation::init()
{
	m_rectShape.setSize({ IMAGE_SIZE_X, IMAGE_SIZE_Y });
	m_rectShape.setOrigin({ IMAGE_SIZE_X / 2.0f, IMAGE_SIZE_Y / 2.0f });
}
