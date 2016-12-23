#include "main_aux.h"
#include <stdio.h>
#include <stdlib.h>

SPBPQueue* createQueueFromPoints(SPPoint** points, int n, SPPoint* q)
{
	SPBPQueue* queue = spBPQueueCreate(n);
	for (int i = 0; i < n; i++)
	{
		double dist = spPointL2SquaredDistance(points[i], q);
		int idx = spPointGetIndex(points[i]);
		spBPQueueEnqueue(queue, idx, dist);
	}
	return queue;
}

void printIndices(SPBPQueue* queue, int k)
{
	BPQueueElement e;
	spBPQueuePeek(queue, &e);
	printf("%d", e.index);
	for (int i = 1; i < k; i++)
	{
		spBPQueueDequeue(queue);
		spBPQueuePeek(queue, &e);
		printf(", %d", e.index);

	}
	printf("\n");
}

void destroyPoints(SPPoint** points, int n)
{
	for(int i = 0; i < n; i++)
		spPointDestroy(points[i]);
	free(points);
}
