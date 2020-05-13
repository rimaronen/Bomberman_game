#include <iostream>
#include <algorithm>
#include <experimental/vector>
#include "GameController.h"
#include "consts.h"
#include "SimpleGuard.h"
#include "CleverGuard.h"
#include "Bomb.h"
#include "wintools.h"
#include "Graph.h"
#include "BombBonus.h"
#include "CoinBonus.h"
#include "SpeedBonus.h"
#include "LifeBonus.h"

// c-tor
GameController::GameController(sf::RenderWindow &gameWindow)
	:m_board(std::make_unique<Board>(gameWindow, m_rocks)),
	m_robot(std::make_unique<Robot>(*m_board)),
	m_gameWindow(gameWindow),
	m_controlBarController(std::make_unique<ControlBarController>(m_robot)),
	m_messageBox(std::make_unique<MessageBox>(m_gameWindow)),
	m_graph(std::make_unique<Graph>(*this))
{
	// load window background image
	if (!m_bgTexture->loadFromFile(GAME_BG_FILE))
		exit(EXIT_FAILURE);
}


// run a single level of this game
bool GameController::runGame(const std::string* levelFileName, unsigned levelIndex)
{
	m_currentLevelIndex = levelIndex;

	// this needs to be reset on start (code on Controller depends on the value of m_didWin returned by runGame)
	m_didWin = false;

	// load level file
	m_levelFileName = levelFileName;
	loadLevelFile();

	// make m_bgSprite span the entire size of the window
	m_bgRect->setSize(sf::Vector2f((float)m_gameWindow.getSize().x, (float)m_gameWindow.getSize().y));


	m_bgRect->setTexture(&*m_bgTexture);

	m_numOfInitGuards = (int)m_guards.size();

	// lose initialization gap time in the clock
	m_moveAndDrawClock->restart();
	m_timeLimitClock->restart();

	// main game loop
	while (m_gameWindow.isOpen() && !m_gameOver && !m_didWin)
		mainLoopAction();

	fullResetMembers();
	m_robot->reset();
	if (m_gameOver)
		m_robot->resetScore();

	return m_didWin;
}

// do this as long as the window is open and the game is not over or won
void GameController::mainLoopAction()
{
	float deltaTime = m_moveAndDrawClock->restart().asSeconds();
	draw(deltaTime);
	handleEvents();

	// handle BFS
	if (m_bfsTimeAccumulator == 0) {
		// initialize the data in the graph for the first moves of the guards in the game
		m_graph->initData(m_rocks, m_board->getStaticItems(), m_boardSize.y, m_boardSize.x);
		sf::Vector2f pos = m_robot->getPosition();
		sf::Vector2i robPos = sfCoordsToGameCoords(pos);
		// start BFS from robot's position to the rest of the points in the graph
		m_graph->BFS(sfCoordsToGameCoords(m_robot->getPosition()));
	}
	m_bfsTimeAccumulator += deltaTime;
	if (m_bfsTimeAccumulator >= BFS_TIME)
		m_bfsTimeAccumulator = 0.0f;

	if (!m_pause) {
		movePlayers(deltaTime);
		m_bgGameSound->play();
		m_bgGameSound->loop();
	}

	// check if time limit reached
	int timeLeft = computeTimeLeftMilliseconds();
	if (timeLeft != UNLIMITED_TIME && timeLeft < 0)
		robotDies();
}

// reset everything. do it if game is over or time is out
void GameController::fullResetMembers()
{
	partReset();
	m_board->resetMembers();
	m_gameOver = false;
	m_alarmSound->stop();
	m_bgGameSound->stop();
	m_messageBox->doNotDisplay();
	m_bfsTimeAccumulator = 0.0f;
	m_bombs.clear();
	m_bonuses.clear();
	m_explosions.clear();
	m_guards.clear();
	m_rocks.clear();
	m_hiddenBonusMap.clear();
	m_timeLimitClock->restart();
	m_moveAndDrawClock->restart();
	m_pauseTimes.clear();
}

// reset robot position and some stuff that need to be reset if the robot died from a bomb or a guard
void GameController::resetOnDeath()
{
	partReset();
	m_robot->resetPosition();
	for (auto& guard : m_guards)
		guard->resetPosition();
	int i = 0;
	Robot &robot = *m_robot;
	std::experimental::erase_if(m_bombs, [&robot](const auto& bomb) {
		return bomb->inAreaOfEffect(robot.getPosition());
	});
	std::experimental::erase_if(m_explosions, [&robot](const auto& explosion) {
		return explosion->inAreaOfEffect(robot.getPosition());
	});
}

