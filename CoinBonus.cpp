#include "CoinBonus.h"
#include "BonusAnimation.h"
#include "Robot.h"

CoinBonus::CoinBonus(const sf::Vector2f & position)
	:BonusItem(new BonusAnimation(GameResources::instance().getCoinTexture(),
		sf::Vector2u(COIN_BONUS_IMAGE_COUNT_X, COIN_BONUS_IMAGE_COUNT_Y), position, COIN_BONUS_SWITCH_TIME))
{
}
//play the animation
void CoinBonus::play(float deltaTime, sf::RenderWindow & window)
{
	play(deltaTime, window);
}

void CoinBonus::pause()
{
	pause();
}

void CoinBonus::unPause()
{
	unPause();
}
//effect the robot by increase score.

void CoinBonus::affectRobot(Robot & robot)
{
	robot.increaseScoreBy(SCORE_BONUS_AMOUNT);
}
