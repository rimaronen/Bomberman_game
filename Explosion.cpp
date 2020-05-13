#include "Explosion.h"
#include "TimedItemAnimation.h"
#include "consts.h"
#include "GameResources.h"
#include "Sound.h"

// c-tor
Explosion::Explosion(const sf::Vector2f & position)
	:TimedItem(new TimedItemAnimation(GameResources::instance().getExplosionTexture(),
	sf::Vector2u(EXPLOSION_IMAGE_COUNT_X, EXPLOSION_IMAGE_COUNT_Y), position, switchTime),
	new Sound(GameResources::instance().getExplosionBuffer()))
{
	// init side offsets. an explosion spans 5 board cells. the center at position, and the for sides
	// up, down, left and right of position.
	static std::vector<sf::Vector2f> sideOffsets = {
		{(float)COL_WIDTH, 0.0f}, {(float)-COL_WIDTH, 0.0f}, {0.0f, (float)ROW_WIDTH}, {0.0f, (float)-ROW_WIDTH}
	};

	// add the side animations
	for (unsigned i = 0; i < NUM_OF_SIDES; ++i) {
		m_sides.push_back(std::make_unique<TimedItemAnimation>(
			GameResources::instance().getExplosionTexture(),
			sf::Vector2u(EXPLOSION_IMAGE_COUNT_X, EXPLOSION_IMAGE_COUNT_Y), position, switchTime));
		m_sides.back()->setPosition(position + sideOffsets[i]);
	}
}

// tells if this explosion has outlived it's duration.
bool Explosion::didTimeOut() const
{
	return getElapsedTime().asSeconds() - getPauseTime() >= EXPLOSION_TIME_OUT;
}

// tells if this explosion intersects (it's center or the sides) with this item.
bool Explosion::intersects(BoardItem & item)
{
	if (getGlobalBounds().intersects(item.getGlobalBounds()))
		return true;
	for (size_t i = 0; i < NUM_OF_SIDES; ++i)
		if (m_sides[i]->getGlobalBounds().intersects(item.getGlobalBounds()))
			return true;
	return false;
}

// draw this explosion on the board
void Explosion::draw(float deltaTime, sf::RenderWindow & window)
{
	BoardItem::draw(deltaTime, window);
	for (size_t i = 0; i < NUM_OF_SIDES; ++i)
		m_sides[i]->play(deltaTime, window);
}
