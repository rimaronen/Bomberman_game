#pragma once
#include "RemovableItem.h"
#include "types.h"
#include "PlayerAnimation.h"

// number of frames in a row in a player's texture
const unsigned PLAYER_IMAGE_COUNT_X = 3;
// number of rows of frames in a player's texture
const unsigned PLAYER_IMAGE_COUNT_Y = 4;
// time between frame switching
const float PLAYER_SWITCH_TIME = 0.2f;

class Board;
class Texture;

class Player :
	public RemovableItem
{
public:
	// c-tor. players need a reference to the game board for colision detection against walls and rocks.
	Player(sf::Texture & texture, const Board & board);
	Player(sf::Texture & texture, const sf::Vector2f & position, const Board & board);
	// moves the player on the baord
	virtual void move(float delta) = 0;
	bool isColidingWith(BoardItem& boardItem) const;
	virtual void pause();
	virtual void unPause();
	void setInitialPosition(const sf::Vector2f& initialPosition);
	void resetPosition();
	
protected:
	// attempt to move, if coliding or out of the board move back.
	bool attemptMove(PlayerAnimation * animation, const sf::Vector2f& offset);
	// accessors for private membres for inheriting classes
	const sf::Vector2f& getSpeed();
	void setSpeed(const sf::Vector2f& speed);
private:
	const Board& m_board;
	// player's movement speed
	sf::Vector2f m_speed;
	sf::Vector2f m_initialPosition;
		
};