// reset this on any case one of the two big reset actions is performed
void GameController::partReset()
{
	//reset the bg image color 
	m_bgRect->setFillColor(sf::Color(255, 255, 255, 255));
	unPause();
	m_alarmData.m_changeToAlarmColor = true;
	m_alarmData.m_playAlarm = false;
	m_alarmData.m_setTimeAlarm = true;
}

// convert sizes in number of rows and columns into actuall sizes in sfml coordinate system.
sf::Vector2f GameController::gameCoordsToSFCoords(const sf::Vector2i & rowCol) const
{
	return gameCoordsToSFCoordsRelToBoard(rowCol) + m_board->getTopLeftCornerPosition();
}

// convert row and col to sf coordinate system relative to the top left corner of the board
sf::Vector2f GameController::gameCoordsToSFCoordsRelToBoard(const sf::Vector2i & rowCol) const
{
	return m_gameWindow.mapPixelToCoords(sf::Vector2i(
		COL_WIDTH * rowCol.x,
		ROW_WIDTH * rowCol.y
	));
}

// convert row and col to sf coordinate system and return the position of the center of the board cell
sf::Vector2f GameController::gameCoordsToSFCoordsCentered(const sf::Vector2i & rowCol) const
{
	return gameCoordsToSFCoords(rowCol) + sf::Vector2f(COL_WIDTH / 2.0f, ROW_WIDTH / 2.0f);
}

// convert sfml position into a row and col on the board
sf::Vector2i GameController::sfCoordsToGameCoords(sf::Vector2f pix) const
{
	pix -= m_board->getTopLeftCornerPosition();
	return {
		(int)(pix.x / COL_WIDTH),
		(int)(pix.y / ROW_WIDTH)
	};
}

// provides access to the mapCoordsToPix function of sf::RenderWindow
sf::Vector2i GameController::mapCoordsToPix(const sf::Vector2f & coords)
{
	return m_gameWindow.mapCoordsToPixel(coords);
}

// load the level from file
void GameController::loadLevelFile()
{
	std::ifstream levelFile;
	levelFile.open("level/" + *m_levelFileName);

	std::string line;
	//sf::Vector2i boardSize;
	int bombQuantity;
	float timeLimit;
	// read first line from level file: rows, columns, time limit and number of bombs at the robot's disposal
	levelFile >> m_boardSize.y >> m_boardSize.x >> timeLimit >> bombQuantity;
	std::getline(levelFile, line);

	initGameSettings(timeLimit, bombQuantity);

	for (int row = 0; row < m_boardSize.y; ++row) {
		// read a line from the file, represents a row on the game board with rocks and players on it
		std::getline(levelFile, line);
		// search for non-empty cells in the row
		processLine(line, row);
	}
	levelFile.close();
}

// process a dingle line from the file
void GameController::processLine(std::string &line, int row)
{
	for (size_t col = 0; col < line.length(); ++col)
		if (line[col] != CHAR_EMPTY) {
			// if line[col] is not empty than there is a board item at (col, row) on the game board
			// compute the position in pixels by multiplying rol and row by col and row width in pixels
			// and add board position to the result.
			sf::Vector2f position = gameCoordsToSFCoordsCentered({ (int)col, row });
			unsigned guardLotto;
			switch (line[col])
			{
			case CHAR_ROBOT:
				m_robot->setInitialPosition(position);
				break;
			case CHAR_DOOR:
				m_board->addDoor(position);
				break;
			case CHAR_WALL:
				m_board->addWall(position);
				break;
			case CHAR_ROCK:
				m_rocks.push_back(std::make_unique<Rock>(position));
				break;
			case CHAR_SIMPLE_GUARD:
				m_guards.push_back(std::make_unique<SimpleGuard>(position, *m_board));
				break;
			case CHAR_CLEVER_GUARD:
				m_guards.push_back(std::make_unique<CleverGuard>(position, *m_board, m_graph));
				break;
			case CHAR_GUARD:
				guardLotto = rand() % 2;
				if (guardLotto == GUARD_LOTTO_CLEVER)
					m_guards.push_back(std::make_unique<CleverGuard>(position, *m_board, m_graph));
				else
					m_guards.push_back(std::make_unique<SimpleGuard>(position, *m_board));
				break;
			case CHAR_BONUS:
				addBonusAt(position, true);
				break;
			case CHAR_HIDDEN_BONUS:
				m_rocks.push_back(std::make_unique<Rock>(position));
				m_hiddenBonusMap[convertCoordsToBoardCellIndex(sfCoordsToGameCoords(position))] = true;
			}
		}
}

