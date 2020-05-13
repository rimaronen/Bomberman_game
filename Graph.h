#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BoardItem.h"
#include "Rock.h"
#include "types.h"

const float HALF_PLAYER_SIZE = 12.0f;

const int LEFT_NEIGHBOR = 0;
const int UP_NEIGHBOR = 1;
const int RIGHT_NEIGHBOR = 2;
const int DOWN_NEIGHBOR = 3;
const int MAX_NEIGHBORS = 4;

class GameController;

struct GraphData {
	// init the members in the strtuct, -1 as infinity
	GraphData() : visited(false), isNode(true), distance(-1), predecessor({ -1, -1 }) {}
	bool visited;
	bool isNode;
	int distance;
	sf::Vector2i predecessor;
	int neighbors[4] = { -1, -1, -1, -1 }; // for left, right, up and down neighbors
};

class Graph
{
public:
	Graph(GameController &gamecontroller);
	// change
	void initData(std::vector<std::unique_ptr<Rock>> &rocks, const std::vector<std::unique_ptr<BoardItem>> &staticItems,
		int numOfRows, int numOfCols);
	~Graph();
	// BFS algorithm on the nodes on the board
	void BFS(sf::Vector2i startNode);
	// get guards next move on the board by their predeccesor
	move_t getNextMove(const sf::Vector2f &currentPosition, move_t prevMov);
	// if the guard is at the center of the rectanle shape
	bool isContained(const sf::Vector2f & center, const sf::Vector2f & current, move_t prevMov);
	// move the guard to its center
	move_t moveToCenter(const sf::Vector2f & center, const sf::Vector2f & current);
private:
	// set for each node its neighbors
	void setNeighbors();
	// move on the nodes in the array and add for each node its neighbors
	void initNodes(std::vector<std::unique_ptr<Rock>> &rocks, const std::vector<std::unique_ptr<BoardItem>> &staticItems);
	void addNeighbors(int node, const sf::Vector2i &position);
	// convert node on the graph to its coords position
	sf::Vector2i convertNodeToCoords(int node);

	GameController &m_gameController;
	GraphData *m_graph = nullptr;

	// indexes for the graph points
	int m_numOfRows;
	int m_numOfCols;


};

