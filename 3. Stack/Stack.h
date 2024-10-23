#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct StackNode {
    DataBox* data;
    struct StackNode* next;  // ���� ��带 ����Ű�� ������
} StackNode;

typedef struct Stack {
    StackNode* top;  // ������ ���� ���� �ִ� ���
    int size;
} Stack;

Stack* Stack_Init() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->top = NULL;  // �ʱ�ȭ �� top�� NULL
    stack->size = 0;
    return stack;
}

int Stack_Empty(Stack* stack) {
    return stack->top == NULL;
}

void Stack_Push(Stack* stack, DataBox* data) {
    if (stack == NULL) return;

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) return;

    newNode->data = data;
    newNode->next = stack->top;  // �� ����� next�� ���� top�� ����Ŵ
    stack->top = newNode;  // top�� �� ��带 ����Ű�� ����
    stack->size++;
}

DataBox* Stack_Pop(Stack* stack) {
    if (Stack_Empty(stack)) return NULL;

    StackNode* temp = stack->top;  // ������ ��� �ӽ� ����
    DataBox* data = temp->data;
    stack->top = stack->top->next;  // top�� ���� ��带 ����Ű�� ����
    free(temp);  // ������ ��� �޸� ����
    stack->size--;

    return data;
}

void Stack_Destroy(Stack* stack) {
    while (!Stack_Empty(stack)) {
        Stack_Pop(stack);
    }
    free(stack);
}

void Stack_View(Stack* stack) {
    if (stack == NULL || stack->top == NULL) return;

    StackNode* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data->i);  // DataBox�� �ʵ� ����
        current = current->next;
    }
    printf("\n");
}

void Stack_Sample() {
    printf("���� ���� �� ������ �߰�\n");
    Stack* stack = Stack_Init();
    DataBox* data;

    // ���ÿ� ������ �߰�
    for (int i = 60; i > 0; i -= 3) {
        data = MakeData(i);  // MakeData�� ������� DataBox ���� �Լ�
        Stack_Push(stack, data);
    }
    Stack_View(stack);

    printf("������ 10�� ���� �� �� 10�� ������ ���\n");
    for (int i = 0; i < 10; i++) {
        data = Stack_Pop(stack);
        if (data != NULL) {
            printf("%d ", data->i);
            DestroyData(data);  // data�� �����ϴ� �Լ�
        }
    }
    printf("\n");
    Stack_Destroy(stack);

    printf("���� ���� �� ���� �ʱ�ȭ\n");
    stack = Stack_Init();
    for (int i = 100; i > 0; i -= 6) {
        data = MakeData(i);
        Stack_Push(stack, data);
    }
    Stack_View(stack);
    Stack_Destroy(stack);
}
