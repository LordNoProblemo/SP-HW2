/*
 * main_aux.h
 *
 *  Note: Since the only usage of all functions here in main function, we assume that the input in valid
 */

#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_

#include "SPPoint.h"
#include "SPBPriorityQueue.h"


/**
 * Creates BPQ whose indices are the indices of points and values are the distance between points and q
 * @param points - The points to enter to queue
 * @param n - Number of points
 * @param q - The query point used in calculation
 * @return queue which has those elements
 */
SPBPQueue* createQueueFromPoints(SPPoint** points, int n, SPPoint* q);

/**
 * Prints the indices of first k elements in queue and dequeue them
 * @param queue - the queue to print from
 * @param k - number of indices to print
 */
void printIndices(SPBPQueue* queue, int k);

/*
 * Destroys an array of points
 * @param points - an array of points
 * @param n - number of points
 */
void destroyPoints(SPPoint** points, int n);


#endif /* MAIN_AUX_H_ */
