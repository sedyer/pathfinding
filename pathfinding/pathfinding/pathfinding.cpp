// pathfinding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int FindPath(
	const int nStartX,
	const int nStartY,
	const int nTargetX,
	const int nTargetY,
	const unsigned char* pMap,
	const int nMapWidth,
	const int nMapHeight,
	int* pOutBuffer,
	const int nOutBufferSize)
{

	return -1;
}

void FindAdjacentNodes(
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

	if (getColumn(index, arrayWidth) != 0) 
	{
		neighbors[0] = index - 1;
	}
	else 
	{ 
		neighbors[0] = -1;
	}

	//get right neighbor

	if (getColumn(index, arrayWidth) != arrayWidth - 1)
	{
		neighbors[1] = index + 1;
	}
	else
	{
		neighbors[1] = -1;
	}

	//get top neighbor

	if (getRow(index, arrayWidth) != 0)
	{
		neighbors[2] = index - arrayWidth;
	}
	else
	{
		neighbors[2] = -1;
	}

	//get bottom neighbor

	if (getRow(index, arrayWidth) < arrayHeight - 1)
	{
		neighbors[3] = index + arrayWidth;
	}
	else
	{
		neighbors[3] = -1;
	}

}

int getRow(
	int index,
	int arrayWidth)
{
	return index / arrayWidth;
}

int getColumn(
	int index,
	int arrayWidth)
{
	return index % arrayWidth;
}

int main()
{
	unsigned char pMap[] = { 1,1,1,1,0,1,0,1,0,1,1,1 };

	//	1 1 1 1
	//	0 1 0 1
	//	0 1 1 1

	int pOutBuffer[12];

	FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    return 0;
}
