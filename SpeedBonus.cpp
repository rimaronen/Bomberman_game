#include "SpeedBonus.h"
#include "BonusAnimation.h"
#include "Robot.h"
//C-tor
//Initializing the data and create new animation for the speed bonus
SpeedBonus::SpeedBonus(const sf::Vector2f & position)
	:BonusItem(new BonusAnimation(GameResources::instance().getSpeedBonusTexture(),
		sf::Vector2u(SPEED_BONUS_IMAGE_COUNT_X, SPEED_BONUS_IMAGE_COUNT_Y), position, SPEED_BONUS_SWITCH_TIME))
{
}
//play the animation
void SpeedBonus::play(float deltaTime, sf::RenderWindow & window)
{
	play(deltaTime, window);
}
//effect robot by increase speed
void SpeedBonus::affectRobot(Robot & robot)
{
	robot.run();
}

