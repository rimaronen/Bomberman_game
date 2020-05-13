#include "LoadController.h"
#include "types.h"


/*load controller constractor*/
LoadController::LoadController(sf::RenderWindow & window)
	:m_loadWindow(window), m_levelLoad(window, m_levelButtons)
{
	for (int button = level_1_lv; button < no_level_lv; ++button)
		m_levelButtons.push_back(std::make_unique<LoadLevelButton>((level_t)button, m_loadWindow));
	initFileNames();
}

// return next level. returns nullptr if there is no next level.
const std::string* LoadController::getNextLevel()
{
	if (m_nextLevelIndex >= m_fileNames.size())
		return nullptr;
	std::string* levelNumber = &m_fileNames[m_nextLevelIndex];
	m_nextLevelIndex++; // increas index for the next level
	return levelNumber;
}

const std::string * LoadController::getFirstLevel()
{
	m_nextLevelIndex = 1;
	return &m_fileNames[0];
}

const std::string* LoadController::getChosenLevel()
{
	m_nextLevelIndex = m_levelIndex + 1;
	return &m_fileNames[m_levelIndex];
}

/*this function acceptes level names files and enter them to the vector by reading each line from it*/
void LoadController::initFileNames()
{
	std::ifstream fileNames;
	std::string level;

	fileNames.open(LEVEL_LIST_FILE); // open the file that contains the level names

	while (!fileNames.eof()) {
		std::getline(fileNames, level);
		m_fileNames.push_back(level); // enter level name to file names vector
	}

	fileNames.close();
}

level_t LoadController::handleEvents()
{
	sf::Event event;
	sf::Vector2f coords;

	while (m_loadWindow.pollEvent(event)) {

		if (m_pressedLevel != no_level_lv)
			m_levelWindowClosed = true;

		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			coords = m_loadWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			m_pressedLevel = m_levelLoad.getMouseButtonPressed(coords); // get level name from the coords where pressed
			break;
		case sf::Event::Closed:
			m_loadWindow.close();
			break;
		case sf::Event::EventType::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				m_levelWindowClosed = true;
				m_loadWindow.close();
			}
			else
				m_pressedLevel = m_levelLoad.getKeyPressedEvent(event);
		}
	}
	return m_pressedLevel;
}

/*this function returns the name of the file to load in the controller game, by the chosen level the user chose*/
const std::string* LoadController::getLevelFromPressedButton(const level_t & button)
{
	//std::string* str = getNextLevel();
	switch (button)
	{
	case level_1_lv:
		m_levelIndex = LEVEL_INDEX_1;
		return getChosenLevel();
	case level_2_lv:
		m_levelIndex = LEVEL_INDEX_2;
		return getChosenLevel();
	case level_3_lv:
		m_levelIndex = LEVEL_INDEX_3;
		return getChosenLevel();
	case level_4_lv:
		m_levelIndex = LEVEL_INDEX_4;
		return getChosenLevel();
	case level_5_lv:
		m_levelIndex = LEVEL_INDEX_5;
		return getChosenLevel();
	case level_6_lv:
		m_levelIndex = LEVEL_INDEX_6;
		return getChosenLevel();
	}
	return nullptr;
}

/*this function returns the next level needed to load in the game*/
size_t LoadController::getNextLevelIndex() const
{
	return m_nextLevelIndex;
}

unsigned LoadController::getCurrentLevelIndex() const
{
	return m_nextLevelIndex;
}

/*main loop for load menu*/
const std::string* LoadController::run()
{
	m_levelLoad.windowIsOpen();
	m_levelLoad.prepareLoadLevelBG(); // prepare the backgroung texture

	while (!m_levelWindowClosed) {

		while (m_loadWindow.isOpen() && !m_levelWindowClosed) {
			draw();
			m_pressedLevel = handleEvents();
		}
	}
	m_loadWindow.clear();

	const std::string* retVal = getLevelFromPressedButton(m_pressedLevel); // return the next level to be loaded
	resetMembers();
	return retVal;
}

/*this function draw all the load menu item on the board*/
void LoadController::draw()
{
	m_loadWindow.clear();
	m_levelLoad.draw();
	m_loadWindow.display();
}

/*this function resets the member of load menu window*/
void LoadController::resetMembers()
{
	m_levelWindowClosed = false;
	m_pressedLevel = no_level_lv;
}
