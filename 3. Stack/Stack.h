#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct StackNode
{
	DataBox* Data;
	StackNode* Next;
}StackNode;

typedef struct Stack
{
	unsigned int Size;
	StackNode* Head;
}Stack;

Stack* stackInit()
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (s == NULL)
	{
		return NULL;
	}

	s->Size = 0;
	s->Head = NULL;

	return s;
}

void stackAdd(Stack* s, DataBox* data)
{
	if (s == NULL)
	{
		return;
	}

	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	newNode->Data = data;
	newNode->Next = NULL;

	if (s->Head == NULL)
	{
		s->Head = newNode;
	}
	else
	{
		newNode->Next = s->Head;
		s->Head = newNode;
	}

	++(s->Size);

	return;	
}

DataBox* stackPop(Stack* s)
{
	if (s == NULL || s->Head == NULL || s->Size == 0)
	{
		return NULL;
	}

	StackNode* node = s->Head;
	DataBox* data = node->Data;

	s->Head = s->Head->Next;
	--(s->Size);

	free(node);

	return data;
}

DataBox* stackPick(Stack* s)
{
	if (s == NULL || s->Head == NULL || s->Size == 0)
	{
		return NULL;
	}

	return s->Head->Data;
}

void stackDestroy(Stack* s)
{
	if (s == NULL || s->Head == NULL || s->Size == 0)
	{
		return;
	}

	while (s->Head != NULL && s->Size != 0)
	{
		stackPop(s);
	}

	printf("completed\n");
	return;
}

void stackSample()
{
	printf("큐 생성 후 0부터 9까지 삽입\n");
	Stack* s = stackInit();
	for (int i = 0; i < 10; ++i)
	{
		DataBox* data = MakeData(i);
		stackAdd(s, data);
	}

	for (int i = 0; i < 3; ++i)
	{
		printf("%d: %d\n", i, stackPick(s)->i);
	}

	for (int i = 0; i < 10; ++i)
	{
		DataBox* data = stackPop(s);
		printf("%d\t", data->i);
		free(data);
	}	
	printf("\n");
	
	for (int i = 0; i < 10; ++i)
	{
		DataBox* data = MakeData(i);
		stackAdd(s, data);
	}
	stackDestroy(s);
}