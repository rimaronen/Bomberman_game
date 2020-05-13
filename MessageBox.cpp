#include "MessageBox.h"
#include "GameResources.h"
#include "consts.h"

// c-tor
MessageBox::MessageBox(sf::RenderWindow & window)
	:m_window(window)
{
	// init text
	m_text->setFont(GameResources::instance().getCbFont());
	m_text->setCharacterSize(CHARACTER_SIZE);
	m_text->setFillColor(sf::Color::Black);
	
	// init background rect shape
	m_rect->setFillColor(sf::Color(255, 255, 255, 128));
	m_rect->setOutlineColor(sf::Color::White);
	m_rect->setOutlineThickness(MB_OUTLINE_THICKNESS);
}

// display this message
void MessageBox::display(const std::string& message, message_type_t messageType)
{
	// set text
	m_text->setString(message);
	sf::FloatRect textBounds = m_text->getLocalBounds();
	m_text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_text->setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
	
	// set rect
	m_rect->setSize({ textBounds.width + PADDING, textBounds.height + PADDING });
	m_rect->setOrigin({ m_rect->getSize().x / 2.0f, m_rect->getSize().y / 2.0f });
	m_rect->setPosition({ m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f });
	
	m_display = true;
	m_messageType = messageType;
}

// tells if this message box should display
bool MessageBox::shouldDisplay() const
{
	return m_display;
}

// tells this message box to not display
void MessageBox::doNotDisplay()
{
	m_display = false;
}

// tells this message box it's time to draw itself if it should draw
void MessageBox::draw()
{
	if (m_display) {
		m_window.draw(*m_rect);
		m_window.draw(*m_text);
	}
}

message_type_t MessageBox::getMessageType() const
{
	return m_messageType;
}
