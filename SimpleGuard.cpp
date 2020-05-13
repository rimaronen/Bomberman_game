#include "SimpleGuard.h"
#include "types.h"
#include "GameResources.h"
#include "Board.h"
#include "GameController.h"
#include "wintools.h"

// c-tor
SimpleGuard::SimpleGuard(const sf::Vector2f & position, const Board & board)
	:Guard(GameResources::instance().getSimpleGuardTexture(), position, board)
{
}

// move this guard on the board
void SimpleGuard::move(float delta)
{
	PlayerAnimation *pa = dynamic_cast<PlayerAnimation *>(getAnimation());
	if (!pa)
		exit(EXIT_FAILURE);

	// first: attempt to move by the current offset.
	bool moved = attemptMove(pa, m_offset);

	// if failed to move or if time of this direction is at 0 (when time is up it is being reset),
	// recalculate the direction and offset.
	if (!moved || m_timeAccumulator == 0) {
		m_direction = (move_t)(rand() % no_mov);
		for (int i = 0; i < no_mov; ++i) {
			m_direction = (move_t)((m_direction + 1) % no_mov);
			computeOffset(delta);
			if (attemptMove(pa, m_offset))
				break;
		}
	}
	// after successfull move recalculate the offset with the same direction.
	computeOffset(delta);

	// accumulate the time and reset it if it's time to switch direction
	m_timeAccumulator += delta;
	if (m_timeAccumulator >= SWITCH_DIRECTION_TIME)
		m_timeAccumulator = 0.0f;
}

// computes a new offset for the current direction
void SimpleGuard::computeOffset(float delta)
{
	PlayerAnimation *pa = dynamic_cast<PlayerAnimation *>(getAnimation());
	if (!pa)
		exit(EXIT_FAILURE);
	switch (m_direction)
	{
	case up_mov:
		pa->up();
		m_offset = { 0, -getSpeed().y * delta };
		break;
	case down_mov:
		pa->down();
		m_offset = { 0, getSpeed().y * delta };
		break;
	case right_mov:
		pa->right();
		m_offset = { getSpeed().x * delta, 0 };
		break;
	case left_mov:
		pa->left();
		m_offset = { -getSpeed().x * delta, 0 };
	}
}