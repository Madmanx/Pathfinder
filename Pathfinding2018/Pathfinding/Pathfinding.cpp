// Pathfinding.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include "PathfindingAPI.h"
#include <iostream>
#include <algorithm>    // std::min

using namespace std;


#define BUFFERSIZE 12
#define BUFFERSIZE2 7

int main()
{
	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[12];
	int nbVisitedPositions = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, BUFFERSIZE);

	// Print Example 1
	cout << nbVisitedPositions << '\n';
	cout << "{";
	int maxIterationCount = min(nbVisitedPositions, BUFFERSIZE);
	for (int i = 0; i < maxIterationCount; i++)
	{
		if (i != 0)
		{
			cout << ";";
		}
		cout << pOutBuffer[i];
	}
	cout << "}" << '\n';
	system("pause");

	// Print Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	int nbVisitedPositions2 = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, BUFFERSIZE2);

	cout << nbVisitedPositions2 << '\n';
	cout << "{";
	int maxIterationCount2 = min(nbVisitedPositions2, BUFFERSIZE2);
	for (int i = 0; i < maxIterationCount2; i++)
	{
		if (i != 0)
		{
			cout << ";";
		}
		cout << pOutBuffer2[i];
	}
	cout << "}" << '\n';

	system("pause");
	return 0;
}

