#include "TimedItem.h"
#include "Sound.h"

// c-tor
TimedItem::TimedItem(Animation * animation, Sound * sound)
	:RemovableItem(animation), m_sound(sound)
{
	init();
}

// c-tor with position
TimedItem::TimedItem(Animation * animation, const sf::Vector2f & position, Sound * sound)
	: RemovableItem(animation, position), m_sound(sound)
{
	init();
}

// d-tor: releases sound
TimedItem::~TimedItem()
{
	m_sound->stop();
	delete m_sound;
}

// initialize the item by playing the sound
void TimedItem::init()
{
	m_sound->play();
}

// pause the item by pausing the sond and animation and saving the pause time
void TimedItem::pause()
{
	m_pauseTimes.push_back({ getElapsedTime().asSeconds(), 0 });
	m_sound->pause();
	getAnimation()->pause();
}

// play this item (after pause) by playing the sound and animation and saving the time this pause stopped
void TimedItem::play()
{
	m_sound->play();
	getAnimation()->unPause();
	if (!m_pauseTimes.empty() && !m_pauseTimes.back().y)
		m_pauseTimes.back().y = getElapsedTime().asSeconds();
}

// check if the given position is in the explosion radius (a timed item is either
// a bomb or an explosion so there will be an explosion here)
bool TimedItem::inAreaOfEffect(const sf::Vector2f & position) const
{
	return abs(position.x - getPosition().x) < COL_WIDTH * 2.0f
		&& abs(position.y - getPosition().y) < ROW_WIDTH * 2.0f;
}

sf::Time TimedItem::getElapsedTime() const
{
	return m_clock->getElapsedTime();
}

// returns the total amount of time this item has been paused
float TimedItem::getPauseTime() const
{
	float retVal = 0.0f;
	for (auto& time : m_pauseTimes)
		retVal += (time.y - time.x);
	return retVal;
}
