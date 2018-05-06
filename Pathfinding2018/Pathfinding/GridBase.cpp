
#include "stdafx.h"
#include "GridBase.h"
#include "Node.h"
#include <iostream>

namespace Pathfinder
{
	static GridBase* instanceUnique = nullptr;


	GridBase::GridBase() {

	}

	void GridBase::Init(const unsigned char *pMap, const int nMapWidth, const int nMapHeight) {
		m_MapWidth = nMapWidth;
		m_MapHeight = nMapHeight;
		grid = std::vector<std::vector<Node*>>(nMapWidth);
		for (int x = 0; x < nMapWidth; x++)
		{
			grid[x] = std::vector<Node*>(nMapHeight);
			for (int y = 0; y < nMapHeight; y++)
			{
				Node *node = new Node(x, y);
				
				if (pMap[x + y] == 1) {
					node->isWalkable = false;
				}

				//then place it to the grid
				grid[x][y] = node;
			}
		}
	}

	GridBase::~GridBase()
	{
		if (!grid.empty())
		{
			for (int x = 0; x < m_MapHeight; x++)
			{
				for (int y = 0; y < m_MapWidth; y++)
				{
					Node* node = grid[x][y];
					if (node != NULL)
					{
						delete node;
					}
				}
			}
			grid.clear();
		}
	}

	Node *GridBase::GetNode(int x, int y)
	{
		if (grid.empty())
		{
			return nullptr;
		}
		if (x < m_MapWidth && x >= 0 && y >= 0 && y < m_MapHeight)
		{
			return grid[x][y];
		}
		return nullptr;
	}


	GridBase* GridBase::GetInstance()
	{
		if (instanceUnique == nullptr)
			instanceUnique = new GridBase();
		return
			instanceUnique;
	}
}