void GameController::initGameSettings(float timeLimit, int bombQuantity)
{
	// set time limit in milliseconds
	if (timeLimit > UNLIMITED_TIME)
		m_timeLimitMilliseconds = (int)(timeLimit * SECOND);
	else
		m_timeLimitMilliseconds = UNLIMITED_TIME;

	// set size of hidden bonus map
	resetHiddenBonusMap();

	// set robot's bomb quantity
	m_robot->setBombQuantity(bombQuantity);

	// get size of board in pixels and set m_board to it
	sf::Vector2f boardSizePix = gameCoordsToSFCoordsRelToBoard(m_boardSize);
	m_board->setBoardSize(m_boardSize, boardSizePix);

	sf::Vector2u windowSize = m_gameWindow.getSize();

	// place control bar relative to the window center, right out of the board
	sf::Vector2f cbPosition(windowSize.x / 2.0f - boardSizePix.x / 2.0f
		- GAME_CONTROL_BAR_WIDTH - GAME_CONTROL_BAR_GAP,
		windowSize.y / 2.0f - boardSizePix.y / 2.0f);
	m_controlBarController->setPosition(cbPosition);
}

void GameController::resetHiddenBonusMap()
{
	unsigned cellNum = m_boardSize.x * m_boardSize.y;
	for (unsigned i = 0; i < cellNum; ++i)
		m_hiddenBonusMap.push_back(false);
}

// draw the game
void GameController::draw(float deltaTime)
{
	m_gameWindow.clear();

	setAlarmColors();

	m_gameWindow.draw(*m_bgRect);

	drawControlBar();
	m_board->draw(deltaTime);

	for (auto& bonus : m_bonuses)
		bonus->draw(deltaTime, m_gameWindow);

	for (auto& rock : m_rocks)
		rock->draw(deltaTime, m_gameWindow);

	drawBombs(deltaTime);

	drawExplosions(deltaTime);

	m_robot->draw(deltaTime, m_gameWindow);

	for (auto& guard : m_guards)
		guard->draw(deltaTime, m_gameWindow);

	checkIfRobotColidesWithGuards();
	checkIfRobotIsAtTheDoor();
	checkIfRobotIsOnBonus();

	drawMessageBox(deltaTime);

	m_gameWindow.display();
}

void GameController::drawExplosions(float deltaTime)
{
	while (!m_pause && !m_explosions.empty() && m_explosions.front()->didTimeOut())
		m_explosions.erase(m_explosions.begin());
	for (auto& explosion : m_explosions)
		explosion->draw(deltaTime, m_gameWindow);
}

void GameController::drawBombs(float deltaTime)
{
	if (!m_pause)
		explodeBombs();
	for (auto& bomb : m_bombs)
		bomb->draw(deltaTime, m_gameWindow);
}

void GameController::drawControlBar()
{
	int timeLeft = computeTimeLeftMilliseconds();
	if (timeLeft < ALARM_TIME_LEFT && timeLeft > UNLIMITED_TIME && !m_alarmData.m_playAlarm)
		playAlaram();
	m_controlBarController->draw(m_gameWindow, timeLeft, m_currentLevelIndex);
}

int GameController::computeTimeLeftMilliseconds()
{
	int timeLeft;
	if (m_timeLimitMilliseconds > UNLIMITED_TIME) {
		// compute total time limit minus the time passed
		timeLeft = m_timeLimitMilliseconds - m_timeLimitClock->getElapsedTime().asMilliseconds();

		// add to result all the pause times
		for (auto& pauseTime : m_pauseTimes)
			if (pauseTime.y)
				timeLeft += pauseTime.y - pauseTime.x;
			else
				timeLeft += m_timeLimitClock->getElapsedTime().asMilliseconds() - pauseTime.x;
	}
	else
		timeLeft = UNLIMITED_TIME;
	return timeLeft;
}

