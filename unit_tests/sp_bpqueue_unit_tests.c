#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>


bool testBPQCopy()
{
	int indices[3] = {1,2,3};
	int values [3] = {6,5,4};
	SPBPQueue* q1 = spBPQueueCreate(3);
	ASSERT_TRUE(spBPQueueSize(q1)==0);
	for(int i = 0; i < 3; i++)
		spBPQueueEnqueue(q1, indices[i], values[i]);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1)==3);
	ASSERT_TRUE(spBPQueueSize(q1)==3);
	ASSERT_TRUE(spBPQueueMinValue(q1)==4);
	ASSERT_TRUE(spBPQueueMaxValue(q1)==6);
	SPBPQueue* q2 = spBPQueueCopy(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q2)==3);
	ASSERT_TRUE(spBPQueueSize(q2)==3);
	ASSERT_TRUE(spBPQueueMinValue(q2)==4);
	ASSERT_TRUE(spBPQueueMaxValue(q2)==6);
	spBPQueueDequeue(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1)==3);
	ASSERT_TRUE(spBPQueueSize(q1)==2);
	ASSERT_TRUE(spBPQueueMinValue(q1)==5);
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	return true;
}

bool testBPQClear()
{
    SPBPQueue* cleared = spBPQueueCreate(5);
    SPBPQueue* notCleared = spBPQueueCreate(5);
    ASSERT_TRUE(spBPQueueGetMaxSize(notCleared) == spBPQueueGetMaxSize(cleared));
    spBPQueueEnqueue(notCleared,1,42);
    spBPQueueEnqueue(notCleared,3,43);
    spBPQueueEnqueue(notCleared,6,42.5);
    spBPQueueEnqueue(notCleared,-10,0);
    ASSERT_TRUE(spBPQueueSize(notCleared) == 4);
    ASSERT_TRUE(spBPQueueMaxValue(notCleared) == 43);
    ASSERT_TRUE(spBPQueueMinValue(notCleared) == 0);
    spBPQueueDequeue(notCleared);
    ASSERT_TRUE(spBPQueueMinValue(notCleared) == 42);
    spBPQueueClear(notCleared);
    ASSERT_TRUE(spBPQueueIsEmpty(notCleared));
    spBPQueueDestroy(cleared);
    spBPQueueDestroy(notCleared);
    return true;

}
int main()
{
	RUN_TEST(testBPQCopy);
	RUN_TEST(testBPQClear);
	return 0;
}
