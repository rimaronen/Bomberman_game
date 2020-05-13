#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Board;
class Robot;

class BoardItem
{
public:
	// constructor with animation only. position must be set manually after creation.
	// animation must be dynamically allocated because it is released in the d-tor.
	BoardItem(Animation * animation);
	// constructor with animation and position.
	BoardItem(Animation * animation, const sf::Vector2f& position);
	// copy constructor disabled, there is no way that makes sence to deep copy an animation
	// becase it is a base class that is not supposed to be instantiated
	BoardItem(const BoardItem & other) = delete;
	// assignement operator disabled, there is no way that makes sence to deep copy an animation
	// becase it is a base class that is not supposed to be instantiated
	BoardItem& operator=(const BoardItem & other) = delete;
	// distructor, deletes the animation object
	virtual ~BoardItem();
	// draw this item on the provided window
	virtual void draw(float deltaTime, sf::RenderWindow &window);
	// sets the position on which this board item will be drawn on the game window
	// set a new position for this board ite. a board item's position is the position of it's center
	virtual void setPosition(const sf::Vector2f& position);
	// returns the bounding rectangle of this item
	virtual sf::FloatRect getGlobalBounds() const;
	// a board item's position is the position of it's center
	const sf::Vector2f & getPosition() const;
protected:
	// provides the internal animation member for member functions to process
	Animation * getAnimation();
private:
	// the internal animation member
	Animation * m_animation;
};

