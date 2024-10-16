#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct CDLL_Node
{
	int Data;
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

// ����Ʈ ������� Ȯ��
int CDLL_IsListEmpty(CDLL* list)
{
	if (list->Size == 0)	return 1;
	return 0;
}


// ������ �߰�
void CDLL_AddData(CDLL* list, int i)
{
	CDLL_Node* new_node = (CDLL_Node*)malloc(sizeof(CDLL_Node));
	if (new_node == NULL) return;

	new_node->Data = i;
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
	if (list->Head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	CDLL_Node* current_node = list->Head;

	do
	{
		printf("%d -> ", current_node->Data);
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
		if (current_node->Data == data)
		{
			return index;
		}
		index++;
		current_node = current_node->Next;
	} while (current_node != list->Head);

	return -1;
}

// ����Ʈ ũ�� ��ȯ
int CDLL_GetSize(CDLL* list)
{
	if (list == NULL)
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
		if (current_node->Data == data)
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

// Ư�� �ε����� �ִ� ������ ���� �� �ش� ������ �� ��ȯ, ���н� -1 ��ȯ
int CDLL_RemoveDataAt(CDLL* list, int index)
{
	if (list->Head == NULL)
	{
		return -1;
	}
	if (CDLL_GetSize(list)-1 < index)
	{
		return -1;
	}

	CDLL_Node* current_node = list->Head;

	if (index == 0)
	{
		int data = current_node->Data;

		if (CDLL_GetSize(list) == 1)
		{
			free(current_node);
			list->Head = NULL;
			list->Size = 0;

			return data;
		}

		list->Head = current_node->Next;
		list->Head->Previous = current_node->Previous;
		current_node->Previous->Next = list->Head;

		free(current_node);
		list->Size--;

		return data;
	}
	do
	{
		if (index == 0)
		{
			current_node->Previous->Next = current_node->Next;
			current_node->Next->Previous = current_node->Previous;
			
			int data = current_node->Data;
			free(current_node);
			list->Size--;

			return data;
		}

		index--;
		current_node = current_node->Next;

	} while (current_node != list->Head);

	return -1;
}

// ����Ʈ ����
int CDLL_Destroy(CDLL* list)
{
	if (list == NULL)
	{
		return 0;
	}

	while (CDLL_GetSize(list) > 0)
	{
		CDLL_RemoveDataAt(list, 0);
	}

	if (list->Head == NULL)
	{
		free(list);
		return 1;
	}
	return 0;
}

// ������ 2�� ��ü
int CDLL_SwapData(CDLL* list, int index0, int index1)
{
	if (list->Head == NULL) return 0;
	if (index0 > CDLL_GetSize(list)-1 || index1 > CDLL_GetSize(list)-1) return 0;

	CDLL_Node* node0 = NULL;
	CDLL_Node* node1 = NULL;

	int index = 0;
	int done = 0;
	CDLL_Node* current_node = list->Head;
	do
	{
		if (index == index0)
		{
			node0 = current_node;
			done++;
		}
		if (index == index1)
		{
			node1 = current_node;
			done++;
		}
		if (done == 2)
		{
			break;
		}

		index++;
		current_node = current_node->Next;

	} while (current_node != list->Head);

	if (done != 2) return 0;
	if (node0 == NULL || node1 == NULL) return 0;

	int temp = node0->Data;
	node0->Data = node1->Data;
	node1->Data = temp;

	return 1;
}

// Ư�� �ε����� �ִ� �� ��ü
int CDLL_ChangeData(CDLL* list, int data, int index)
{
	if (CDLL_IsListEmpty(list)) return 0;

	if (index - 1 > CDLL_GetSize(list)) return 0;

	CDLL_Node* current_node = list->Head;
	int i = 0;

	do
	{
		if (i == index)
		{
			current_node->Data = data;
			return 1;
		}

		i++;
		current_node = current_node->Next;

	} while (current_node != list->Head);

	return 0;
}

// ����Ʈ 2�� ��ġ��

// ����Ʈ ��� �ٲٱ�

// ����Ʈ ���� �ٲٱ�

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

	printf("����Ʈ ����\n");
	printf("%d\n", CDLL_Destroy(list));

	printf("����Ʈ �ٽ� ����\n");
	CDLL* list2 = CDLL_Init();

	for (int i = 0; i < 10; i++)
	{
		CDLL_AddData(list2, i);
	}
	CDLL_ViewAllData(list2);

	printf("1�� 3, 5�� 7 ����\n");
	CDLL_SwapData(list2, 1, 3);
	CDLL_SwapData(list2, 5, 7);
	CDLL_ViewAllData(list2);

	printf("4�� �ε����� �ִ� �� 121�� ����\n");
	CDLL_ChangeData(list2, 121, 4);
	CDLL_ViewAllData(list2);

	return;
}