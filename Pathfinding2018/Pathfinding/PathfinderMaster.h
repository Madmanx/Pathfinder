#pragma once
#include "stdafx.h"
#include <vector>
#include "Node.h"
#include "Pathfinder.h"
#include <algorithm>
#include <functional>

using namespace std;

namespace Pathfinder { class Node; }
namespace Pathfinder { class GridBase; }
namespace Pathfinder { class Pathfinder; }

namespace Pathfinder
{
	//Delegates are a variable that points to a function
	using PathfindingJobComplete = function<void(vector<Node*> &path)>;

	//This class controls the threads
	class PathfinderMaster
	{

	public:
		//The maximum simultaneous threads we allow to open
		/*int MaxJobs = 3;*/

		PathfinderMaster();

		vector<Pathfinder*> currentJobs;
		vector<Pathfinder*> todoJobs;

		virtual ~PathfinderMaster() {
			currentJobs.clear();
			todoJobs.clear();
		}

		static PathfinderMaster* GetInstance();

		void Solve();

		void RequestPathfind(Node *start, Node *target, PathfindingJobComplete completeCallback);
	};
}

