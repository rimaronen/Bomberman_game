#include "BonusAnimation.h"
#include "consts.h"


void BonusAnimation::play(float deltaTime, sf::RenderWindow & window)
{
		m_totalTime += deltaTime; //calculate how much time pass
		
		if (m_totalTime >= m_switchTime && !m_pause)
		{
			m_totalTime -= m_switchTime;
				m_currentImage.x++; //replace picture
			if (m_currentImage.x >= m_imageCount.x) //keep on image range
				m_currentImage.x = START_IMG; //if the sprite sheets ends start again
		}

		m_intRect.left = m_currentImage.x * m_intRect.width;
		m_intRect.top = m_currentImage.y * m_intRect.height;
		Animation::play(deltaTime, window);
}

