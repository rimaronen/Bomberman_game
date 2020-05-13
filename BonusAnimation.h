#pragma once
#include "Animation.h"
class BonusAnimation : public Animation
{
public:

	using::Animation::Animation; //using animation C-tor
	virtual void play(float deltaTime, sf::RenderWindow& window) override; //play animation

private:

};

