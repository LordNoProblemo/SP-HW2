/*
 * main.c
 *
 *  Created on: Dec 17, 2016
 *      Author: Asaf
 */

#include "main_aux.h"
#include <stdlib.h>

int main()
{
	// Collect input from user
	SPPoint **points = NULL, *q = NULL;
	int n, d, k;
	scanf("%d %d %d", &n, &d, &k);
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

	SPBPQueue* queue = createQueueFromPoints(points, n, q);
	printIndices(queue, k);
	spBPQueueDestroy(queue);
	spPointDestroy(q);
	destroyPoints(points, n);
}
