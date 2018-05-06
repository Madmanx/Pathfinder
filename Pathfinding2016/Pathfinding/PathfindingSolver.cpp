///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 pathfindingSolver.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#include "PathfindingSolver.h"

namespace Pathfinding {

	// Public constructor : initiate an array of Node*
	PathfindingSolver::PathfindingSolver(const unsigned char * pMap, const int nMapWidth, const int nMapHeight) 
		: m_mapWidth(nMapWidth)
		, m_mapHeight(nMapHeight)
		, m_map(pMap)
	{
		m_nodesMap = (Node**)calloc(nMapWidth * nMapHeight, nMapWidth * nMapHeight * sizeof(Node*));
	}

	// Public destructor : clear an array of Node*
	PathfindingSolver::~PathfindingSolver()
	{
		if (m_nodesMap != NULL)
		{
			for (int i = 0; i < m_mapHeight*m_mapWidth; i++)
			{
				Node* node = m_nodesMap[i];
				if (node != NULL)
				{
					delete node;
				}

			}
			free(m_nodesMap);
		}
	}

	// Public method : Find the shortest path, return -1 if such a path doesn't exist
	int PathfindingSolver::solveWithAStarAlgorithm(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, int* pOutBuffer, const int nOutBufferSize) 
	{
		Coordinate startCoordinate(nStartX, nStartY);
		Coordinate targetCoordinate(nTargetX, nTargetY);

		// Start Node
		Node* currentNode = createNode(startCoordinate, targetCoordinate);

		// Initialise the priority queue with the first node
		std::priority_queue<Node*, std::vector<Node*>, Node::CompareNode> pqNodeToVisit;
		pqNodeToVisit.push(currentNode);
		currentNode->setCurrentState(Node::e_stateQueued);

		while (!pqNodeToVisit.empty()) {

			currentNode = pqNodeToVisit.top();
			currentNode->setCurrentState(Node::e_stateProcessed);

			pqNodeToVisit.pop();

			// If the current position matches with the targeted position
			if (currentNode->getCoordinate().equals(targetCoordinate)) 
			{
				// Store to return the traveled distance known by the current node since the first node
				int distanceToStart = currentNode->getDistanceToStart();

				// Store in pOutBuffer the shortest path used by each parent to achieved the coordinates of the current node
				std::stack<Node*> sReverseOrderPath;
				while (currentNode->getParent() != NULL)
				{
					sReverseOrderPath.push(currentNode);
					currentNode = currentNode->getParent();
				}
				for (int i = 0; i < nOutBufferSize; i++) {
					if (sReverseOrderPath.empty()){ break; }
					Node* node = sReverseOrderPath.top();
					sReverseOrderPath.pop();
					pOutBuffer[i] = node->getCoordinate().getLinearOffset(m_mapWidth);
				}
				return distanceToStart;
			}
			else 
			{

				// Retrieve all possible neighbouring Nodes of the current Node
				Node* neighboringNodes[4];
				calculateNeighbours(currentNode, targetCoordinate, neighboringNodes);

				for (int i = 0; i < 4; i++) {
					Node* neighbourNode = neighboringNodes[i];

					if (neighbourNode != NULL) {
						// Function of the state of the node
						switch (neighbourNode->getCurrentState())
						{
						case (Node::e_stateNew) :
							// New node
							pqNodeToVisit.push(neighbourNode);
							neighbourNode->setCurrentState(Node::e_stateQueued);
							break;
						case (Node::e_stateQueued) :
							// Nothing
							break;
						case (Node::e_stateProcessed) :
							// Node already processed
							if ((currentNode->getDistanceToStart() + 1) < neighbourNode->getDistanceToStart() )
							{
								neighbourNode->setParent(currentNode);
							}
							break;
						}
	
					}
				}

			}
		}

		return -1;
	}

	// Private methode : creates a valid node, adds its parent if it exist, registers the created node in the nodesMap and returns it
	// Passes the targeted coordinates in order to estimate the remaining distance from the targeted node to this node
	Node* PathfindingSolver::createNode(Coordinate& coordinate, Coordinate& target, Node* parent /*= NULL*/)
	{
		if (coordinate.getX() < 0 || coordinate.getY() < 0 || coordinate.getX() >= m_mapWidth || coordinate.getY() >= m_mapHeight) return NULL;

		Node* newNode = new Node(coordinate, target);
		if (parent != NULL)
		{
			newNode->setParent(parent);
		}

		m_nodesMap[coordinate.getLinearOffset(m_mapWidth)] = newNode;

		return newNode;
	}

	// Private method : retrieve a pointer the node by its coordinates in the nodesMap
	Node* PathfindingSolver::getNode(Coordinate &coordinate)
	{
		if (coordinate.getX() < 0 || coordinate.getY() < 0 || coordinate.getX() >= m_mapWidth || coordinate.getY() >= m_mapHeight) return NULL;
		return m_nodesMap[coordinate.getLinearOffset(m_mapWidth)];
	}


	// Private method : calculates and stores all possible neighbours from a node
	// Passes the targeted coordinates in order to estimate the remaining distance from the targeted node to all of the neighbouring nodes
	void PathfindingSolver::calculateNeighbours(Node* previousNode, Coordinate& target, Node* neighbours[4])
	{
		{
			// Retrieve neighbouring node coordinate on the right
			Coordinate coordinate(previousNode->getCoordinate().getX() + 1, previousNode->getCoordinate().getY());

			// Returned NULL if out of bounds
			Node* node = getNode(coordinate);

			if (node == NULL)
			{
				if (isPassable(coordinate))
				{
					node = createNode(coordinate, target, previousNode);
				}

			}
			neighbours[0] = node;
		}

		{
			// Retrieve neighbouring node coordinate on the left
			Coordinate coordinate(previousNode->getCoordinate().getX() - 1, previousNode->getCoordinate().getY());

			// Returned NULL if out of bounds
			Node* node = getNode(coordinate);
			if (node == NULL)
			{
				if (isPassable(coordinate))
				{
					node = createNode(coordinate, target, previousNode);
				}

			}
			neighbours[1] = node;
		}

		{
			// Retrieve neighbouring node coordinate above
			Coordinate coordinate(previousNode->getCoordinate().getX(), previousNode->getCoordinate().getY() + 1);

			// Returned NULL if out of bounds
			Node* node = getNode(coordinate);
			if (node == NULL)
			{
				if (isPassable(coordinate))
				{
					node = createNode(coordinate, target, previousNode);
				}

			}
			neighbours[2] = node;
		}
		
		{
			// Retrieve neighbouring node coordinate below
			Coordinate coordinate(previousNode->getCoordinate().getX(), previousNode->getCoordinate().getY() - 1);

			// Returned NULL if out of bounds
			Node* node = getNode(coordinate);
			if (node == NULL)
			{
				if (isPassable(coordinate))
				{
					node = createNode(coordinate, target, previousNode);
				}

			}
			neighbours[3] = node;
		}
	}

	// Public function : return true if the coordinate is a valid position in pMap
	bool PathfindingSolver::isPassable(Coordinate& coordinateToTest)
	{
		if (coordinateToTest.getX() < 0 || coordinateToTest.getY() < 0 || coordinateToTest.getX() >= m_mapWidth || coordinateToTest.getY() >= m_mapHeight) return false;
		return (m_map[coordinateToTest.getLinearOffset(m_mapWidth)] != 0);
	}
} // namespace pathfinding