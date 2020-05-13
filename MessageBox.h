#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

const unsigned MB_OUTLINE_THICKNESS = 3;
const unsigned PADDING = 5;

// message types enum
enum message_type_t { game_over_msg, victory_msg, pause_msg };

class MessageBox
{
public:
	// c-tor with RenderWindow reference
	MessageBox(sf::RenderWindow& window);
	// displays the provided message on the center of the window
	void display(const std::string& message, message_type_t messaegType);
	// tells if this message box is supposed to be displaying
	bool shouldDisplay() const;
	// sets this message box to not display
	void doNotDisplay();
	// draws this message box on the screen
	void draw();
	// returns the message type of this message box
	message_type_t getMessageType() const;
private:
	// sf::Text object to display the message in
	std::unique_ptr<sf::Text> m_text = std::make_unique<sf::Text>();
	// sf::RectangleShape for the background of the message box
	std::unique_ptr<sf::RectangleShape> m_rect = std::make_unique<sf::RectangleShape>();
	// reference to the sf::RenderWindow on which to display this message box
	sf::RenderWindow& m_window;
	// the type of the currently displayed message
	message_type_t m_messageType = pause_msg;
	// if true this message box should display, else this message box should not display 
	bool m_display = false;
};

