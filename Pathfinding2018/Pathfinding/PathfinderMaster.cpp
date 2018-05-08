///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    08/05/2015
//  Filename:		 pathfinderMaster.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PathfinderMaster.h"
#include "Node.h"
#include "Pathfinder.h"
#include <thread>

using namespace std;

namespace Pathfinder
{
	static PathfinderMaster* instanceUnique;

	// Update on the main thread
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

			if (static_cast<int>(todoJobs.size()) > 0 /*&& static_cast<int>(currentJobs.size()) < MaxJobs*/)
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

	// starting job could be called by multiple agents
	void PathfinderMaster::RequestPathfind(Node *start, Node *target, PathfindingJobComplete completeCallback)
	{
		Pathfinder *newJob = new Pathfinder(start, target, completeCallback);
		todoJobs.push_back(newJob);
		Solve();
	}

	// destructor
	PathfinderMaster::PathfinderMaster() {
		currentJobs = vector<Pathfinder*>();
		todoJobs = vector<Pathfinder*>();
	}

	// singleton
	PathfinderMaster* PathfinderMaster::GetInstance()
	{
		if (instanceUnique == nullptr)
			instanceUnique = new PathfinderMaster();
		return
			instanceUnique;
	}
}