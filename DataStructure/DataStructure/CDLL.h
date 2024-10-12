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
	int Size;
}CDLL;

// ȯ�� ���� ���� ����Ʈ �ʱ�ȭ
CDLL* CDLL_Init()
{
	CDLL* list = (CDLL*)malloc(sizeof(CDLL));
	if (list == NULL) return NULL;
	list->Head = NULL;
	list->Size = 0;

	return list;
}

// ������ �߰�
void CDLL_AddData(CDLL* list, int i)
{
	CDLL_Node* new_node = (CDLL_Node*)malloc(sizeof(CDLL_Node));
	if (new_node == NULL) return;

	new_node->data = i;
	list->Size++;

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


// ��ü ���
void CDLL_ViewAllData(CDLL* list)
{
	if (list->Head == NULL) return;

	CDLL_Node* current_node = list->Head;

	do
	{
		printf("%d -> ", current_node->data);
		current_node = current_node->Next;
	} while (current_node != list->Head);
	printf("\n");

	return;
}

// ã�� ������ �ε��� ��ȯ
int CDLL_FindData(CDLL* list, int data)
{
	if (list->Head == NULL) return -1;

	CDLL_Node* current_node = list->Head;

	int index = 0;
	do
	{
		if (current_node->data == data)
		{
			return index;
		}
		index++;
		current_node = current_node->Next;
	} while (current_node != list->Head);

	return -1;
}
int CDLL_GetSize(CDLL* list)
{
	if (list == NULL || list->Head == NULL)
	{
		return -1;
	}
	return list->Size;
}

// Ư�� �����Ͱ� ã�Ƽ� ���� �� �ε��� ��ȯ
int CDLL_RemoveData(CDLL* list, int data)
{
	if (list->Head == NULL) return -1;
	
	CDLL_Node* current_node = list->Head;

	int count = 0;
	do
	{
		if (current_node->data == data)
		{
			if (list->Size == 1)
			{
				free(current_node);
				list->Head = NULL;
				list->Size = 0;
				return 0;
			}
			if (current_node == list->Head)
			{
				list->Head = current_node->Next;
				list->Head->Previous = current_node->Previous;
				current_node->Previous->Next = list->Head;

				list->Size--;
				free(current_node);
				return count;
			}
			CDLL_Node* previous_node = current_node->Previous;
			CDLL_Node* next_node = current_node->Next;

			previous_node->Next = next_node;
			next_node->Previous = previous_node;

			free(current_node);
			list->Size--;

			return count;
		}
		count++;
		current_node = current_node->Next;
	} while (current_node != list->Head);

	return -1;
}



// ���� �ڵ�
void CDLL_Sample()
{
	printf("CDLL SampleCode\n");
	CDLL* list = CDLL_Init();

	printf("����Ʈ�� 0~9 �� �߰�\n");
	for (int i = 0; i < 10; i++)
	{
		CDLL_AddData(list, i);
	}
	CDLL_ViewAllData(list);

	printf("����Ʈ�� 0~9�� ����\n");
	for (int i = 0; i < 10; i++)
	{
		CDLL_RemoveData(list, i);
	}
	CDLL_ViewAllData(list);

	printf("����Ʈ�� 5~20 �� �߰�\n");
	for (int i = 5; i < 21; i++)
	{
		CDLL_AddData(list, i);
	}
	CDLL_ViewAllData(list);
	
	printf("����Ʈ�� 6, 9, 12, 15, 18 �� ����\n");
	for (int i = 6; i < 19; i += 3)
	{
		CDLL_RemoveData(list, i);
	}
	CDLL_ViewAllData(list);

	printf("����Ʈ ũ��\n");
	printf("%d\n", CDLL_GetSize(list));

	return;
}