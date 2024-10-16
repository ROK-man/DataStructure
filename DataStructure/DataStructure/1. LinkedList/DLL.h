#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct DLL_Node
{
	int data;
	DLL_Node* Next;
	DLL_Node* Previous;
}DLL_Node;

typedef struct DLL
{
	DLL_Node* Head;
}DLL;

DLL* DLL_Init()
{
	DLL* list = (DLL*)malloc(sizeof(DLL));
	if (list == NULL) return NULL;

	list->Head = NULL;

	return list;
}

void DLL_AddData(DLL* list, int i)
{
	DLL_Node* new_node = (DLL_Node*)malloc(sizeof(DLL_Node));
	if (new_node == NULL) return;

	new_node->data = i;

	if (list->Head == NULL)
	{
		list->Head = new_node;
		new_node->Previous = NULL;
		new_node->Next = NULL;
		return;
	}

	DLL_Node* current_node = list->Head;

	while (current_node->Next != NULL)
	{
		current_node = current_node->Next;
	}
	new_node->Previous = current_node;
	new_node->Next = NULL;
	current_node->Next = new_node;

	return;
}

void DLL_ViewAllData(DLL* list)
{
	if (list->Head == NULL) return;

	DLL_Node* current_node = list->Head;

	while (current_node != NULL)
	{
		printf("%d\n", current_node->data);
		current_node = current_node->Next;
	}
	return;
}

void DLL_Sample()
{
	DLL* list = DLL_Init();
	for (int i = 0; i < 10; i++)
	{
		DLL_AddData(list, i);
	}
	DLL_ViewAllData(list);

	return;
}