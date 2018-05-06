///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 pathfindingsolver.h
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PATHFINDINGSOLVER_H
#define PATHFINDINGSOLVER_H

#include "Node.h"
#include <stack>

namespace Pathfinding {

	class PathfindingSolver {
		public:
			// Public constructor : initiate an array of Node*
			PathfindingSolver::PathfindingSolver(const unsigned char * pMap, const int nMapWidth, const int nMapHeight);
			// Public destructor : clear an array of Node*
			PathfindingSolver::~PathfindingSolver();

			// Public method : Find the shortest path, return -1 if such a path doesn't exist
			int PathfindingSolver::solveWithAStarAlgorithm(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, int* pOutBuffer, const int nOutBufferSize);

		private:
			Node** m_nodesMap;
			const int m_mapWidth;
			const int m_mapHeight;
			const unsigned char* m_map;

			// Private methode : creates a valid node, adds its parent if it exist, registers the created node in the nodesMap and returns it
			// Passes the targeted coordinates in order to estimate the remaining distance from the targeted node to this node
			Node* PathfindingSolver::createNode(Coordinate& coordinate, Coordinate& target, Node* parent = NULL);
	
			// Private method : retrieve a pointer the node by its coordinates in the nodesMap
			Node* PathfindingSolver::getNode(Coordinate& coordinate);
			
			// Private method : calculates and stores all possible neighbours from a node
			// Passes the targeted coordinates in order to estimate the remaining distance from the targeted node to all of the neighbouring nodes
			void PathfindingSolver::calculateNeighbours(Node* previousNode, Coordinate& target, Node* neighbours[4]);

			// Public function : return true if the coordinate is a valid position in pMap
			bool PathfindingSolver::isPassable(Coordinate& coordinateToTest);

	};
} // namespace pathfinding
#endif