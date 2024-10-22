#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct heapNode
{
	DataBox* Data;
	int priority;
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

	if (heap->Heap == NULL)
	{
		free(heap);
		return NULL;
	}

	heap->Capacity = 128;
	heap->UsedSize = 0;

	return heap;
}

void minHeap_SwitchNode(minHeap* heap, int idx1, int idx2)
{
	heapNode* temp = heap->Heap[idx1];
	heap->Heap[idx1] = heap->Heap[idx2];
	heap->Heap[idx2] = temp;
}

void minHeap_AddData(minHeap* heap, DataBox* data, int priority)
{
	if (heap == NULL) return;
	if (heap->Heap == NULL) return;

	heapNode* newNode = (heapNode*)malloc(sizeof(heapNode));
	if (newNode == NULL) return;

	if (heap->UsedSize >= heap->Capacity)
	{
		heapNode** temp = (heapNode**)realloc(heap->Heap, sizeof(heapNode*) * heap->Capacity * 2);
		if (temp != NULL)
		{
			heap->Heap = temp;
		}
		else
		{
			free(newNode);
			return;
		}

		heap->Capacity *= 2;
	}

	newNode->Data = data;
	newNode->priority = priority;

	int current_index = heap->UsedSize;
	heap->Heap[current_index] = newNode;
	int parent_index = (current_index - 1) / 2;

	while (heap->Heap[parent_index]->priority > heap->Heap[current_index]->priority && parent_index >= 0)
	{
		minHeap_SwitchNode(heap, parent_index, current_index);

		current_index = parent_index;
		parent_index = (parent_index-1)/2;
	}

	heap->UsedSize += 1;
	return;
}


DataBox* minHeap_Pop(minHeap* heap)
{
	if (heap == NULL || heap->Heap == NULL || heap->UsedSize <= 0) return NULL;

	DataBox* data = heap->Heap[0]->Data;

	free(heap->Heap[0]);
	heap->Heap[0] = NULL;
	if (heap->UsedSize == 0)
	{
		return data;
	}
	heap->Heap[0] = heap->Heap[heap->UsedSize - 1];
	heap->UsedSize--;
	if (heap->Heap[0] == NULL) return data;

	int current, child1, child2;
	current = 0;
	child1 = current * 2 + 1;
	child2 = current * 2 + 2;
	int target_child;
	while (child1 <= heap->UsedSize - 1)
	{
		if (child2 > heap->UsedSize - 1)
		{
			if (heap->Heap[child1]->priority < heap->Heap[current]->priority)
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
			if (heap->Heap[child1]->priority < heap->Heap[child2]->priority)
			{
				target_child = child1;
			}
			else
			{
				target_child = child2;
			}

			if (heap->Heap[target_child]->priority >= heap->Heap[current]->priority)
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
	for (int i = 0; i < heap->UsedSize; i++)
	{
		printf("%d ", heap->Heap[i]->priority);
	}
	printf("\n");
}

void minHeap_Destroy(minHeap* heap)
{
	if (heap == NULL || heap->Heap == NULL) return;
	while (heap->UsedSize > 0)
	{
		minHeap_Pop(heap);
	}
	free(heap->Heap);
	free(heap);
	return;
}

// 힙 최대크기 줄이기
void shrinkHeap(minHeap* heap)
{
	if (heap->UsedSize < heap->Capacity / 4)
	{
		heap->Capacity /= 2;
		heapNode** temp = (heapNode**)realloc(heap->Heap, sizeof(heapNode*) * heap->Capacity);
		if (temp != NULL) 
		{
			heap->Heap = temp;
			return;
		}
	}
}


// Pop 없이 숫자만 확인
DataBox* minHeap_Peek(minHeap* heap)
{
	if (heap == NULL || heap->Heap == NULL || heap->UsedSize == 0) return NULL;
	return heap->Heap[0]->Data;
}


void minHeap_Sample()
{
	printf("최소힙 생성 및 데이터추가\n");
	minHeap* heap = minHeap_Init();
	DataBox* data;
	for (int i = 60; i >0; i-=3)
	{
		data = MakeData(i);
		minHeap_AddData(heap, data, data->i);
	}
	minHeap_View(heap);
	printf("데이터 10개 뽑은 뒤 그 10개 데이터 출력\n");
	for (int i = 0; i < 10; i++)
	{
		data = minHeap_Pop(heap);
		printf("%d ", data->i);
		DestroyData(data);
	}
	printf("\n");
	minHeap_Destroy(heap);

	printf("힙 삭제 후 새로 초기화\n");
	heap = minHeap_Init();
	for (int i = 100; i > 0; i -= 6)
	{
		data = MakeData(i);
		minHeap_AddData(heap, data, data->i);
	}
	minHeap_View(heap);
}