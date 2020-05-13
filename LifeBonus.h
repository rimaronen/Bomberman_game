#include "BonusItem.h"


const unsigned LIFE_BONUS_AMOUNT = 1;
// the animation will switch frames by this time (in seconds)
const float LIFE_BONUS_SWITCH_TIME = 0.07f;
// the texture will have this many frames in every row
const unsigned LIFE_BONUS_IMAGE_COUNT_X = 14;
// the texture will have this many rows of frames
const unsigned LIFE_BONUS_IMAGE_COUNT_Y = 1;

class Robot;

class LifeBonus :
	public BonusItem
{
public:
	//constractor get position
	LifeBonus(const sf::Vector2f& position);
	//play the animation
	virtual void play(float deltaTime, sf::RenderWindow &window);
	//effect the robot by life
	virtual void affectRobot(Robot& robot) override;
};

