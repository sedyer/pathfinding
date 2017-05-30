#include "stdafx.h"
#include <iostream>
#include <list>  
#include <map>
#include <algorithm>
using namespace std;

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
	//	0 1 2 3 4 5 6 7 8 9 10 11
	//	0's neighbors are 1 and 4
	//	4's neighbors are 0, 5, 8

	//	0 1 2 3
	//	4 5 6 7
	//	8 9 10 11

	//get left neighbor

	if (getColumn(index, arrayWidth) != 0) {
		neighbors[0] = index - 1;
	}
	else {
		neighbors[0] = -1;
	}

	//get right neighbor

	if (getColumn(index, arrayWidth) != arrayWidth - 1) {
		neighbors[1] = index + 1;
	}
	else {
		neighbors[1] = -1;
	}

	//get top neighbor

	if (getRow(index, arrayWidth) != 0) {
		neighbors[2] = index - arrayWidth;
	}
	else {
		neighbors[2] = -1;
	}

	//get bottom neighbor

	if (getRow(index, arrayWidth) < arrayHeight - 1) {
		neighbors[3] = index + arrayWidth;
	}
	else {
		neighbors[3] = -1;
	}

}

template <typename K, typename V>

V getWithDefault(const map <K, V> & map, const K & key, const V & default) {

	typename map<K, V>::const_iterator iterator = map.find(key);

	if (iterator == map.end()) {
		return default;
	}
	else {
		return iterator->second;
	}
}

void reconstructPath(list<int>& totalPath, map<int, int>& cameFrom, int currentIndex) {
	
	totalPath.push_back(currentIndex);

	while (find(begin(cameFrom), end(cameFrom), currentIndex) != end(cameFrom)) {
		currentIndex = cameFrom[currentIndex];
		totalPath.push_back(currentIndex);
	}
}

void FindPath(
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

	map <int, int> gScore, fScore, cameFrom;

	int startIndex = getIndex(nStartX, nStartY, nMapWidth);

	int goalIndex = getIndex(nTargetX, nTargetY, nMapWidth);

	openSet = { startIndex };

	//gScore = cost of getting from start node to this node

	gScore[startIndex] = 0;

	//fScore = cost of getting from start node to the target not, by passing that node

	fScore[startIndex] = estimateCost(startIndex, goalIndex);

	while (openSet.size() != 0) 
	{
		int currentIndex = indexWithLowestValue(fScore);

		if (currentIndex = goalIndex) {
			reconstructPath(totalPath, cameFrom, currentIndex);
		}

		openSet.remove(currentIndex);

		closedSet.push_back(currentIndex);

		int neighbors[4];

		findAdjacentNodes(currentIndex, neighbors, nMapWidth, nMapHeight);

		for (int i = 0; i < 4; i++) {
			if (find(begin(closedSet), end(closedSet), neighbors[i]) != end(closedSet)) {
				continue;
			}

			if (find(begin(openSet), end(openSet), neighbors[i]) == end(openSet)) {
				openSet.push_back(neighbors[i]);
			}
			else if (gScore[currentIndex] >= gScore[neighbors[i]]) {
				continue;
			}

			cameFrom[neighbors[i]] = currentIndex;
			gScore[neighbors[i]] = gScore[currentIndex];
			fScore[neighbors[i]] = gScore[neighbors[i]] + estimateCost(neighbors[i], goalIndex);
		}
	}
}

int main()
{
	unsigned char pMap[] = { 1,1,1,1,0,1,0,1,0,1,1,1 };

	//	1 1 1 1
	//	0 1 0 1
	//	0 1 1 1

	int pOutBuffer[12];

	FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	//	0 1 2 3
	//	4 5 6 7
	//	8 9 10 11

	int neighbors[4];

	findAdjacentNodes(6, neighbors, 4, 3);

    return 0;
}
