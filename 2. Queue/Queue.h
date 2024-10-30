#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct QueueNode
{
	DataBox* Data;
	QueueNode* Next;
}QueueNode;

typedef struct Queue
{
	QueueNode* Head;
	QueueNode* Tail;
	unsigned int Size;
}Queue;

Queue* queueInit()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL)
	{
		return NULL;
	}
	q->Head = NULL;
	q->Tail = NULL;
	q->Size = 0;

	return q;
}

void queueAdd(Queue* q, DataBox* data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL)
	{
		return;
	}

	newNode->Next = NULL;
	newNode->Data = data;

	if (q->Head == NULL)
	{
		q->Head = newNode;
		q->Tail = newNode;
	}
	else
	{
		q->Tail->Next = newNode;
		q->Tail = newNode;
	}

	++(q->Size);
	return;
}

DataBox* queuePop(Queue* q)
{
	if (q == NULL || q->Head == NULL)
	{
		return NULL;
	}

	QueueNode* head = q->Head;
	DataBox* data = q->Head->Data;

	q->Head = head->Next;
	free(head);
	--(q->Size);

	return data;
}

DataBox* queuePick(Queue* q)
{
	if (q == NULL || q->Head == NULL)
	{
		return NULL;
	}

	return q->Head->Data;
}

void queueDestroy(Queue* q)
{
	if (q == NULL)
	{
		return;
	}

	while (q->Head != NULL && q->Size == 0)
	{
		queuePop(q);
	}

	printf("Completed destroy\n");
	return;
}


void queueSample()
{
	printf("큐 생성 후 0부터 9까지 삽입\n");
	Queue* q = queueInit();
	for (int i = 0; i < 10; ++i)
	{
		DataBox* data = MakeData(i);
		queueAdd(q, data);
	}

	for (int i = 0; i < 3; ++i)
	{
		printf("%d: %d\n", i, queuePick(q)->i);
	}

	for (int i = 0; i < 10; ++i)
	{
		DataBox* data = queuePop(q);
		printf("%d\t", data->i);
		free(data);
	}
	queueDestroy(q);
}