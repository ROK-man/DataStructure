#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct SLL_Node 
{
	DataBox* Data;
	SLL_Node* Next;
}SLL_Node;

typedef struct SLL 
{
	SLL_Node* Head;
}SLL;

SLL* SLL_Init()
{
	SLL* list = (SLL*)malloc(sizeof(SLL));
	if (list == NULL) return NULL;

	list->Head = NULL;

	return list;
}

void SLL_AddData(SLL* list, DataBox* data)
{
	SLL_Node* new_node = (SLL_Node*)malloc(sizeof(SLL_Node));
	if (new_node == NULL) return;

	new_node->Data = data;
	new_node->Next = NULL;

	if (list->Head == NULL)
	{
		list->Head = new_node;
	}
	else
	{
		SLL_Node* current_node = list->Head;
		while (current_node->Next != NULL)
		{
			current_node = current_node->Next;
		}
		current_node->Next = new_node;
	}
	return;
}

SLL_Node* SLL_GetStartNode(SLL* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	return list->Head;
}

SLL_Node* SLL_NextNode(SLL_Node* node)
{
	if (node == NULL)
	{
		return NULL;
	}

	return node->Next;
}

void SLL_RemoveNode(SLL* list, SLL_Node* node)
{
	if (list == NULL || node == NULL)
	{
		return;
	}

	SLL_Node* currentNode = list->Head;
	if (currentNode == node)
	{
		free(currentNode);
		list->Head = NULL;
		return;
	}

	while (currentNode)
	{
		if (currentNode->Next == node)
		{
			SLL_Node* remov = currentNode->Next;
			currentNode->Next = remov->Next;
			free(remov);
			return;
		}
		currentNode = currentNode->Next;
	}

	return;
}