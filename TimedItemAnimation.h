#pragma once
#include <sfml/graphics.hpp>
#include "Animation.h"

class TimedItemAnimation 
	: public Animation
{
public:
	//using C-tor animation
	using::Animation::Animation;
	//play the animation
	virtual void play(float deltaTime, sf::RenderWindow& window) override;
};

