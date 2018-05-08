#include "stdafx.h"
#include "Pathfinder.h"
#include "PathfinderMaster.h"
#include "GridBase.h"
#include "Node.h"
#include <unordered_set>
#include <thread>         // std::thread
#include <mutex>  // std::mutex, std::lock

using namespace std;

mutex mtx;

namespace Pathfinder
{
	Pathfinder::Pathfinder(Node *start, Node *target, PathfindingJobComplete callback)
	{
		startPosition = start;
		endPosition = target;
		completeCallback = callback;
		gridBase = GridBase::GetInstance();
	}

	// Job started
	void Pathfinder::FindPath()
	{
		foundPath = FindPathActual(startPosition, endPosition);

		jobDone = true;
	}

	// Notify -> all the way back to lamba function in PathfindingAPI
	void Pathfinder::NotifyComplete()
	{
		if (completeCallback != nullptr)
		{
			completeCallback(foundPath);
		}
	}

	vector<Node*> Pathfinder::FindPathActual(Node *start, Node *target)
	{
		//Typical A* algorythm from here and on
		vector<Node*> foundPath;

		//We need two lists, one for the nodes we need to check and one for the nodes we've already checked
		vector<Node*> openSet;
		unordered_set<Node*> closedSet;

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
			for (auto neighbour : GetNeighbours(currentNode))
			{
				if (find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end() == false)
				{
					//we create a new movement cost for our neighbours
					int newMovementCostToNeighbour = currentNode->gCost + GetDistance(currentNode, neighbour);

					//and if it's lower than the neighbour's cost
					if (newMovementCostToNeighbour < neighbour->gCost || (find(openSet.begin(), openSet.end(), neighbour) != openSet.end() == false))
					{
						//we calculate the new costs
						neighbour->gCost = newMovementCostToNeighbour;
						neighbour->hCost = GetDistance(neighbour, target);
						//Assign the parent node
						neighbour->parentNode = currentNode;
						//And add the neighbour node to the open set
						if (find(openSet.begin(), openSet.end(), neighbour) != openSet.end() == false)
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

	vector<Node*> Pathfinder::RetracePath(Node *startNode, Node *endNode)
	{
		//Retrace the path, is basically going from the endNode to the startNode
		vector<Node*> path;
		Node *currentNode = endNode;

		while (currentNode != startNode)
		{
			path.push_back(currentNode);
			//by taking the parentNodes we assigned
			currentNode = currentNode->parentNode;
		}

		//then we simply reverse the list
		reverse(path.begin(), path.end());

		return path;
	}

	vector<Node*> Pathfinder::GetNeighbours(Node *node)
	{
		//This is were we start taking our neighbours
		vector<Node*> retList;

		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{		
				//000 is the current node
				if ((x == -1 && y == 0)
				|| (x == 0 && y == -1)
				|| (x == 0 && y == 1)
				|| (x == 1 && y == 0)
				) {
					Node *searchPos = new Node(node->m_x + x, node->m_y + y);
					Node *newNode = GetNeighbourNode(searchPos, node);

					// basically if not out of bounds
					if (newNode != nullptr)
						retList.push_back(newNode);
				}
			}
		}
		return retList;

	}

	Node *Pathfinder::GetNeighbourNode(Node *adjPos, Node *currentNodePos)
	{
		//this is where the meat of it is
		//We can add all the checks we need here to tweak the algorythm to our heart's content
		Node *retVal = nullptr;

		//let's take the node from the adjacent positions we passed
		Node *node = GetNode(adjPos->m_x, adjPos->m_y);

		//if it's not null and we can walk on it
		if (node != nullptr && node->isWalkable)
		{
			//we can use that node
			retVal = node;
		}

		//and here's where we can add even more additional checks
		if (retVal != nullptr)
		{
			// nothing yet
		}

		return retVal;
	}

	Node* Pathfinder::GetNode(int x, int y)
	{
		Node *n = nullptr;

		// multi access on grid
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
