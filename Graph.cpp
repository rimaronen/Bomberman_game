//#include <list>
#include <queue>
#include "Graph.h"
#include "consts.h"
#include "GameController.h"
#include "wintools.h"

/*Graph constructor*/
Graph::Graph(GameController & gamecontroller)
	:m_gameController(gamecontroller)
{
}

/*this function inittializes all the data for builfing the graph of the empty paths on the board*/
void Graph::initData(std::vector<std::unique_ptr<Rock>>& rocks, const std::vector<std::unique_ptr<BoardItem>>& staticItems,
	int numOfRows, int numOfCols)
{
	m_numOfCols = numOfCols;
	m_numOfRows = numOfRows;
	// holds one line of all the nodes that will be kept as neighbors
	m_graph = new GraphData[m_numOfRows * m_numOfCols];

	if (!m_graph) // if alloc is failed
		exit(EXIT_FAILURE);

	initNodes(rocks, staticItems);
}

/*this function initializes all the nodes in the graph. if the position contains rock or other static
item, then they are not nodes in our graph*/
void Graph::initNodes(std::vector<std::unique_ptr<Rock>> &rocks, const std::vector<std::unique_ptr<BoardItem>> &staticItems)
{
	sf::Vector2f positionInPixels;
	sf::Vector2i positionInCoords;
	int node;

	for (size_t i = 0; i < rocks.size(); ++i) {
		positionInPixels = rocks[i]->getPosition(); // set position for rocks position 
		positionInCoords = m_gameController.sfCoordsToGameCoords(positionInPixels); // convert position to vector2u
		node = m_gameController.convertCoordsToBoardCellIndex(positionInCoords); // convert vector2u to a node position on the array
		m_graph[node].isNode = false;
	}

	for (size_t i = 0; i < staticItems.size(); ++i) {
		positionInPixels = staticItems[i]->getPosition(); // set position for static items
		positionInCoords = m_gameController.sfCoordsToGameCoords(positionInPixels); // convert position to vector2u
		node = m_gameController.convertCoordsToBoardCellIndex(positionInCoords); // convert vector2u to a node position on the array
		m_graph[node].isNode = false;
	}

	setNeighbors();
}

/*this function sets position on the board from a given node*/
sf::Vector2i Graph::convertNodeToCoords(int node)
{
	int xPos = node % m_numOfCols;
	int yPos = node / m_numOfCols;
	return { xPos, yPos };
}

/*this function sets the neighbors to all the nodes in the graph by calling addNeighbors function to add all four
neighbors around the node if exists*/
void Graph::setNeighbors()
{
	// run on the array the neighbors of the nodes if exists
	for (int i = 0; i < (m_numOfRows*m_numOfCols); ++i)
		if (m_graph[i].isNode) // if is a node
			addNeighbors(i, convertNodeToCoords(i)); // sent the nonde and its position to add neighbors
}

/*this function acceptes the node index and its position on the board, set its neighbors*/
void Graph::addNeighbors(int node, const sf::Vector2i & position)
{
	int neighbor;

	if (position.y - 1 >= 0) { // if not out of range on the left
		neighbor = m_gameController.convertCoordsToBoardCellIndex({ position.x , position.y - 1 });
		if (m_graph[neighbor].isNode) // if the left neighbor exists
			m_graph[node].neighbors[UP_NEIGHBOR] = neighbor;
	}
	if (position.y + 1 < m_numOfRows) {//  if not out of range on the right
		neighbor = m_gameController.convertCoordsToBoardCellIndex({ position.x, position.y + 1 });
		if (m_graph[neighbor].isNode) // if right neighbor exists
			m_graph[node].neighbors[DOWN_NEIGHBOR] = neighbor;
	}
	if (position.x - 1 >= 0) {//  if not out of range on the top
		neighbor = m_gameController.convertCoordsToBoardCellIndex({ position.x - 1,  position.y });
		if (m_graph[neighbor].isNode) // if right neighbor exists
			m_graph[node].neighbors[LEFT_NEIGHBOR] = neighbor;
	}
	if (position.x + 1 < m_numOfCols) {//  if not out of range on the button
		neighbor = m_gameController.convertCoordsToBoardCellIndex({ position.x + 1, position.y });
		if (m_graph[neighbor].isNode) // if button neighbor exists
			m_graph[node].neighbors[RIGHT_NEIGHBOR] = neighbor;
	}
}


