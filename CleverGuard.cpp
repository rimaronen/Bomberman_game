#include "CleverGuard.h"
#include "GameResources.h"

// c-tor
CleverGuard::CleverGuard(const sf::Vector2f & position, const Board & board, std::unique_ptr<Graph>& graph)
	:Guard(GameResources::instance().getCleverGuardTexture(), position, board), m_graph(graph)
{
}

// move this guard on the board
void CleverGuard::move(float delta)
{
	PlayerAnimation *pa = dynamic_cast<PlayerAnimation *>(getAnimation());

	if (!pa)
		exit(EXIT_FAILURE);

	// get direction sugestion from graph for the next move
	move_t tempDir = m_graph->getNextMove(getPosition(), m_direction);
	if (tempDir != no_mov) // no_mov means don't change your current direction
		m_direction = tempDir;

	sf::Vector2f offset;

	// tell animation the direction and compute the offset by which to move from current position
	switch (m_direction)
	{
	case up_mov:
		pa->up();
		offset = { 0, -getSpeed().y * delta };
		break;
	case down_mov:
		pa->down();
		offset = { 0, getSpeed().y * delta };
		break;
	case left_mov:
		pa->left();
		offset = { -getSpeed().x * delta, 0 };
		break;
	case right_mov:
		pa->right();
		offset = { getSpeed().x * delta, 0 };
	}

	// try to move
	attemptMove(pa, offset);
}
