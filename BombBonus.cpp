#include "BombBonus.h"
#include "BonusAnimation.h"
#include "Robot.h"
//bomb bonus C-tor 
//Initializing the data and create new animation for the bomb
BombBonus::BombBonus(const sf::Vector2f & position)
	:BonusItem(new BonusAnimation(GameResources::instance().getBombBonusTexture(),
		sf::Vector2u(BOMB_BONUS_IMAGE_COUNT_X, BOMB_BONUS_IMAGE_COUNT_Y), position, BOMB_BONUS_SWITCH_TIME))
{
}
//play the anitmation
void BombBonus::play(float deltaTime, sf::RenderWindow & window)
{
	getAnimation()->play(deltaTime, window);
}
//effect the robot by increase bomb
void BombBonus::affectRobot(Robot & robot)
{
	robot.increaseBombQuantity(BOMB_BONUS_AMOUNT);
}


