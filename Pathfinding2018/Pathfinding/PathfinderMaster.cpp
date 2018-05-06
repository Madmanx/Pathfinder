
#include "stdafx.h"
#include "PathfinderMaster.h"
#include "Node.h"
#include "Pathfinder.h"
#include <thread>

using namespace std;

namespace Pathfinder
{

	static PathfinderMaster* instanceUnique;

	void PathfinderMaster::Solve()
	{
		int i = 0;
		while (!todoJobs.empty() || !currentJobs.empty()) {
			while (i < static_cast<int>(currentJobs.size()))
			{
				if (currentJobs[i]->jobDone)
				{
					currentJobs[i]->NotifyComplete();
					currentJobs.erase(currentJobs.begin() + i);
				}
				else
				{
					i++;
				}
			}

			if (static_cast<int>(todoJobs.size()) > 0 && static_cast<int>(currentJobs.size()) < MaxJobs)
			{
				Pathfinder *job = todoJobs[0];
				todoJobs.erase(todoJobs.begin());
				currentJobs.push_back(job);

				//Start a new thread

				thread  *jobThread = new thread([&]() {job->FindPath(); });
				jobThread->join();

			}
		}
		
	}

	void PathfinderMaster::RequestPathfind(Node *start, Node *target, PathfindingJobComplete completeCallback)
	{
		Pathfinder *newJob = new Pathfinder(start, target, completeCallback);
		todoJobs.push_back(newJob);
		Solve();
	}

	PathfinderMaster::PathfinderMaster() {
		currentJobs = std::vector<Pathfinder*>();
		todoJobs = std::vector<Pathfinder*>();
	}

	PathfinderMaster* PathfinderMaster::GetInstance()
	{
		if (instanceUnique == nullptr)
			instanceUnique = new PathfinderMaster();
		return
			instanceUnique;
	}
}