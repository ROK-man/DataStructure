#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
	int data;
	Node* Next;
}Node;

typedef struct SLL 
{
	Node* Head;
}SLL;

SLL* SLL_Init()
{
	SLL* list = (SLL*)malloc(sizeof(SLL));
	if (list == NULL) return NULL;

	list->Head = NULL;

	return list;
}

void SLL_AddData(SLL* list, int i)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) return;

	new_node->data = i;
	new_node->Next = NULL;

	if (list->Head == NULL)
	{
		list->Head = new_node;
	}
	else
	{
		Node* current_node = list->Head;
		while (current_node->Next != NULL)
		{
			current_node = current_node->Next;
		}
		current_node->Next = new_node;
	}
	return;
}

void SLL_ViewAllData(SLL* list)
{
	if (list->Head == NULL)
	{
		return;
	}

	Node* current_node = list->Head;

	while (current_node != NULL)
	{
		printf("%d\n", current_node->data);
		current_node = current_node->Next;
	}
	return;
}

void SLL_Sample()
{
	SLL* list = SLL_Init();
	
	for (int i = 0; i < 100; i++)
	{
		SLL_AddData(list, i);
	}
	SLL_ViewAllData(list);

	return;
}