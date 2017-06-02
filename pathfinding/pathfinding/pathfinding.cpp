#include "stdafx.h"
#include "pathfinding.h"
#include <iostream>
#include <algorithm>
#include <list>  
#include <map>
#include <cmath>
#include <float.h>
#include <string>
#include <math.h>

using namespace std;

class pathfinding {

	int getIndex(
		int column,
		int row,
		int arrayWidth) {

		return row * arrayWidth + column;
	}

	int getRow(
		int index,
		int arrayWidth) {

		return index / arrayWidth;
	}

	int getColumn(
		int index,
		int arrayWidth) {

		return index % arrayWidth;
	}

	void findAdjacentNodes(
		int index,
		int* neighbors,
		int arrayWidth,
		int arrayHeight)
	{
		//left

		if (getColumn(index, arrayWidth) != 0) {
			neighbors[0] = index - 1;
		}
		else {
			neighbors[0] = -1;
		}

		//right

		if (getColumn(index, arrayWidth) != arrayWidth - 1) {
			neighbors[1] = index + 1;
		}
		else {
			neighbors[1] = -1;
		}

		//top

		if (getRow(index, arrayWidth) != 0) {
			neighbors[2] = index - arrayWidth;
		}
		else {
			neighbors[2] = -1;
		}

		//bottom

		if (getRow(index, arrayWidth) < arrayHeight - 1) {
			neighbors[3] = index + arrayWidth;
		}
		else {
			neighbors[3] = -1;
		}

	}

	void findAdjacentPassableNodes(
		int index,
		int* neighbors,
		int arrayWidth,
		int arrayHeight,
		const unsigned char* pMap)
	{
		findAdjacentNodes(index, neighbors, arrayWidth, arrayHeight);

		for (int i = 0; i < 4; i++) {
			if (!isPassable(neighbors[i], pMap)) {
				neighbors[i] = -1;
			}
		}
	}

	bool isPassable(int index, const unsigned char* pMap) {
		return pMap[index] == 1;
	}

	int getMinIndexInSet(map<int, double>& map, list<int>& set) {

		int lowestIndex = set.back();

		double lowestFScore = getWithDefault(map, lowestIndex, DBL_MAX);

		for each (int i in set) {

			double currentfScore = getWithDefault(map, i, DBL_MAX);

			if (currentfScore < lowestFScore) {

				lowestFScore = currentfScore;
				lowestIndex = i;
			}

		}

		return lowestIndex;
	}

	void reconstructPath(list<int>& totalPath, map<int, int>& cameFrom, int currentIndex, int startIndex) {

		totalPath.push_back(currentIndex);

		while (getWithDefault(cameFrom, currentIndex, -1) != -1 && cameFrom[currentIndex] != startIndex) {

			currentIndex = cameFrom[currentIndex];
			totalPath.push_back(currentIndex);

		}
	}

	double manhattanDistance(int startIndex, int goalIndex, int width) {

		int x1 = getColumn(startIndex, width);
		int x2 = getColumn(goalIndex, width);

		int y1 = getRow(startIndex, width);
		int y2 = getRow(goalIndex, width);

		int xdiff = abs(x2 - x1);
		int ydiff = abs(y2 - y1);

		double tieBreaker = ((double)rand() / (double)(RAND_MAX)) / 100;

		return xdiff + ydiff + tieBreaker;
	}

public:
	int FindPath(
		const int nStartX,
		const int nStartY,
		const int nTargetX,
		const int nTargetY,
		const unsigned char* pMap,
		const int nMapWidth,
		const int nMapHeight,
		int* pOutBuffer,
		const int nOutBufferSize) {

		list<int> closedSet, openSet, totalPath;

		map <int, int> cameFrom;

		map<int, double> gScore, fScore;

		int neighbors[4];

		int startIndex = getIndex(nStartX, nStartY, nMapWidth);

		int goalIndex = getIndex(nTargetX, nTargetY, nMapWidth);

		int shortestPathLength = -1;

		openSet = { startIndex };

		closedSet = { -1 };

		gScore[startIndex] = 0; //cost of getting from start node to this node

		fScore[startIndex] = manhattanDistance(startIndex, goalIndex, nMapWidth); //cost of getting from start node to the target node via this one

		while (openSet.size() != 0)
		{
			int currentIndex = getMinIndexInSet(fScore, openSet);

			if (currentIndex == goalIndex) {

				reconstructPath(totalPath, cameFrom, currentIndex, startIndex);

				shortestPathLength = totalPath.size();

				for (int i = 0; i < shortestPathLength; i++) {
					pOutBuffer[i] = totalPath.back();
					totalPath.pop_back();
				}

				break;
			}

			openSet.remove(currentIndex);

			closedSet.push_back(currentIndex);

			findAdjacentPassableNodes(currentIndex, neighbors, nMapWidth, nMapHeight, pMap);

			for each (int n in neighbors) {

				if (find(begin(closedSet), end(closedSet), n) != end(closedSet)) {
					continue;
				}

				double tentativeG = getWithDefault(gScore, currentIndex, DBL_MAX) + manhattanDistance(startIndex, n, nMapWidth);

				if (find(begin(openSet), end(openSet), n) == end(openSet)) {
					openSet.push_back(n);
				}
				else if (tentativeG >= getWithDefault(gScore, n, DBL_MAX)) {
					continue;
				}

				cameFrom[n] = currentIndex;
				gScore[n] = tentativeG;
				fScore[n] = getWithDefault(gScore, n, DBL_MAX) + manhattanDistance(n, goalIndex, nMapWidth);
			}
		}

		return shortestPathLength;
	}
};

int main()
{
	pathfinding pf;

	const unsigned char pMap[] = {
		1,1,1,0,1,1,
		1,1,1,0,1,1,
		1,0,1,1,1,1,
		1,1,1,0,0,1,
		1,1,1,1,0,1,
		1,1,1,0,1,1
	};

	int pOutBuffer[24];

	int pathLength = pf.FindPath(4, 5, 0, 3, pMap, 6, 6, pOutBuffer, 24);

	// handle too small buffer

	//int bufferSize = sizeof(pOutBuffer) / sizeof(pOutBuffer[0]);

	//if (pathLength > bufferSize) {

	//	int* newBuffer;

	//	newBuffer = (int*)alloca(pathLength);

	//	pathLength = pf.FindPath(4, 5, 0, 3, pMap, 6, 6, newBuffer, pathLength);

	//	int stop = 0;

	//}

	return 0;
}