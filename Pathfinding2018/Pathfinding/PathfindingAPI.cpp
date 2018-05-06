///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 pathfindingAPI.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PathfindingAPI.h"
#include "GridBase.h"
#include "PathfinderMaster.h"
#include <iostream>

using PathfindingJobComplete = std::function<void(std::vector<Pathfinder::Node*> &path)>;
/**
nStartX, nStarty start position
nTargetX, nTargetY target position
nMapWidth, nMapHeight height and width of the grid
pOutBuffer tab position visited by the buffer
nOutBufferSize max entries visited by the buffer
pOutBuffer[nOutBufferSize] buffer of visited position
Retrieve the number of step of an optimized path between a started position and a targeted position in a 1 dimensional Map
Update pOutBuffer with visited positions in the 1 dimensional Map
*/
int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	Pathfinder::GridBase::GetInstance()->Init(pMap, nMapWidth, nMapHeight);

	Pathfinder::Node startNode(nStartX, nStartY);
	Pathfinder::Node end(nTargetX, nTargetY);

	Pathfinder::PathfinderMaster::GetInstance()->RequestPathfind(&startNode, &end, [&](std::vector<Pathfinder::Node*> path) { 
		int i = 0;
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			i++;
			pOutBuffer[i] = (*it)->m_x + nMapWidth * (*it)->m_y;
		}
		return static_cast<int>(path.size());
	});
	//Pathfinder::Pathfinder solver(pMap, nMapWidth, nMapHeight);

	//Use a a - star alike algorithm.
	//return solver.solveWithAStarAlgorithm(nStartX, nStartY, nTargetX, nTargetY, pOutBuffer, nOutBufferSize);
	return -1;
}

