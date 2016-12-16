#include<stdio.h>
#include "SPBPriorityQueue.h"
//Define the struct of queue
struct sp_bp_queue_t{
	int capacity; // The capacity of the queue
	int size; //Amount of elements in queue
	//Elements indexes are MinIndex<=i<MinIndex+size<=capacity
	int MinIndex;//The index of the element with lowest value in the elements array, -1<=> queue is empty
	BPQueueElement* elements; //The array of Elements
};

SPBPQueue* spBPQueueCreate(int maxSize)
{
	SPBPQueue* ret = (SPBPQueue*)malloc(sizeof(SPBPQueue));
	ret->MinIndex = -1;//Queue is empty
	ret->size = 0;//Queue is empty
	ret->capacity = maxSize;
	ret->elements = (BPQueueElement*)malloc(sizeof(BPQueueElement)*maxSize);//Initialize memory for the array with size maxSize
	return ret;
}

/**
 * Returns the index of element with max value in queue in the array
 * @param source - the queue
 * @assert source!=NULL and source isn't empty
 */
int MaxIndex(SPBPQueue* source)
{
	return source->MinIndex + source->size-1;
}

SPBPQueue* spBPQueueCopy(SPBPQueue* source)
{
	SPBPQueue* ret = (SPBPQueue*)malloc(sizeof(SPBPQueue));//Initialize memory for the new Queue
	ret->MinIndex = source->MinIndex;
	ret->size = source->size;
	ret->capacity = source->capacity;
	ret->elements = (BPQueueElement*)malloc(sizeof(source->elements));//Initialize memory for the elements
	// Updates the elements of ret to be the same as those of source
	int i = 0;

	for(; i < ret->size ; i++)
	{
		ret->elements[i+ret->MinIndex] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
		ret->elements[i+ret->MinIndex]->index = source->elements[i+ret->MinIndex]->index;
		ret->elements[i+ret->MinIndex]->value = source->elements[i+ret->MinIndex]->value;
	}
	return ret;
}

int spBPQueueSize(SPBPQueue* source)
{
	return source->size;
}

int spBPQueueGetMaxSize(SPBPQueue* source)
{
	return source->capacity;
}

bool spBPQueueIsEmpty(SPBPQueue* source)
{
	return source->size == 0;
}

bool spBPQueueIsFull(SPBPQueue* source)
{
	return source->size == source->capacity;
}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue* source)
{
	if(source == NULL || *source == NULL)
		return SP_BPQUEUE_INVALID_ARGUMENT;
	if(spBPQueueIsEmpty(source))
		return SP_BPQUEUE_EMPTY;
	BPQueueElement* lowest = source->elements[source->MinIndex];
	free(lowest);
	source->elements[source->MinIndex] = NULL;
	source->size--;
	if(source->size==0)
		source->MinIndex = -1;
	else
		source->MinIndex++;
	return SP_BPQUEUE_SUCCESS;

}

double spBPQueueMinValue(SPBPQueue* source)
{
	return source->elements[source->MinIndex]->value;
}

double spBPQueueMaxValue(SPBPQueue* source)
{
	return source->elements[MaxIndex(source)]->value;
}

SP_BPQUEUE_MSG spBPQueuePeekLast(SPBPQueue* source, BPQueueElement* res)
{
	if(source == NULL || *source == NULL)
		return SP_BPQUEUE_INVALID_ARGUMENT;
	if(spBPQueueIsEmpty(source))
		return SP_BPQUEUE_EMPTY;
	res = (BPQueueElement*)malloc(sizeof(BPQueueElement));
	res->index = source->elements[MaxIndex(source)]->index;
	res->value = source->elements[MaxIndex(source)]->value;
	return SP_BPQUEUE_SUCCESS;
}

SP_BPQUEUE_MSG spBPQueuePeek(SPBPQueue* source, BPQueueElement* res)
{
	if(source == NULL || *source == NULL)
		return SP_BPQUEUE_INVALID_ARGUMENT;
	if(spBPQueueIsEmpty(source))
		return SP_BPQUEUE_EMPTY;
	res = (BPQueueElement*)malloc(sizeof(BPQueueElement));
	res->index = source->elements[source->MinIndex]->index;
	res->value = source->elements[source->MinIndex]->value;
	return SP_BPQUEUE_SUCCESS;
}

void spBPQueueClear(SPBPQueue* source)
{
	int i = 0;
	for(; i < source->capacity ; i++)
	{
		if(source->elements[i] != NULL && *(source->elements[i]) != NULL)
		{
			free(source->elements[i]);
			source->elements[i] = NULL;
		}
	}
}

