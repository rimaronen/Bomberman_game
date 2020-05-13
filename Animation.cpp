#include "Animation.h"
#include "consts.h"

const float IMAGE_SIZE_X = 50.0f;
const float IMAGE_SIZE_Y = 50.0f;
//animation C-tor
Animation::Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime)
	:m_imageCount(imageCount), m_switchTime(switchTime), m_rectShape(sf::Vector2f(IMAGE_SIZE_X, IMAGE_SIZE_Y))
{
	init(texture);
}
//animation C-tor
Animation::Animation(sf::Texture& texture, sf::Vector2u imageCount, const sf::Vector2f& position, float switchTime)
	: m_imageCount(imageCount), m_switchTime(switchTime), m_rectShape(sf::Vector2f(IMAGE_SIZE_X, IMAGE_SIZE_Y))
{
	//calculate the rectangle size//
	m_rectShape.setPosition(position);
	init(texture);
}
//this function inittializes all the texture data
void Animation::init(sf::Texture& texture)
{
	m_intRect.width = texture.getSize().x / m_imageCount.x;
	m_intRect.height = texture.getSize().y / m_imageCount.y;
	texture.setSmooth(true);
	m_rectShape.setTexture(&texture);
	m_currentImage.x = IDLE_POS;
	m_rectShape.setOrigin({ IMAGE_SIZE_X / 2.0f, IMAGE_SIZE_Y / 2.0f });
}
//draw the animation
void Animation::play(float deltaTime, sf::RenderWindow& window)
{
	m_rectShape.setTextureRect(m_intRect);
	window.draw(m_rectShape);
}
//set the animation position
void Animation::setPosition(const sf::Vector2f& position)
{
	m_rectShape.setPosition(position);
}
//get the animation position
const sf::Vector2f & Animation::getPosition() const
{
	return m_rectShape.getPosition();
}
//get the global bounds for collision 
sf::FloatRect Animation::getGlobalBounds() const
{
	return m_rectShape.getGlobalBounds();
}
//pause
void Animation::pause()
{
	m_pause = true;
}
//unpause
void Animation::unPause()
{
	m_pause = false;
	m_totalTime = 0.0f;
}
