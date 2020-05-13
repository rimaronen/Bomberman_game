#include <string>
#include <ctime>
#include "Controller.h"
#include "types.h"

// c-tor
Controller::Controller()
	:m_menuController(m_window), m_gameController(m_window), m_loadController(m_window)
{
}

// run the game. this is the main run function and the only one called from main.
// when this function returns, the program shuts down.
void Controller::run()
{
	srand((unsigned)time(nullptr));
	choice_t menuChoice;

	// create the window and set the frame rate limit
	m_window.create(sf::VideoMode(1600, 700), "Bomberman", sf::Style::Fullscreen);
	m_window.setFramerateLimit(60);


	while (m_window.isOpen()) {
		bool isVictorious = true;

		// display the menu and get the selected action
		menuChoice = m_menuController.run();
		const std::string* levelFileToLoad = nullptr;

		// perform the selected action
		switch (menuChoice) {
		case start_btn:
			levelFileToLoad = m_loadController.getFirstLevel();
			break;
		case load_btn:
			levelFileToLoad = m_loadController.run();
			break;
		case exit_btn:
			m_window.close();
			break;
		}

		// play the level, if victorious get the next level and repeat
		while (m_window.isOpen() && isVictorious && levelFileToLoad) {
			isVictorious = m_gameController.runGame(levelFileToLoad, m_loadController.getCurrentLevelIndex());
			levelFileToLoad = m_loadController.getNextLevel();
		}
	}
	m_window.close();
}
