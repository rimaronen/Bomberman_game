#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class MenuButtonBase
{
public:
	MenuButtonBase(sf::RenderWindow& window);
	// draw sprite on the window
	void draw();
	bool isPressed(const sf::Vector2f & position); // return if the current button is pressed
protected:
	void init(); // initiazlize function
	const sf::Vector2u& getWindowSize() const;
	void setPos(const sf::Vector2f& newPos); // set position for items in the menu window
	// load texture from file
	void loadTextureFromFile(const std::string& file); 
	void setRepeated();
private:
	sf::RenderWindow& m_window;
	std::unique_ptr<sf::Texture> m_texture = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::Sprite> m_sprite = std::make_unique<sf::Sprite>();
	//sf::Vector2f m_windowSize;
	sf::Vector2f m_pos; // holds the position's of the buttons in the menu window

};

