#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../1. LinkedList/SLL.h"
#include "../DataBox.h"

typedef struct HashTable
{
	SLL** Arr;
	unsigned int Size;
	
}HashTable;

HashTable* hashTableInit(int size)
{
	if (size < 1)
	{
		size = 31;
	}
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));

	if (table == NULL)
	{
		return NULL;
	}
	table->Size = size;
	table->Arr = (SLL**)malloc(sizeof(SLL) * size);
	if (table->Arr == NULL)
	{
		return NULL;
	}
	
	return table;
}

int hashTablehash(char* key)
{
	int value = 0;
	while (*key != '\0')
	{
		value += ((int)(*key) * 31) % 2147483647;
		value %= 2147483647;
	}
	return value;
}

void hashTableAddData(HashTable* table, DataBox* data, char* key)
{
	if (table == NULL || data == NULL)
	{
		return;
	}

	int index = hashTablehash(key) % table->Size;

	SLL_AddData(table->Arr[index], data);

	return;
}

DataBox* hashTableGetData(HashTable* table, char* key)
{
	int index = hashTablehash(key) % table->Size;

	SLL_Node* node = SLL_GetStartNode(table->Arr[index]);

	do
	{
		if (stricmp(node->Data->key, key))
		{
			return node->Data;
		}
	} while ((node = SLL_NextNode(node)));

	return NULL;
}

void hashTableRemoveData(HashTable* table, char* key)
{
	return;
}