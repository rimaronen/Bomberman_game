#include "BoardItem.h"
#include "consts.h"

// c-tor with animation (must be dynamically allocated, the d-tor releases it)
BoardItem::BoardItem(Animation * animation)
	:m_animation(animation)
{
}

// c-tor with animation (must be dynamically allocated, the d-tor releases it) and position
BoardItem::BoardItem(Animation * animation, const sf::Vector2f& position)
	:m_animation(animation)
{
	setPosition(position);
}

// d-tor releases animation
BoardItem::~BoardItem()
{
	delete m_animation;
}

// draw this item on the window
void BoardItem::draw(float deltaTime, sf::RenderWindow & window)
{
	m_animation->play(deltaTime, window);
}

// set the position of this item
// a board item's position is the position of it's center
void BoardItem::setPosition(const sf::Vector2f & position)
{
	m_animation->setPosition(position);
}

// get the bounding rectangle of this item
sf::FloatRect BoardItem::getGlobalBounds() const
{
	return m_animation->getGlobalBounds();
}

// get the current position of this item on the window
const sf::Vector2f & BoardItem::getPosition() const
{
	return m_animation->getPosition();
}

Animation * BoardItem::getAnimation()
{
	return m_animation;
}

