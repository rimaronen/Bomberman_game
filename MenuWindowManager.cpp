#include "MenuWindowManager.h"
#include "MenuButtonBase.h"

MenuWindowManager::MenuWindowManager(sf::RenderWindow & window)
	:WindowManager(window)
{
}

/*ths function draws the backround of the menu and load windoe*/
void MenuWindowManager::draw()
{
	getWindow().draw(*m_rectShape); // draw background
}

void MenuWindowManager::loadTextureFromFile(std::string file)
{
	if (!m_texture->loadFromFile(file))
		exit(EXIT_FAILURE);
}

/*prepare background texture*/
void MenuWindowManager::prepareTextureBG()
{
	m_texture->setSmooth(true);
	m_rectShape->setTexture(&*m_texture);
}

// set the size of the rectangle shape
void MenuWindowManager::setSize(const sf::Vector2f & size)
{
	m_rectShape->setSize(size);
}

void MenuWindowManager::setRepeated()
{
	m_texture->setRepeated(true);
}
 
/*set the rectangle texture*/ 
void MenuWindowManager::setTextureRect(sf::IntRect rect)
{
	m_rectShape->setTextureRect(rect);
}

/*this function sets the winfow size for the background menu and load window*/
void MenuWindowManager::windowIsOpen()
{
	setSize(sf::Vector2f((float)getWindow().getSize().x, (float)getWindow().getSize().y)); // set menu background size
}
