#include "main_aux.h"
#include <stdio.h>
#include <stdlib.h>

int getDataFromUser(SPPoint** points, SPPoint* q, int* k)
{
	int n, d;
	scanf("%d %d %d", &n, &d, k);
	double * data = (double *) malloc(d * sizeof(double));
	points = (SPPoint **) malloc(n * sizeof(SPPoint*));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < d; j++)
			scanf("%lf", &data[j]);
		points[i] = spPointCreate(data, d, i + 1);
	}
	for (int j = 0; j < d; j++)
		scanf("%lf", &data[j]);
	q = spPointCreate(data, d, 3316);
	free(data);

	return n;
}

SPBPQueue* createQueueFromPoints(SPPoint** points, int n, SPPoint* q)
{
	SPBPQueue* queue = spBPQueueCreate(n);
	for (int i = 0; i < n; i++)
	{
		int dist = spPointL2SquaredDistance(points[i], q);
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
