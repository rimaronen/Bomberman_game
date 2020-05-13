#pragma once
#include "RemovableItem.h"
#include "consts.h"

class Sound;

// base class for bombs and explosions
class TimedItem :
	public RemovableItem
{
public:
	TimedItem(Animation * animation, Sound * sound);
	TimedItem(Animation * animation, const sf::Vector2f& position, Sound * sound);
	~TimedItem();
	// conceptually every timed item has a time to live, this function will tell if that time has passed
	virtual bool didTimeOut() const = 0;
	void pause();
	void play();
	// tells if the given position will be affected by the explosion
	bool inAreaOfEffect(const sf::Vector2f & position) const;
protected:
	sf::Time getElapsedTime() const;
	// computes all the time this item was in pause condition
	float getPauseTime() const;
private:
	void init();
	std::unique_ptr<sf::Clock> m_clock = std::make_unique<sf::Clock>();
	Sound * m_sound;

	// clock time when paused and continued
	std::vector<sf::Vector2f> m_pauseTimes;
};

