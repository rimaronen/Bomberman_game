#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

// base class for window managers like menu, levelload and board
class WindowManager
{
public:
	WindowManager(sf::RenderWindow& window);
protected:
	sf::RenderWindow& getWindow();
	const sf::Vector2u& getWindowSize() const;
private:
	sf::RenderWindow& m_window;
};

