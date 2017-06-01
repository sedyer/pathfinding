#include "stdafx.h"
#include "pathfinding.h"
#include <iostream>
#include <algorithm>
#include <list>  
#include <map>
#include <cmath>

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

	int getMinIndex(map<int, double>& map) {

		int lowestIndex = 0;
		double lowestValue = map.begin()->second;

		for each (pair<int, double> pair in map)
		{
			if (pair.second < lowestValue) {

				lowestValue = pair.second;
				lowestIndex = pair.first;
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

	double estimateCost(int startIndex, int goalIndex, int width) {

		int x1 = getColumn(startIndex, width);
		int x2 = getColumn(goalIndex, width);

		int y1 = getRow(startIndex, width);
		int y2 = getRow(goalIndex, width);

		int xdiff = x2 - x1;
		int ydiff = y2 - y1;

		int sumOfSquares = xdiff * xdiff + ydiff * ydiff;

		return sqrt(sumOfSquares);
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

		fScore[startIndex] = estimateCost(startIndex, goalIndex, nMapWidth); //cost of getting from start node to the target node via this one

		while (openSet.size() != 0)
		{
			int currentIndex = getMinIndex(fScore);

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

				if (find(begin(openSet), end(openSet), n) == end(openSet)) {
					openSet.push_back(n);
				}
				else if (gScore[currentIndex] >= gScore[n]) {
					continue;
				}

				cameFrom[n] = currentIndex;
				gScore[n] = gScore[currentIndex];
				fScore[n] = gScore[n] + estimateCost(n, goalIndex, nMapWidth);
			}
		}

		return shortestPathLength;
	}
};

int main()
{
	pathfinding pf;

	unsigned char pMap[] = {
		1,0,1,1,
		1,1,0,1,
		0,1,0,1
	};

	int pOutBuffer[2];

	int pathLength = pf.FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	// handle too small buffer

	int bufferSize = sizeof(pOutBuffer) / sizeof(pOutBuffer[0]);

	if (pathLength > bufferSize) {

		int* buffer = new int[pathLength];

		int newbufferSize = sizeof(buffer) / sizeof(buffer[0]);

		pf.FindPath(0, 0, 1, 2, pMap, 4, 3, buffer, pathLength);

		int stop = 0;

	}

	return 0;
}