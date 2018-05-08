///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    08/05/2015
//  Filename:		 node.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Node.h"

namespace Pathfinder
{
	// Final cost of the path : current distance travelled + remaining distance to travel (heuristic)
	int Node::getfCost() const
	{
		return gCost + hCost;
	}

	Node::Node(int x, int y) : m_x(x), m_y(y) 
	{
	}

	// Redefine Operator Equals
	bool Node::Equals(Node* n) {
		return (this->m_x == n->m_x && this->m_y == n->m_y);
	}
}
