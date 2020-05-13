#include "LoadLevelButton.h"
#include "consts.h"

// TODO:: work on save button.

LoadLevelButton::LoadLevelButton(const level_t & levelButton, sf::RenderWindow & window)
	:MenuButtonBase(window) ,m_levelButton(levelButton)
{
	prepareTextureAndPos();

	init();
}

/*this function prepares all textures and positions of the level load buttons on menu*/
void LoadLevelButton::prepareTextureAndPos()
{

	std::string levelImage; // set text level to the given number level

	float xPos = sf::VideoMode::getDesktopMode().width / 3.0f; // change by backgrond and size of butttons
	float yPosTop = sf::VideoMode::getDesktopMode().height * (2.0f / 6.0f);
	float yPosBottom = sf::VideoMode::getDesktopMode().height * (4.5f / 6.0f);


	switch (m_levelButton)
	{
	case level_1_lv:
		levelImage = LEVEL_1_BUTTON;
		setPos({ xPos - xPos / 2.0f, yPosTop });
		break;
	case level_2_lv:
		levelImage = LEVEL_2_BUTTON;
		setPos({ (xPos * 2) - xPos / 2.0f , yPosTop });
		break;
	case level_3_lv:
		levelImage = LEVEL_3_BUTTON;
		setPos({ (xPos * 3) - xPos / 2.0f, yPosTop });
		break;
	case level_4_lv:
		levelImage = LEVEL_4_BUTTON;
		setPos({ xPos - xPos / 2.0f, yPosBottom });
		break;
	case level_5_lv:
		levelImage = LEVEL_5_BUTTON;
		setPos({ (xPos * 2) - xPos / 2.0f , yPosBottom });
		break;
	case level_6_lv:
		levelImage = LEVEL_6_BUTTON;
		setPos({ (xPos * 3) - xPos / 2.0f, yPosBottom });
	}

	loadTextureFromFile(levelImage);
}

/*return the current level button*/
level_t LoadLevelButton::getLevel() const
{
	return m_levelButton;
}
