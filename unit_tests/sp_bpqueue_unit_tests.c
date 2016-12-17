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
	ASSERT_TRUE(spBPQueueMaxValue(q1)==4);
	SPBPQueue* q2 = spBPQueueCopy(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q2)==3);
	ASSERT_TRUE(spBPQueueSize(q2)==3);
	ASSERT_TRUE(spBPQueueMinValue(q2)==4);
	ASSERT_TRUE(spBPQueueMaxValue(q2)==4);
	spBPQueueDequeue(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1)==3);
	ASSERT_TRUE(spBPQueueSize(q1)==3);
	ASSERT_TRUE(spBPQueueMinValue(q1)==5);
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	return true;
}
int main()
{
	RUN_TEST(testBPQCopy);
	return 0;
}
