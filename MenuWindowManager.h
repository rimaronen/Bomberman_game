#pragma once
#include "WindowManager.h"

class MenuButtonBase;

class MenuWindowManager :
	public WindowManager
{
public:
	MenuWindowManager(sf::RenderWindow &window);
	virtual void draw();
	// load texture from file
	void loadTextureFromFile(std::string file);
	// prepare menu and load window backgrounds
	void prepareTextureBG();
	// set menu and load rectangle size
	void setSize(const sf::Vector2f& size);
	void setRepeated();
	void setTextureRect(sf::IntRect rect);
	// set menu and load window size
	void windowIsOpen();

private:
	std::unique_ptr<sf::Texture> m_texture = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::RectangleShape> m_rectShape = std::make_unique<sf::RectangleShape>();
	sf::IntRect m_rect;
};

