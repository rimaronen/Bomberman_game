#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "LevelLoad.h"
#include "LoadLevelButton.h"
#include "types.h"

const std::string LEVEL_LIST_FILE = "level/game.levels";

const int LEVEL_INDEX_1 = 0;
const int LEVEL_INDEX_2 = 1;
const int LEVEL_INDEX_3 = 2;
const int LEVEL_INDEX_4 = 3;
const int LEVEL_INDEX_5 = 4;
const int LEVEL_INDEX_6 = 5;

class LoadController
{
public:
	LoadController(sf::RenderWindow &window);
	const std::string* getNextLevel(); // returns the next level needed to load and start
	const std::string* getFirstLevel(); // returns the first level in the file
	const std::string* getChosenLevel(); // returns the wanted level the user chose
	const std::string* run();
	void draw();
	void resetMembers();
	size_t getNextLevelIndex() const;
	unsigned getCurrentLevelIndex() const;

private:
	void initFileNames();
	level_t handleEvents();
	// returns level name the user chose to play
	const std::string* getLevelFromPressedButton(const level_t &button);

	LevelLoad m_levelLoad; 
	level_t m_pressedLevel = no_level_lv; // holds the pressed level the user chose
	sf::RenderWindow &m_loadWindow;
	bool m_levelWindowClosed = false;
	size_t m_nextLevelIndex = 0; // for the next level waiting to be loaded
	size_t m_levelIndex = 0; // for current level played
	std::vector<std::string> m_fileNames; // string vector to keep level names while loading the level file 
	std::vector<std::unique_ptr<LoadLevelButton>> m_levelButtons; // vector for holding the buttons for load menu
};