void GameController::drawMessageBox(float deltaTime)
{
	if (m_messageBox->shouldDisplay()) {
		m_messageBox->draw();
		m_messageBoxTimeAccumulator += deltaTime;
		if (m_messageBox->getMessageType() == victory_msg &&
			m_messageBoxTimeAccumulator >= MESSAGE_TIME) {
			m_messageBoxTimeAccumulator = 0.0f;
			m_didWin = true;
		}
		else if (m_messageBox->getMessageType() == game_over_msg &&
			m_messageBoxTimeAccumulator >= MESSAGE_TIME) {
			m_messageBoxTimeAccumulator = 0.0f;
			m_gameOver = true;
		}
	}
}

void GameController::checkIfRobotColidesWithGuards()
{
	for (auto& guard : m_guards)
		if (m_robot->isColidingWith(*guard)) {
			robotDies();
			break;
		}
}

void GameController::checkIfRobotIsAtTheDoor()
{
	if (m_board->isAtTheDoor(*m_robot))
		robotWins();
}

void GameController::checkIfRobotIsOnBonus()
{
	for (size_t i = 0; i < m_bonuses.size();) // since we might erase from the vector, we can't always increase i
		if (m_bonuses[i]->getGlobalBounds().contains(m_robot->getPosition())) {
			m_bonuses[i]->affectRobot(*m_robot);
			m_bonuses.erase(m_bonuses.begin() + i);
		}
		else // if we did not erase, we increase i
			++i;
}

// converts row and column into an index for an array with as many entries as the cells in the board.
unsigned GameController::convertCoordsToBoardCellIndex(const sf::Vector2i & position)
{
	return (position.y * m_boardSize.x) + position.x;
}

// stuff to do when the robot wins.
void GameController::robotWins()
{
	pause();
	if (!m_messageBox->shouldDisplay())
		m_robot->increaseScoreBy(PASSED_DOOR_SCORE_FACTOR * m_numOfInitGuards);
	m_messageBox->display(VICTORY_MESSAGE, victory_msg);
}

void GameController::explodeBombs()
{
	while (!m_bombs.empty() && m_bombs.front()->didTimeOut()) {
		m_explosions.push_back(std::make_unique<Explosion>(m_bombs.front()->getPosition()));
		if (explodeItems(m_explosions.back()))
			break;
		m_bombs.erase(m_bombs.begin());
	}
}

bool GameController::explodeItems(std::unique_ptr<Explosion> & explosion)
{
	explodeRocks(explosion);
	explodeGuards(explosion);
	if (explosion->intersects(*m_robot)) {
		robotDies();
		return true;
	}
	return false;
}

void GameController::explodeGuards(std::unique_ptr<Explosion> & explosion)
{
	for (size_t i = 0; i < m_guards.size();)
		if (explosion->intersects(*m_guards[i])) {
			m_robot->increaseScoreBy(KILL_GUARDS_SCORE_FACTOR * m_numOfInitGuards);
			m_guards.erase(m_guards.begin() + i);
		}
		else
			++i;
}

void GameController::explodeRocks(std::unique_ptr<Explosion> & explosion)
{
	for (size_t i = 0; i < m_rocks.size();)	// since we might erase from the vector we can't always increase i
		if (explosion->intersects(*m_rocks[i])) {
			sf::Vector2i coords = sfCoordsToGameCoords(m_rocks[i]->getPosition());
			unsigned indexOfRockPosition = convertCoordsToBoardCellIndex(coords);
			// add bonus where rock exploded. Use a 50% chance to add the bonus unless this
			// rock was specified in the file as a hidden bonus place
			addBonusAt(m_rocks[i]->getPosition(), m_hiddenBonusMap[indexOfRockPosition]);
			m_rocks.erase(m_rocks.begin() + i);
		}
		else // if we don't erase, we increase i
			++i;
}

void GameController::addBonusAt(const sf::Vector2f& position, bool noRandom)
{
	bool addedBonus = false;
	while (!addedBonus) {
		addedBonus = true;
		unsigned gambleBonus = rand() % (noRandom ? NUM_BUNUS_ITEMS : BONUS_LOTTO_MAX);
		switch (gambleBonus)
		{
		case SPEED_BONUS:
			m_bonuses.push_back(std::make_unique<SpeedBonus>(position));
			break;
		case COIN_BONUS:
			m_bonuses.push_back(std::make_unique<CoinBonus>(position));
			break;
		case BOMB_BONUS:
			if (m_robot->getBombQuantity() != UNLIMITED_BOMBS)
				m_bonuses.push_back(std::make_unique<BombBonus>(position));
			break;
		case LIFE_BONUS:
			m_bonuses.push_back(std::make_unique<LifeBonus>(position));
			break;
		}
	}
}

