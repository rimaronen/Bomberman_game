#pragma once
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "Board.h"
#include "Guard.h"
#include "Robot.h"
#include "Rock.h"
#include "BonusItem.h"
#include "Bomb.h"
#include "Explosion.h"
#include "ControlBarController.h"
#include "MessageBox.h"
#include "Graph.h"
#include "Sound.h"

const int MINUTE = 60; // minute is 60 in terms of seconds
const int SECOND = 1000; // second is 1000 in terms of milliseconds
const float BFS_TIME = 1.0f; // time between running BFS on graph
const float MESSAGE_TIME = 3.0f; // duration time for message box messages
const std::string GAME_OVER_MESSAGE = "Game Over.";
const std::string VICTORY_MESSAGE = "You Win!";
const std::string GAME_BG_FILE = "img/gamebackgrond1.jpg";

// when adding a guard gc will generate a random 0 or 1, which stands for
// clever or simple guard:
const unsigned GUARD_LOTTO_CLEVER = 0;
const unsigned GUARD_LOTTO_SIMPLE = 1;

// when adding a bonus item gc will generate a number in range [0,4] for
// one of the four possible bonuses. unless the bonus is being added under a '@' rock, in which case
// gc will generate a number in range [0,8] to provide a 50% chance for a bonus. '&' rocks have 100%
// chance for a bonus and gc gererates a number in range [0,4].
const int BONUS_LOTTO_MAX = 8;
const int NUM_BUNUS_ITEMS = 4;
const int SPEED_BONUS = 0;
const int BOMB_BONUS = 1;
const int COIN_BONUS = 2;
const int LIFE_BONUS = 3;

// number of milliseconds left to the level when alarm starts
const int ALARM_TIME_LEFT = 10000;
// the width of the gap to the left of the game board between the game board and the control bar panel
const float GAME_CONTROL_BAR_GAP = 75;

//class Graph
struct AlarmData {
	int m_alarmStartTime; 
	bool m_changeToAlarmColor = true;
	bool m_playAlarm = false;
	bool m_setTimeAlarm = true;
};

class GameController
{
public:
	GameController(sf::RenderWindow &gameWindow);
	// run a single level. return true if victoriouse, false if not
	bool runGame(const std::string* levelFileName, unsigned levelIndex);
	// used to map a board cell (x, y coordinates) into an index in an array with
	// size same as number of cells in the board
	unsigned convertCoordsToBoardCellIndex(const sf::Vector2i &position);
	// convert sizes in terms of rows and columns (game specific) into actual sizes in sfml coordinate system.
	sf::Vector2f gameCoordsToSFCoords(const sf::Vector2i& coords) const;
	// converts game coords to sfml coords and adds the top left corner of the board
	// to provide an accurate position on the board
	sf::Vector2f gameCoordsToSFCoordsRelToBoard(const sf::Vector2i & coords) const;
	// converts coords to pixels and provides the center of the board cell the coords refer to
	sf::Vector2f gameCoordsToSFCoordsCentered(const sf::Vector2i& coords) const;
	// converts sfml coordinates into game col and row
	sf::Vector2i sfCoordsToGameCoords(sf::Vector2f pix) const;
	// provide access to the mapCoordsToPix of the sf::RenderWindow object member
	sf::Vector2i mapCoordsToPix(const sf::Vector2f& coords);

private:
	void mainLoopAction();
	// reset members when time is up
	void fullResetMembers();
	// reset members when robot die
	void resetOnDeath();
	void partReset();
	// check if robot is on a bonus item and collect it
	void checkIfRobotIsOnBonus();
	// load a level from file
	void loadLevelFile();
	void processLine(std::string &line, int row);
	void initGameSettings(float timeLimit, int bombQuantity);
	void resetHiddenBonusMap();
	// draw the entire game
	void draw(float deltaTime);
	void drawExplosions(float deltaTime);
	void drawBombs(float deltaTime);
	void drawControlBar();
	int computeTimeLeftMilliseconds();
	void drawMessageBox(float deltaTime);
	void checkIfRobotColidesWithGuards();
	void checkIfRobotIsAtTheDoor();
	// stuff to do when the robot passes the door
	void robotWins();
	void explodeBombs();
	bool explodeItems(std::unique_ptr<Explosion> & explosion);
	void explodeGuards(std::unique_ptr<Explosion> & explosion);
	void explodeRocks(std::unique_ptr<Explosion> & explosion);
	// add a bonus item at the given position. if noRandom is false, the item has a half chance of being added.
	// else it will be added for sure.
	void addBonusAt(const sf::Vector2f & position, bool noRandom = false);
	// stuff to do when robot colided with a guard or an explosion
	void robotDies();
	void handleEvents();
	void handleKeyReleasedEvent(sf::Keyboard::Key keyCode);
	// pause the game
	void pause();
	// unpause the game
	void unPause();
	void movePlayers(float deltaTime);
	void playAlaram();
	void setAlarmColors();

	const std::string* m_levelFileName;

	sf::RenderWindow& m_gameWindow;

	// graphics and sounds
	std::unique_ptr<sf::Texture> m_bgTexture = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::RectangleShape> m_bgRect = std::make_unique<sf::RectangleShape>();
	std::unique_ptr<Sound> m_alarmSound = std::make_unique<Sound>(GameResources::instance().geAlarmBuffer());
	std::unique_ptr<Sound> m_bgGameSound = std::make_unique<Sound>(GameResources::instance().getBgGameBuffer());

	// the control bar
	std::unique_ptr<ControlBarController> m_controlBarController;

	// clocks
	std::unique_ptr<sf::Clock> m_moveAndDrawClock = std::make_unique<sf::Clock>();
	std::unique_ptr<sf::Clock> m_timeLimitClock = std::make_unique<sf::Clock>();

	// game board
	std::unique_ptr<Board> m_board;

	// players
	std::unique_ptr<Robot> m_robot;
	std::vector<std::unique_ptr<Guard>> m_guards;

	// bombs and explosions
	std::vector<std::unique_ptr<Bomb>> m_bombs;
	std::vector<std::unique_ptr<Explosion>> m_explosions;

	std::vector<std::unique_ptr<Rock>> m_rocks;
	// bonuses like life and bombs
	std::vector<std::unique_ptr<BonusItem>> m_bonuses;
	// this vector maps boolean values (hidden bonus exists/doesn't exist) to board cells
	std::vector<bool> m_hiddenBonusMap;

	// message box for messages when robot wins or game over
	std::unique_ptr<MessageBox> m_messageBox;

	// graph for AI calculations: represents the board as a graph and performs BFS on it to find the
	// shortest path from the robot to every board cell (used by clever guards)
	std::unique_ptr<Graph> m_graph;

	// clock time when paused and continued
	std::vector<sf::Vector2i> m_pauseTimes;

	sf::Vector2i m_boardSize = { 0, 0 };
	int m_timeLimitMilliseconds;
	// number of guards on level start
	int m_numOfInitGuards = 0;
	unsigned m_currentLevelIndex = 0;
	float m_bfsTimeAccumulator = 0.0f;
	float m_messageBoxTimeAccumulator = 0.0f;
	bool m_gameOver = false;
	bool m_didWin = false;
	bool m_pause = false;
	// used to follow the state of the alarm at last 10 seconds
	AlarmData m_alarmData;
};

