#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct CDLL_Node
{
	int data;
	CDLL_Node* Next;
	CDLL_Node* Previous;
}CDLL_Node;

typedef struct CDLL
{
	CDLL_Node* Head;
}CDLL;

CDLL* CDLL_Init()
{
	CDLL* list = (CDLL*)malloc(sizeof(CDLL));
	if (list == NULL) return NULL;
	list->Head = NULL;

	return list;
}

void CDLL_AddData(CDLL* list, int i)
{
	CDLL_Node* new_node = (CDLL_Node*)malloc(sizeof(CDLL_Node));
	if (new_node == NULL) return;

	new_node->data = i;

	if (list->Head == NULL)
	{
		list->Head = new_node;
		new_node->Previous = new_node;
		new_node->Next = new_node;
		return;
	}

	CDLL_Node* current_node = list->Head->Previous;

	new_node->Previous = current_node;
	new_node->Next = list->Head;
	current_node->Next = new_node;
	list->Head->Previous = new_node;
	return;
}

void CDLL_ViewAllData(CDLL* list)
{
	if (list->Head == NULL) return;

	CDLL_Node* current_node = list->Head;

	do
	{
		printf("%d\n", current_node->data);
		current_node = current_node->Next;
	} while (current_node != list->Head);

	return;
}

void CDLL_Sample()
{
	CDLL* list = CDLL_Init();
	for (int i = 0; i < 10; i++)
	{
		CDLL_AddData(list, i);
	}
	CDLL_ViewAllData(list);

	return;
}