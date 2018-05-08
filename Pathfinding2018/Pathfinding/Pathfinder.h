#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <functional>
#include "PathfinderMaster.h"


namespace Pathfinder { class Node; }
namespace Pathfinder { class GridBase; }

using namespace std;

namespace Pathfinder
{
	// Redefine two many times ?  ? ? 
	using PathfindingJobComplete = function<void(vector<Node*> &path)>;
	class Pathfinder
	{
	public:
		GridBase * gridBase;

		Node * startPosition;
		Node *endPosition;

		bool /*volatile*/ jobDone = false;
		PathfindingJobComplete completeCallback;
		vector<Node*> foundPath;

		//Constructor
		virtual ~Pathfinder()
		{
			delete startPosition;
			delete endPosition;
		}

		Pathfinder(Node *start, Node *target, PathfindingJobComplete callback);

		void FindPath();

		void NotifyComplete();

	private:
		vector<Node*> FindPathActual(Node *start, Node *target);

		// Retrace path using parent node
		vector<Node*> RetracePath(Node *startNode, Node *endNode);

		vector<Node*> GetNeighbours(Node *node);

		// Retrieve a node, insert controls here
		Node *GetNeighbourNode(Node *adjPos, Node *currentNodePos);

		Node *GetNode(int x, int y);

		int GetDistance(Node *posA, Node *posB);

	};
}
