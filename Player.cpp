#include "Player.h"
#include "Sound.h"
#include "Board.h"
#include "wintools.h"

// c-tor
Player::Player(sf::Texture & texture, const Board & board)
	:RemovableItem(new PlayerAnimation(texture, sf::Vector2u(PLAYER_IMAGE_COUNT_X, PLAYER_IMAGE_COUNT_Y),
		PLAYER_SWITCH_TIME)),
	m_board(board)
{
}


// c-tor with position
Player::Player(sf::Texture & texture, const sf::Vector2f & position, const Board & board)
	:RemovableItem(new PlayerAnimation(texture, sf::Vector2u(PLAYER_IMAGE_COUNT_X, PLAYER_IMAGE_COUNT_Y),
		position, PLAYER_SWITCH_TIME)),
	m_board(board)
{
}

// tells if this player is coliding with this board item
bool Player::isColidingWith(BoardItem & boardItem) const
{
	return getGlobalBounds().intersects(boardItem.getGlobalBounds());
}

void Player::pause()
{
	getAnimation()->pause();
}
void Player::unPause()
{
	getAnimation()->unPause();
}

// attempts to move by offset from current position
bool Player::attemptMove(PlayerAnimation * animation, const sf::Vector2f& offset)
{
	// if the position to move to is in the board, move into it
	animation->move(offset);
	// else move back to previous position
	if (!m_board.isPlayerInBoard(*this) || m_board.isPlayerColiding(*this)) {
		animation->move(-offset);
		return false;
	}
	return true;
}

// return to the initial position (the one extracted from the level file)
void Player::resetPosition()
{
	setPosition(m_initialPosition);
}

const sf::Vector2f & Player::getSpeed()
{
	return m_speed;
}

void Player::setSpeed(const sf::Vector2f & speed)
{
	m_speed = speed;
}

// set the initial position member and move this player to it's initial position
void Player::setInitialPosition(const sf::Vector2f & initialPosition)
{
	m_initialPosition = initialPosition;
	resetPosition();
}
