#include "stdafx.h"
#include "pathfinding.cpp"

int main()
{
	pathfinding *pf = new pathfinding();

	//given examples

	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };

	int pOutBuffer[12];

	int result = pf->FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	/*unsigned char pMap[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };

	int pOutBuffer[7];

	int result = pf->FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);*/

	//thread safety demo

	/*unsigned char pMap[] = {
		1,1,1,0,1,1,
		1,1,1,0,1,1,
		1,0,1,1,1,1,
		1,1,1,0,0,1,
		1,1,1,1,0,1,
		1,1,1,0,1,1
	};

	int pOutBuffer[24];

	thread t1 = pf->pathfindingThread(4, 5, 0, 3, ref(pMap), 6, 6, ref(pOutBuffer), 24);
	thread t2 = pf->pathfindingThread(0, 3, 4, 5, ref(pMap), 6, 6, ref(pOutBuffer), 24); //reversal of t1
	thread t3 = pf->pathfindingThread(0, 3, 3, 5, ref(pMap), 6, 6, ref(pOutBuffer), 24); //no path, won't write to buffer/console
	thread t4 = pf->pathfindingThread(2, 0, 2, 4, ref(pMap), 6, 6, ref(pOutBuffer), 24); //straight line down, 8 14 20 26

	t1.join();
	t2.join();
	t3.join();
	t4.join();*/

	return 0;
}