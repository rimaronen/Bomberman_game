#pragma once
#include "Animation.h"

const unsigned STATICA_IMAGE_COUNT_X = 1;
const unsigned STATICA_IMAGE_COUNT_Y = 1;
const float NO_SWITCH_TIME = std::numeric_limits<float>::max();
const float IMAGE_SIZE_X = 75.0f;
const float IMAGE_SIZE_Y = 75.0f;

class StaticAnimation :
	public Animation
{
public:
	StaticAnimation(sf::Texture & texture);
	StaticAnimation(sf::Texture & texture, const sf::Vector2f& position);
	void init();
};