void spBPQueueDestroy(SPBPQueue* source)
{
	int i = 0;
	for(; i < source->capacity ; i++)
	{
		if(source->elements[i] != NULL && *(source->elements[i]) != NULL)
		{
			free(source->elements[i]);
		}
	}
	free(source->elements);
	free(source->MinIndex);
	free(source->size);
	free(source->capacity);
	free(source);
}

/*
 * Returns the place in array of the new element according to value
 * @param array - the array of elements
 * @assert array is not empty and array!=null
 * @param start - the index from which we start searching
 * @param end - the index on which we end searching
 * @assert start<=end
 * @param value - the value of new element
 * @return
 * The index i for which is the place of the new element
 */
int findPlace(BPQueueElement* array, int start, int end, double value)
{
	if(value <= array[start]->value)
		return start-1;
	if(value >= array[end]->value)
		return end + 1;
	int lowBound = start;
	int highBound = end;
	while(!((array[(lowBound + highBound) / 2 - 1]->value) < value <= (array[(lowBound + highBound) / 2]->value)))
	{
		if(value > (array[(lowBound + highBound) / 2]->value))
			lowBound = (lowBound + highBound) / 2;
		else
			highBound = (lowBound + highBound) / 2;
	}
	return (lowBound + highBound) / 2;
}


SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue* source, int index, double value)
{
	if(source == NULL || *source == NULL)
			return SP_BPQUEUE_INVALID_ARGUMENT;

	if(spBPQueueIsEmpty(source))
	{
		source->MinIndex = 0;
		source->size = 1;
		source->elements[0] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
		source->elements[0]->index = index;
		source->elements[0]->value = value;
		return SP_BPQUEUE_SUCCESS;
	}
	int insertIndex = findPlace(source->elements,source->MinIndex,MaxIndex(source),value);
	if(insertIndex > MaxIndex(source))
	{
		if(spBPQueueIsFull(source))
			return SP_BPQUEUE_FULL;
		if(MaxIndex(source) == source->capacity - 1)
		{
			for(int i = source->MinIndex ; i <= source->capacity-1 ; i++)
			{
				if(i == 0)
					return SP_BPQUEUE_OUT_OF_MEMORY;
				source->elements[i - 1] = source->elements[i];
			}
			source->MinIndex--;
			source->size++;
			source->elements[source->capacity - 1] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
			source->elements[source->capacity-1]->index = index;
			source->elements[source->capacity-1]->value = value;
		}
		else
		{
			source->elements[insertIndex] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
			source->elements[insertIndex]->index = index;
			source->elements[insertIndex]->value = value;
		}
		return SP_BPQUEUE_SUCCESS;
	}

	if(insertIndex < source->MinIndex)
	{
		if(source->MinIndex > 0)
		{
			source->MinIndex--;
			source->elements[insertIndex] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
			source->elements[insertIndex]->index = index;
			source->elements[insertIndex]->value = value;
			source->size++;
		}
		else
		{
			if(spBPQueueIsFull(source))
			{
				free(source->elements[source->capacity - 1]);
				source->size--;
			}
			for(int i = MaxIndex(source) ; i >= 0 ; i++)
			{
				if(i >= source->capacity)
					return SP_BPQUEUE_OUT_OF_MEMORY;
				source->elements[i + 1] = source->elements[i];
			}
			source->elements[0] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
			source->elements[0]->index = index;
			source->elements[0]->value = value;
			source->size++;
		}
		return SP_BPQUEUE_SUCCESS;
	}
	if(spBPQueueIsFull(source))
	{
		free(source->elements[source->capacity - 1]);
		source->size--;
	}
	if(MaxIndex(source) < source->capacity - 1)
	{
		for(int i = MaxIndex(source) ; i >= insertIndex ; i++)
		{
			if(i >= source->capacity)
				return SP_BPQUEUE_OUT_OF_MEMORY;
			source->elements[i + 1] = source->elements[i];
		}
	}
	else
	{
		for(int i = source->MinIndex ; i <= insertIndex ; i++)
		{
			if(i==0)
				return SP_BPQUEUE_OUT_OF_MEMORY;
			source->elements[i - 1] = source->elements[i];
		}
		source->MinIndex--;
	}
	source->size++;
	source->elements[insertIndex] = (BPQueueElement*)malloc(sizeof(BPQueueElement));
	source->elements[insertIndex]->index = index;
	source->elements[insertIndex]->value = value;
	return SP_BPQUEUE_SUCCESS;
}



