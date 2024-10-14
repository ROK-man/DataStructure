#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct heapNode
{
	element Data;
}heapNode;

typedef struct minHeap
{
	heapNode** Heap;
	int Capacity;
	int UsedSize;
}minHeap;

minHeap* minHeap_Init()
{
	minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
	if (heap == NULL)
	{
		heap = (minHeap*)malloc(sizeof(minHeap));
	}
	if (heap == NULL) return NULL;
	
	heap->Heap = (heapNode**)malloc(sizeof(heapNode*) * 128);

	if (heap->Heap == NULL) return NULL;

	heap->Capacity = 128;
	heap->UsedSize = 0;

	return heap;
}

void minHeap_AddData(minHeap* heap, element data)
{
	if (heap == NULL) return;
	if (heap->Heap == NULL) return;

	heapNode* newNode = (heapNode*)malloc(sizeof(heapNode));
	if (newNode == NULL) return;

	if (heap->UsedSize >= heap->Capacity)
	{
		heap->Heap = (heapNode**)realloc(heap->Heap, sizeof(heapNode*) * heap->Capacity * 2);
		if (heap->Heap == NULL)
		{
			free(newNode);
			return;
		}
		heap->Capacity *= 2;
	}

	newNode->Data = data;

	int current_index = heap->UsedSize;
	heap->Heap[current_index] = newNode;
	int parent_index = (current_index - 1) / 2;

	while (heap->Heap[parent_index]->Data > heap->Heap[current_index]->Data && parent_index >= 0)
	{
		heapNode* temp = heap->Heap[parent_index];
		heap->Heap[parent_index] = heap->Heap[current_index];
		heap->Heap[current_index] = temp;

		current_index = parent_index;
		parent_index = (parent_index-1)/2;
	}

	heap->UsedSize += 1;
	return;
}

void minHeap_SwitchNode(minHeap* heap, int idx1, int idx2)
{
	heapNode* temp = heap->Heap[idx1];
	heap->Heap[idx1] = heap->Heap[idx2];
	heap->Heap[idx2] = temp;
}

element minHeap_Pop(minHeap* heap)
{
	if (heap == NULL || heap->Heap == NULL || heap->UsedSize <= 0) return -1;

	element data = heap->Heap[0]->Data;

	heap->Heap[0] = heap->Heap[heap->UsedSize - 1];
	free(heap->Heap[heap->UsedSize - 1]);
	heap->UsedSize--;

	int current, child1, child2;
	current = 0;
	child1 = current * 2 + 1;
	child2 = current * 2 + 2;
	int target_child;
	heapNode* temp;
	while (child1 <= heap->UsedSize - 1)
	{
		if (child2 > heap->UsedSize - 1)
		{
			if (heap->Heap[child1]->Data < heap->Heap[current]->Data)
			{
				target_child = child1;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (heap->Heap[child1]->Data < heap->Heap[child2]->Data)
			{
				target_child = child1;
			}
			else
			{
				target_child = child2;
			}

			if (heap->Heap[target_child]->Data >= heap->Heap[current]->Data)
			{
				break;
			}
		}
		minHeap_SwitchNode(heap, current, target_child);

		current = target_child;
		child1 = current * 2 + 1;
		child2 = current * 2 + 2;
	}
	
	return data;
}

void minHeap_View(minHeap* heap)
{
	if (heap == NULL || heap->Heap == NULL || heap->UsedSize == 0) return;
	for (int i = 1; i < heap->UsedSize; i++)
	{
		printf("%d ", heap->Heap[i]->Data);
	}
	printf("\n");
}


void minHeap_Sample()
{
	minHeap* heap = minHeap_Init();
	for (int i = 10; i >8; i--)
	{
		printf("%d\n", i);
		minHeap_AddData(heap, i);
		minHeap_View(heap);
	}
	//for (int i = 0; i < 10; i++)
	//{
	//printf("%d %d ",  heap->UsedSize, minHeap_Pop(heap));
	//}
}