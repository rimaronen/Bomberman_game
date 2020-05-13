#pragma once
#include "Animation.h"

//animation position
const int UP_POS = 3;
const int DOWN_POS = 0;
const int LEFT_POS = 1;
const int RIGHT_POS = 2;

class PlayerAnimation :
	public Animation
{
public:
	//using 
	using::Animation::Animation;
	//play the animation
	virtual void play(float totalTime, sf::RenderWindow& window) override;

	void up(); //set up position
	void down(); //set down position
	void left(); //set left position
	void right(); //set right position
	void idle(); //set idle position
	void move(const sf::Vector2f& offset);
};

