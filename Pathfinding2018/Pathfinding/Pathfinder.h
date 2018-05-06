#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <functional>
#include "PathfinderMaster.h"

namespace Pathfinder { class Node; }
namespace Pathfinder { class GridBase; }

namespace Pathfinder
{
	using PathfindingJobComplete = std::function<void(std::vector<Node*> &path)>;
	class Pathfinder
	{
	public:
		GridBase * gridBase;

		Node * startPosition;
		Node *endPosition;

		//ORIGINAL LINE: public volatile bool jobDone = false;
		bool /*volatile*/ jobDone = false;
		PathfindingJobComplete completeCallback;
		std::vector<Node*> foundPath;

		//Constructor
		virtual ~Pathfinder()
		{
//			delete gridBase;
			delete startPosition;
			delete endPosition;
		}

		Pathfinder(Node *start, Node *target, PathfindingJobComplete callback);

		void FindPath();

		void NotifyComplete();

	private:
		std::vector<Node*> FindPathActual(Node *start, Node *target);

		std::vector<Node*> RetracePath(Node *startNode, Node *endNode);

		std::vector<Node*> GetNeighbours(Node *node, bool getVerticalneighbours = false);

		Node *GetNeighbourNode(Node *adjPos, bool searchTopDown, Node *currentNodePos);

		Node *GetNode(int x, int y);

		int GetDistance(Node *posA, Node *posB);

	};
}
