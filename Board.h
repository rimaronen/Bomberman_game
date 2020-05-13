#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Wall.h"
#include "Door.h"
#include "types.h"

const std::string BOARD_BG_FILE = "img/bgtexture3.png";

class Player;
class Rock;
class GameController;

class Board :
	public WindowManager
{
public:
	// requires the texture for the door and the window on which to display the game
	Board(sf::RenderWindow& window, std::vector<std::unique_ptr<Rock>>& rocks);
	// draws all the objects of the board on m_window
	void draw(float deltaTime);
	// sets the board size and adapts internal objects like m_bgTexture and m_bgSprite
	void setBoardSize(const sf::Vector2i& boardSizeCoords, const sf::Vector2f& boardSizePix);
	// returns the board size in sfml coordinates
	const sf::Vector2f& getBoardSizeSFCoords() const;
	// adds a wall to the static items vector
	void addWall(sf::Vector2f& wallPos);
	// add a door to the static items vector
	void addDoor(sf::Vector2f& doorPos);
	// checks if this player (human or computerized) is inside the board.
	bool isPlayerInBoard(const Player& player) const;
	// checks if this player (human or computerised) is coliding with a wall.
	bool isPlayerColiding(const Player& player) const;
	// checks if the robot is at the door
	bool isAtTheDoor(const Player& player);
	// returns a const ref to the static items vector
	const std::vector<std::unique_ptr<BoardItem>> & getStaticItems();
	// resets the state of this board for a new level to be loaded
	void resetMembers();
	// returns the top left position of this board
	sf::Vector2f getTopLeftCornerPosition() const;

private:
	// board background texture. will display on repeat
	std::unique_ptr<sf::Texture> m_bgTexture = std::make_unique<sf::Texture>();
	// board background sprite
	std::unique_ptr<sf::Sprite> m_bgSprite = std::make_unique<sf::Sprite>();
	// this is set to false untile the board is ready to be drawn after board size was set for the first time
	bool m_drawBG = false;

	// vector of wa
	std::vector<std::unique_ptr<BoardItem>> m_staticItems;
	std::vector<std::unique_ptr<Rock>>& m_rocks;

	// number of rows and column in the game board (each level has a different number of rows and columns)
	sf::Vector2i m_rowColNums;
	// actual size of the board in pixels, in which the height is a multiple of the number of rows and
	// the width is a multiple of the number of columns.
	sf::Vector2f m_boardSizeSFCoords;
};

