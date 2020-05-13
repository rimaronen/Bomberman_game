#include "Board.h"
#include "consts.h"
#include "Player.h"
#include "Rock.h"
#include "GameController.h"
#include "wintools.h"

// c-tor
Board::Board(sf::RenderWindow& window, std::vector<std::unique_ptr<Rock>>& rocks)
	:WindowManager(window), m_rocks(rocks)
{
	// load bg image
	if (!m_bgTexture->loadFromFile(BOARD_BG_FILE))
		exit(EXIT_FAILURE);

	// bg image is drawn on repeat - it is expected to be a tilable texture
	m_bgSprite->setTexture(*m_bgTexture);
}

// draw this board
void Board::draw(float deltaTime)
{
	// draw board's background if ready (if board size was set)
	if (m_drawBG)
		getWindow().draw(*m_bgSprite);

	for (auto& item : m_staticItems)
		item->draw(deltaTime, getWindow());
}

// initialize board to this size
// rowColNums: number of rows and columns the board is logically divided to (these numbers are input from the file)
// boardSizeSFCoords: rowColNums translated to sfml coordinate system (similar to pixels).
void Board::setBoardSize(const sf::Vector2i & rowColNums, const sf::Vector2f & boardSizeSFCoords)
{
	m_rowColNums = rowColNums;
	m_boardSizeSFCoords = boardSizeSFCoords;

	m_bgSprite->setOrigin({ m_boardSizeSFCoords.x / 2.0f, m_boardSizeSFCoords.y / 2.0f });

	// place m_bgSprite in the middle of the window
	sf::Vector2u windowSize = getWindow().getSize();
	m_bgSprite->setPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f });

	// make m_bgSprite span the entire size of the board
	m_bgSprite->setTextureRect(sf::IntRect(0, 0, (int)m_boardSizeSFCoords.x, (int)m_boardSizeSFCoords.y));

	// mark bg ready to be drawn
	m_drawBG = true;
}

// get the board size in sfml coordinates system
const sf::Vector2f & Board::getBoardSizeSFCoords() const
{
	return m_boardSizeSFCoords;
}

void Board::addWall(sf::Vector2f& wallPos)
{
	m_staticItems.push_back(std::move(std::make_unique<Wall>(wallPos)));
}

void Board::addDoor(sf::Vector2f& doorPos)
{
	m_staticItems.insert(m_staticItems.begin(), std::move(std::make_unique<Door>(doorPos)));
}

// check if a character at this position is in the board of not.
bool Board::isPlayerInBoard(const Player& player) const
{
	// the character at this position spans half column width to both sides
	// of this position and half row width above and below this position.
	sf::Vector2u windowSize = getWindowSize();

	// using epsilon to compare two numbers: since float arithmetics are inaccurate
	// we use an epsilon to get definite results. if the difference of two numbers is
	// larger then epsilon, the left number is considered bigger than the right one.
	float epsilon = 0.5;

	sf::FloatRect playerBoundingRect = player.getGlobalBounds();

	float characterLeftBorder = playerBoundingRect.left;
	float boardLeftBorder = windowSize.x / 2.0f - m_boardSizeSFCoords.x / 2.0f;
	float characterTopBorder = playerBoundingRect.top;
	float boardTopBorder = windowSize.y / 2.0f - m_boardSizeSFCoords.y / 2.0f;

	// if boardLeftBorder is bigger than characterLeftBorder up to epsilon
	if (boardLeftBorder - characterLeftBorder > epsilon  ||
		boardTopBorder - characterTopBorder > epsilon)
		return false;
	
	float characterRightBorder = playerBoundingRect.left + playerBoundingRect.width;
	float boardRightBorder = windowSize.x / 2.0f + m_boardSizeSFCoords.x / 2.0f;
	float characterBottomBorder = playerBoundingRect.top + playerBoundingRect.height;
	float boardBottomBorder = windowSize.y / 2.0f + m_boardSizeSFCoords.y / 2.0f;
	
	// if characterLeftBorder is bigger than boardLeftBorder up to epsilon
	if (characterRightBorder - boardRightBorder > epsilon ||
		characterBottomBorder - boardBottomBorder > epsilon)
		return false;

	// if not returned false return true. this means that if the float representing the
	// position on the window is out of the board by up to epsilon, we will consider it
	// in the board.
	return true;
}

// check if the player clashes with any of the objects on the board
bool Board::isPlayerColiding(const Player & player) const
{
	for (size_t i = 1; i < m_staticItems.size(); ++i)
		if (player.isColidingWith(*m_staticItems[i]))
			return true;
	for (auto& rock : m_rocks)
		if (player.isColidingWith(*rock))
			return true;

	return false;
}

// tells if this player is at the door
bool Board::isAtTheDoor(const Player & player)
{
	return m_staticItems[0]->getGlobalBounds().contains(player.getPosition());
}

const std::vector<std::unique_ptr<BoardItem>>& Board::getStaticItems()
{
	return this->m_staticItems;
}

// resets members between levels or after timeouts
void Board::resetMembers()
{
	m_drawBG = false;
	m_rocks.clear();
	m_staticItems.clear();
}

sf::Vector2f Board::getTopLeftCornerPosition() const
{
	return m_bgSprite->getPosition() - m_bgSprite->getOrigin();
}
