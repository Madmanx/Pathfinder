#pragma once
#include "stdafx.h"
#include "Node.h"
#include <vector>

using namespace std;

namespace Pathfinder { class Node; }
namespace Pathfinder { class PathfinderMaster; }
namespace Pathfinder
{
	class GridBase
	{
	public:	
		GridBase();

		// initiate a vector of vector of Node*
		void Init(const unsigned char * pMap, const int nMapWidth, const int nMapHeight);

		int m_MapWidth;
		int m_MapHeight;

		vector<vector<Node*>> grid; // our grid
		//int agents = 0;

		virtual ~GridBase();

		Node *GetNode(int x, int y);

		static GridBase* GetInstance();
	};

}
