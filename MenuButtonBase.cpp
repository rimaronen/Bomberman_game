#include "MenuButtonBase.h"

/*Menu button base constructor */
MenuButtonBase::MenuButtonBase(sf::RenderWindow & window)
	:m_window(window)
{
}

/*this function initialize the texture and the position of the elements on the menu window*/
void MenuButtonBase::init()
{
	m_sprite->setTexture(*m_texture);
	m_sprite->setPosition(m_pos);
	m_sprite->setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
}

const sf::Vector2u & MenuButtonBase::getWindowSize() const
{
	return m_window.getSize();
}

void MenuButtonBase::setPos(const sf::Vector2f & newPos)
{
	m_pos = newPos;
}

void MenuButtonBase::loadTextureFromFile(const std::string & file)
{
	if (!m_texture->loadFromFile(file))
		exit(EXIT_FAILURE);
	m_texture->setSmooth(true);
}

void MenuButtonBase::setRepeated()
{
	m_texture->setRepeated(true);
}

/*draw the icon level sprite*/
void MenuButtonBase::draw()
{
	m_window.draw(*m_sprite);
}

/*this function return true if the icon at the position is pressed or not*/
bool MenuButtonBase::isPressed(const sf::Vector2f & position)
{
	return m_sprite->getGlobalBounds().contains(position);
}
