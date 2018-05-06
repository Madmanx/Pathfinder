///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 node.h
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#pragma once

namespace Pathfinder
{
	class Node
	{
		//Node's position in the grid
	public:
		int m_x = 0;
		int m_y = 0;

		//Node's costs for pathfinding purposes
		int hCost = 0;
		int gCost = 0;

		virtual ~Node()
		{
			delete parentNode;
		}

		int getfCost() const; //the fCost is the gCost+hCost so we can get it directly this way

		Node *parentNode;
		bool isWalkable = true;

		Node(int x, int y);

		bool Equals(Node* n);
	};
}
