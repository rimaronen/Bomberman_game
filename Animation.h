#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

const int IDLE_POS = 1; //idle position

class Animation
{
public:
	//constructor that build the animation only without postion
	Animation(sf::Texture & texture, sf::Vector2u imageCount, float switchTime);
	////constructor that build the animation only with postion
	Animation(sf::Texture & texture, sf::Vector2u imageCount, const sf::Vector2f& position, float switchTime);
	//initialize the texture
	void init(sf::Texture & texture);
	//this function play the animation
	virtual void play(float deltaTime, sf::RenderWindow& window);
	//set the animation position
	void setPosition(const sf::Vector2f& position);
	//return the position
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	//pause and unpause the animation
	virtual void pause();
	virtual void unPause();

protected:

	sf::IntRect m_intRect;
	sf::RectangleShape m_rectShape;
	sf::RectangleShape m_centerShape;
	sf::Vector2u m_imageCount; //store how much pictures we have in a row and col 
	sf::Vector2u m_currentImage;

	float m_totalTime = 0.0f;
	float m_switchTime; //this member control the speed of the animation
	bool m_pause = false;
	move_t m_dir = no_mov; 
};

