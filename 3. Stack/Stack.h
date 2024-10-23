#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct StackNode {
    DataBox* data;
    struct StackNode* next;  // 다음 노드를 가리키는 포인터
} StackNode;

typedef struct Stack {
    StackNode* top;  // 스택의 가장 위에 있는 노드
    int size;
} Stack;

Stack* Stack_Init() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) return NULL;

    stack->top = NULL;  // 초기화 시 top은 NULL
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
    newNode->next = stack->top;  // 새 노드의 next가 기존 top을 가리킴
    stack->top = newNode;  // top이 새 노드를 가리키게 설정
    stack->size++;
}

DataBox* Stack_Pop(Stack* stack) {
    if (Stack_Empty(stack)) return NULL;

    StackNode* temp = stack->top;  // 삭제할 노드 임시 저장
    DataBox* data = temp->data;
    stack->top = stack->top->next;  // top이 다음 노드를 가리키게 변경
    free(temp);  // 삭제할 노드 메모리 해제
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
        printf("%d ", current->data->i);  // DataBox의 필드 가정
        current = current->next;
    }
    printf("\n");
}

void Stack_Sample() {
    printf("스택 생성 및 데이터 추가\n");
    Stack* stack = Stack_Init();
    DataBox* data;

    // 스택에 데이터 추가
    for (int i = 60; i > 0; i -= 3) {
        data = MakeData(i);  // MakeData는 사용자의 DataBox 생성 함수
        Stack_Push(stack, data);
    }
    Stack_View(stack);

    printf("데이터 10개 꺼낸 뒤 그 10개 데이터 출력\n");
    for (int i = 0; i < 10; i++) {
        data = Stack_Pop(stack);
        if (data != NULL) {
            printf("%d ", data->i);
            DestroyData(data);  // data를 해제하는 함수
        }
    }
    printf("\n");
    Stack_Destroy(stack);

    printf("스택 삭제 후 새로 초기화\n");
    stack = Stack_Init();
    for (int i = 100; i > 0; i -= 6) {
        data = MakeData(i);
        Stack_Push(stack, data);
    }
    Stack_View(stack);
    Stack_Destroy(stack);
}
