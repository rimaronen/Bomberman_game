#include "PlayerAnimation.h"
#include "consts.h"




void PlayerAnimation::play(float deltaTime, sf::RenderWindow& window)
{
	m_totalTime += deltaTime; //calculate how much time pass

	if (m_totalTime >= m_switchTime && !m_pause)
	{
		m_totalTime -= m_switchTime;
		if (m_dir != no_mov)
			m_currentImage.x++; //replace picture

		if (m_currentImage.x >= m_imageCount.x) //keep on image range
			m_currentImage.x = START_IMG; //if the sprite sheets ends start again
	}

	m_intRect.left = m_currentImage.x * m_intRect.width;
	m_intRect.top = m_currentImage.y * m_intRect.height;
	Animation::play(deltaTime, window);
}

//this section handle the characters position
//=================================
void PlayerAnimation::up()
{
	m_dir = up_mov;
	m_currentImage.y = UP_POS;
}

void PlayerAnimation::down()
{
	m_dir = down_mov;
	m_currentImage.y = DOWN_POS;
}

void PlayerAnimation::left()
{
	m_dir = left_mov;
	m_currentImage.y = LEFT_POS;
}

void PlayerAnimation::right()
{
	m_dir = right_mov;
	m_currentImage.y = RIGHT_POS;
}

void PlayerAnimation::idle()
{
	m_dir = no_mov;
	m_currentImage.x = IDLE_POS;
}
void PlayerAnimation::move(const sf::Vector2f & offset)
{
	m_rectShape.move(offset);
}
//=================================