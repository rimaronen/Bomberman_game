#pragma once
#include "BonusItem.h"



const unsigned SCORE_BONUS_AMOUNT = 100;
// the animation will switch frames by this time (in seconds)
const float COIN_BONUS_SWITCH_TIME = 0.3f;
// the texture will have this many frames in every row
const unsigned COIN_BONUS_IMAGE_COUNT_X = 10;
// the texture will have this many rows of frames
const unsigned COIN_BONUS_IMAGE_COUNT_Y = 1;

class CoinBonus :
	public BonusItem
{
public:
	//constractor get position
	CoinBonus(const sf::Vector2f& position);
	//play the animation
	virtual void play(float deltaTime, sf::RenderWindow &window);
	//pause and unpause the animation 
	virtual void pause();
	virtual void unPause();
	//effect the robot by score
	virtual void affectRobot(Robot& robot) override;

private:

};