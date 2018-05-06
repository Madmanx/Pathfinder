#include "stdafx.h"
#include "Pathfinder.h"
#include "PathfinderMaster.h"
#include "GridBase.h"
#include "Node.h"
#include <unordered_set>
#include <thread>         // std::thread
#include <mutex>  // std::mutex, std::lock

std::mutex mtx;

namespace Pathfinder
{

	Pathfinder::Pathfinder(Node *start, Node *target, PathfindingJobComplete callback)
	{
		startPosition = start;
		endPosition = target;
		completeCallback = callback;
		gridBase = GridBase::GetInstance();
	}

	void Pathfinder::FindPath()
	{
		foundPath = FindPathActual(startPosition, endPosition);

		jobDone = true;
	}

	void Pathfinder::NotifyComplete()
	{
		if (completeCallback != nullptr)
		{
			completeCallback(foundPath);
		}
	}

	std::vector<Node*> Pathfinder::FindPathActual(Node *start, Node *target)
	{
		//Typical A* algorythm from here and on

		std::vector<Node*> foundPath;

		//We need two lists, one for the nodes we need to check and one for the nodes we've already checked
		std::vector<Node*> openSet;
		std::unordered_set<Node*> closedSet;

		//We start adding to the open set
		openSet.push_back(start);

		while (static_cast<int>(openSet.size()) > 0)
		{
			Node *currentNode = openSet[0];

			for (int i = 0; i < static_cast<int>(openSet.size()); i++)
			{
				//We check the costs for the current node
				//You can have more opt. here but that's not important now
				if (openSet[i]->getfCost() < currentNode->getfCost() || (openSet[i]->getfCost() == currentNode->getfCost() && openSet[i]->hCost < currentNode->hCost))
				{
					//and then we assign a new current node
					if (!currentNode->Equals(openSet[i]))
					{
						currentNode = openSet[i];
					}
				}
			}

			//we remove the current node from the open set and add to the closed set
			for (int i = 0; i < static_cast<int>(openSet.size()); i++)
			{
				if (currentNode->Equals(openSet[i]))
				{
					openSet.erase(openSet.begin() + i);
				}	
			}
			closedSet.insert(currentNode);

			//if the current node is the target node
			if (currentNode->Equals(target))
			{
				//that means we reached our destination, so we are ready to retrace our path
				foundPath = RetracePath(start, currentNode);
				break;
			}

			//if we haven't reached our target, then we need to start looking the neighbours
			for (auto neighbour : GetNeighbours(currentNode, true))
			{
				if (std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end() == false)
				{
					//we create a new movement cost for our neighbours
					int newMovementCostToNeighbour = currentNode->gCost + GetDistance(currentNode, neighbour);

					//and if it's lower than the neighbour's cost
					if (newMovementCostToNeighbour < neighbour->gCost || (std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end() == false))
					{
						//we calculate the new costs
						neighbour->gCost = newMovementCostToNeighbour;
						neighbour->hCost = GetDistance(neighbour, target);
						//Assign the parent node
						neighbour->parentNode = currentNode;
						//And add the neighbour node to the open set
						if (std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end() == false)
						{
							openSet.push_back(neighbour);
						}
					}
				}
			}
		}

		//we return the path at the end
		return foundPath;
	}

	std::vector<Node*> Pathfinder::RetracePath(Node *startNode, Node *endNode)
	{
		//Retrace the path, is basically going from the endNode to the startNode
		std::vector<Node*> path;
		Node *currentNode = endNode;

		while (currentNode != startNode)
		{
			path.push_back(currentNode);
			//by taking the parentNodes we assigned
			currentNode = currentNode->parentNode;
		}

		//then we simply reverse the list
		std::reverse(path.begin(), path.end());

		return path;
	}

	std::vector<Node*> Pathfinder::GetNeighbours(Node *node, bool getVerticalneighbours)
	{
		//This is were we start taking our neighbours
		std::vector<Node*> retList;

		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				//If we don't want a 3d A*, then we don't search the y
				if (!getVerticalneighbours)
				{
					y = 0;
				}

				if (x == 0 && y == 0)
				{
					//000 is the current node
				}
				else
				{
					Node *searchPos = new Node(node->m_x + x, node->m_y + y);
					Node *newNode = GetNeighbourNode(searchPos, true, node);

					if (newNode != nullptr)
					{
						retList.push_back(newNode);
					}
				}
			}
		}

		return retList;

	}

	Node *Pathfinder::GetNeighbourNode(Node *adjPos, bool searchTopDown, Node *currentNodePos)
	{
		//this is where the meat of it is
		//We can add all the checks we need here to tweak the algorythm to our heart's content
		//but first let's start from the the usual stuff you'll see in A*

		Node *retVal = nullptr;

		//let's take the node from the adjacent positions we passed
		Node *node = GetNode(adjPos->m_x, adjPos->m_y);

		//if it's not null and we can walk on it
		if (node != nullptr && node->isWalkable)
		{
			//we can use that node
			retVal = node;
		} //if not
		else if (searchTopDown) //and we want to have 3d A*
		{
			//then look what the adjacent node have under him
			adjPos->m_y -= 1;
			Node *bottomBlock = GetNode(adjPos->m_x, adjPos->m_y);

			//if there is a bottom block and we can walk on it
			if (bottomBlock != nullptr && bottomBlock->isWalkable)
			{
				retVal = bottomBlock; // we can return that
			}
			else
			{
				//otherwise, we look what it has on top of it
				adjPos->m_y += 2;
				Node *topBlock = GetNode(adjPos->m_x, adjPos->m_y);
				if (topBlock != nullptr && topBlock->isWalkable)
				{
					retVal = topBlock;
				}
			}
		}

		//if the node is diagonal to the current node then check the neighbouring nodes
		//so to move diagonally, we need to have 4 nodes walkable
		int originalX = adjPos->m_x - currentNodePos->m_x;
		int originalY = adjPos->m_y - currentNodePos->m_y;

		if (abs(originalX) == 1 && abs(originalY) == 1)
		{
			// the first block is originalX, 0 and the second to check is 0, originalZ
			//They need to be pathfinding walkable
			Node *neighbour1 = GetNode(currentNodePos->m_x + originalX, currentNodePos->m_y);
			if (neighbour1 == nullptr || !neighbour1->isWalkable)
			{
				retVal = nullptr;
			}

			Node *neighbour2 = GetNode(currentNodePos->m_x, currentNodePos->m_y);
			if (neighbour2 == nullptr || !neighbour2->isWalkable)
			{
				retVal = nullptr;
			}
		}

		//and here's where we can add even more additional checks
		if (retVal != nullptr)
		{
			//Example, do not approach a node from the left
			/*if(node.x > currentNodePos.x) {
			node = null;
			}*/
		}

		return retVal;
	}

	Node* Pathfinder::GetNode(int x, int y)
	{
		Node *n = nullptr;

		mtx.lock();
		if (gridBase)
		{
			n = gridBase->GetNode(x, y);
		}
		mtx.unlock();

		return n;
	}

	int Pathfinder::GetDistance(Node *posA, Node *posB)
	{
		//We find the distance between each node
		//not much to explain here

		int distX = abs(posA->m_x - posB->m_x);
		int distY = abs(posA->m_y - posB->m_y);

		// sqrt or heuristic
		if (distX > distY)
		{
			return distY + (distX - distY);
		}

		return distX + (distY - distX);
	}
}