// stuff to do when robot dies
void GameController::robotDies()
{
	// robot looses one life. if no life are left die() returns false and game over message is displayed.
	if (!m_robot->die()) {
		pause();
		m_messageBox->display(GAME_OVER_MESSAGE, game_over_msg);
		m_robot->resetScore();
	}
	else {
		m_bgGameSound->pause();
		m_robot->stopSound();

		if (m_timeLimitMilliseconds != UNLIMITED_TIME &&
			computeTimeLeftMilliseconds() <= 0) {
			int lives = m_robot->getLives();
			fullResetMembers();
			loadLevelFile();
			m_robot->setLives(lives);
		}
		else
			resetOnDeath();
	}
}

void GameController::handleEvents()
{
	sf::Event event;
	while (m_gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_gameWindow.close();
			break;
		case sf::Event::KeyReleased:
			if (!m_messageBox->shouldDisplay())
				handleKeyReleasedEvent(event.key.code);
			else if (m_messageBox->getMessageType() == game_over_msg)
				m_gameOver = true;
			break;
		}
	}
}

// things that happen once and are not continuose should happen on key release.
// like closing the game window or stopping to move
void GameController::handleKeyReleasedEvent(sf::Keyboard::Key keyCode) {
	switch (keyCode)
	{
	case sf::Keyboard::Escape:
		m_gameOver = true;
		break;
	case sf::Keyboard::B:
		if (!m_pause && m_robot->useBomb())
			m_bombs.push_back(std::make_unique<Bomb>(m_robot->getPosition()));
		break;
	case sf::Keyboard::P:
		if (!m_pause)
			pause();
		else
			unPause();
		break;
	case sf::Keyboard::Q:
		robotDies();
		break;
	}
}

// pause the game
void GameController::pause()
{
	// save the time when pause was started
	m_pauseTimes.push_back({ m_timeLimitClock->getElapsedTime().asMilliseconds(), 0 });
	for (auto& bomb : m_bombs)
		bomb->pause();
	for (auto &bonus : m_bonuses)
		bonus->pause();
	for (auto & guard : m_guards)
		guard->pause();
	for (auto & explosion : m_explosions)
		explosion->pause();
	m_robot->pause();
	m_robot->pauseSound();
	m_pause = true;
	m_bgGameSound->pause();
	m_alarmSound->pause();
}

// un-pause the game
void GameController::unPause()
{
	for (auto & explosion : m_explosions)
		explosion->play();
	for (auto& bomb : m_bombs)
		bomb->play();
	for (auto& bonus : m_bonuses)
		bonus->unPause();
	for (auto & guard : m_guards)
		guard->unPause();
	m_robot->unPause();
	m_pause = false;
	m_bgGameSound->play();
	if(m_alarmData.m_playAlarm)
		m_alarmSound->play();

	// if there is a started pause, save the time it ended
	if (!m_pauseTimes.empty() && !m_pauseTimes.back().y)
		m_pauseTimes.back().y = m_timeLimitClock->getElapsedTime().asMilliseconds();
}

void GameController::movePlayers(float deltaTime)
{
	m_robot->move(deltaTime);
	for (auto& guard : m_guards)
		guard->move(deltaTime);
}

void GameController::playAlaram()
{
	m_bgGameSound->pause();
	m_alarmSound->play();
	m_alarmData.m_playAlarm = true;
}

// this function handles the visual alarm: it changes the color of the screen every second or so from
// redish to blackish
void GameController::setAlarmColors()
{
	int timeLeft = computeTimeLeftMilliseconds();

	if (timeLeft < ALARM_TIME_LEFT && timeLeft > UNLIMITED_TIME &&!m_pause)
	{
		if (m_alarmData.m_setTimeAlarm) {
			m_alarmData.m_alarmStartTime = timeLeft;
			m_alarmData.m_setTimeAlarm = false;
		}
		if (m_alarmData.m_alarmStartTime - timeLeft > SECOND) {
			m_alarmData.m_alarmStartTime = timeLeft;
		}
		if (timeLeft == m_alarmData.m_alarmStartTime)
		{
			if (m_alarmData.m_changeToAlarmColor) {
				m_bgRect->setFillColor(sf::Color::Red);
				m_alarmData.m_changeToAlarmColor = false;
			}
			else {
				m_bgRect->setFillColor(sf::Color(255, 255, 255, 80));
				m_alarmData.m_changeToAlarmColor = true;
			}
		}
	}
}
