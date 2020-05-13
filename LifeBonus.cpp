#include "LifeBonus.h"
#include "BonusAnimation.h"
#include "Robot.h"

//C-tor
//Initializing the data and create new animation for the life bonus
LifeBonus::LifeBonus(const sf::Vector2f & position)
	:BonusItem(new BonusAnimation(GameResources::instance().getLifeTexture(),
		sf::Vector2u(LIFE_BONUS_IMAGE_COUNT_X, LIFE_BONUS_IMAGE_COUNT_Y), position, LIFE_BONUS_SWITCH_TIME))
{
}
//play animation
void LifeBonus::play(float deltaTime, sf::RenderWindow & window)
{
	getAnimation()->play(deltaTime, window);

}
//effect robot by increase life
void LifeBonus::affectRobot(Robot & robot)
{
	robot.increaseLifeQuantity(LIFE_BONUS_AMOUNT);

}
