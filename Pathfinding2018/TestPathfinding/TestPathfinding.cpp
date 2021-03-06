// TestPathfinding.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "PathfindingAPI.h"
#include <algorithm>
#include <iostream>

#define BUFFERSIZE 12
#define BUFFERSIZE2 7
#define BUFFERSIZE3 20

int main()
{
	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[BUFFERSIZE];
	int nbVisitedPositions = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, BUFFERSIZE);

	//// Print Example 1
	cout << nbVisitedPositions << '\n';
	cout << "{";
	int maxIterationCount = min(nbVisitedPositions, BUFFERSIZE);
	for (int i = 0; i < maxIterationCount; i++)
	{
		if (i != 0)
			cout << ";";
		cout << pOutBuffer[i];
	}
	cout << "}" << '\n';
	system("pause");

	// Print Example 2
	unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[BUFFERSIZE2];
	int nbVisitedPositions2 = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, BUFFERSIZE2);

	cout << nbVisitedPositions2 << '\n';
	cout << "{";
	int maxIterationCount2 = min(nbVisitedPositions2, BUFFERSIZE2);
	for (int i = 0; i < maxIterationCount2; i++)
	{
		if (i != 0)
			cout << ";";
		cout << pOutBuffer2[i];
	}
	cout << "}" << '\n';

	system("pause");


	// Print Example 3
	unsigned char pMap3[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer3[BUFFERSIZE3];
	int nbVisitedPositions3 = FindPath(3, 4, 8, 3, pMap3, 9, 9, pOutBuffer3, BUFFERSIZE3);

	cout << nbVisitedPositions3 << '\n';
	cout << "{";
	int maxIterationCount3 = min(nbVisitedPositions3, BUFFERSIZE2);
	for (int i = 0; i < maxIterationCount3; i++)
	{
		if (i != 0)
			cout << ";";
		cout << pOutBuffer3[i];
	}
	cout << "}" << '\n';

	system("pause");
	return 0;
}

