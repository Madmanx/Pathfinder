///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 pathfindingAPI.h
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PATHFINDINGAPI_H
#define PATHFINDINGAPI_H

#include "Coordinate.h"
#include "Node.h"

/**
nStartX, nStarty start position
nTargetX, nTargetY target position
nMapWidth, nMapHeight height and width of the grid
pOutBuffer tab position visited by the buffer
nOutBufferSize max entries visited by the buffer
pOutBuffer[nOutBufferSize] buffer of visited position
Retrieve the number of step of an optimized path between a started position and a targeted position in a 1 dimensional Map
Use a a-star alike algorithm.
Update pOutBuffer with visited positions in the 1 dimensional Map
*/
int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize);

#endif