/*delete the allocated array*/
Graph::~Graph()
{
	delete[]m_graph;
}

/*this function runs BFS algotithm from the robots position to all the nodes in the graph - the unblocked
paths in the board, and sets the shortest path to each guard to the robot*/
void Graph::BFS(sf::Vector2i startNode)
{
	std::queue<int> queue; // for the queue used in the algorithm

	int node = m_gameController.convertCoordsToBoardCellIndex(startNode);
	m_graph[node].visited = true;

	queue.push(node); // enter start node first to the queue
	m_graph[node].distance = 0;

	while (!queue.empty()) { // as long as nodes not checked for their neighbors

		int firstNode = queue.front(); // handle the first node in the queue.
		queue.pop(); // remove the first node from the queue 

		for (int i = 0; i < MAX_NEIGHBORS; ++i)
			// if neighbor exist and first visited the node
			if (m_graph[firstNode].neighbors[i] != -1 && !m_graph[m_graph[firstNode].neighbors[i]].visited) {
				m_graph[m_graph[firstNode].neighbors[i]].visited = true; // mark node as visited node
				// place coordinates in the predecessor node
				m_graph[m_graph[firstNode].neighbors[i]].predecessor = (convertNodeToCoords(firstNode));
				m_graph[m_graph[firstNode].neighbors[i]].distance = m_graph[firstNode].distance + 1; // set discovered node distance
				queue.push(m_graph[firstNode].neighbors[i]);
			}
	}
}

//*this function returns the next position for the guard on the shortest path to the robot*/
move_t Graph::getNextMove(const sf::Vector2f & currentPosition, move_t prevMov)
{
	sf::Vector2i currentCoordsPos = m_gameController.sfCoordsToGameCoords(currentPosition); // convert position to coords
	sf::Vector2f center = m_gameController.gameCoordsToSFCoordsCentered(currentCoordsPos);
	if (!isContained(center, currentPosition, prevMov))
		return moveToCenter(center, currentPosition);
	int node = m_gameController.convertCoordsToBoardCellIndex(currentCoordsPos); // convert to a node on the graph
	sf::Vector2i predeccesorCoords = m_graph[node].predecessor;

	// check move by comparing coords
	if (currentCoordsPos.x == predeccesorCoords.x)
		if (currentCoordsPos.y > predeccesorCoords.y) {
			//OutputDebugStringA("robot up from guard\n");
			return up_mov;
		}
		else {
			//OutputDebugStringA("robot down from guard\n");
			return down_mov;
		}
	else if (currentCoordsPos.y == predeccesorCoords.y)
		if (currentCoordsPos.x > predeccesorCoords.x) {
			//OutputDebugStringA("robot right from guard\n");
			return left_mov;
		}
		else {
			//OutputDebugStringA("robot left from guard\n");
			return right_mov;
		}
	return no_mov;
}

/*tells if 'current' position passed 'center' position moving in 'prevMov' direction*/
bool Graph::isContained(const sf::Vector2f& center, const sf::Vector2f& current, move_t prevMov)
{
	switch (prevMov)
	{
	case up_mov:
		return current.y < center.y || abs(center.y - current.y) < HALF_PLAYER_SIZE;
	case down_mov:
		return current.y > center.y || abs(center.y - current.y) < HALF_PLAYER_SIZE;
	case right_mov:
		return current.x > center.x || abs(center.x - current.x) < HALF_PLAYER_SIZE;
	case left_mov:
		return current.x < center.x || abs(center.x - current.x) < HALF_PLAYER_SIZE;
	default:
		// if not moving, not after
		return true;
	}
}

/*this function moves the guard to it's center by the center coodinates and it's current position cooridantes*/
move_t Graph::moveToCenter(const sf::Vector2f & center, const sf::Vector2f & current)
{
	float verticalFactor = center.y - current.y;
	float horizontalFactor = center.x - current.x;
	if (abs(verticalFactor) > abs(horizontalFactor))
		if (verticalFactor < 0)	// current below center
			return up_mov;
		else
			return down_mov;
	else
		if (horizontalFactor < 0)
			return left_mov;
		else
			return right_mov;
}

