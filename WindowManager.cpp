#include "WindowManager.h"

// c-tor
WindowManager::WindowManager(sf::RenderWindow& window)
	:m_window(window)
{
}

sf::RenderWindow & WindowManager::getWindow()
{
	return m_window;
}

const sf::Vector2u & WindowManager::getWindowSize() const
{
	return m_window.getSize();
}
