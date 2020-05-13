#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Guard.h"
#include "Graph.h"

class Graph;

class CleverGuard :
	public Guard
{
public:
	// clever guar c-tor. requires a board to check for collisions and a graph to find the way to the robot
	CleverGuard(const sf::Vector2f& position, const Board& board, std::unique_ptr<Graph>& graph);
	// attempts to move on the board (change internal position to a legitimate new one)
	virtual void move(float delta) override;
private:
	// a reference to the graph that the gamecontroller is using to perform BFS on the board
	// to find the shortests paths from the robot to every place on the board. clever guard will
	// ask the graph where to go every time it moves.
	std::unique_ptr<Graph> & m_graph;
	// the last direction in which this clever guard moved. used to determine the next move.
	move_t m_direction = no_mov;
};

