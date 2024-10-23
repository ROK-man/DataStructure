#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct QueueNode {
    DataBox* data;
    struct QueueNode* next;  // 다음 노드를 가리키는 포인터
} QueueNode;

typedef struct Queue {
    QueueNode* front;  // 큐의 가장 앞에 있는 노드
    QueueNode* rear;   // 큐의 가장 뒤에 있는 노드
    int size;
} Queue;

Queue* Queue_Init() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

int Queue_Empty(Queue* queue) {
    return queue->front == NULL;
}

void Queue_Enqueue(Queue* queue, DataBox* data) {
    if (queue == NULL) return;

    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) return;

    newNode->data = data;
    newNode->next = NULL;

    if (Queue_Empty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;  // 기존 rear의 next가 새 노드를 가리킴
        queue->rear = newNode;        // rear를 새 노드로 변경
    }
    queue->size++;
}

DataBox* Queue_Dequeue(Queue* queue) {
    if (Queue_Empty(queue)) return NULL;

    QueueNode* temp = queue->front;  // 삭제할 노드 임시 저장
    DataBox* data = temp->data;
    queue->front = queue->front->next;  // front를 다음 노드로 변경

    if (queue->front == NULL) {  // 만약 큐가 비었다면 rear도 NULL로
        queue->rear = NULL;
    }

    free(temp);  // 삭제한 노드 메모리 해제
    queue->size--;

    return data;
}

void Queue_Destroy(Queue* queue) {
    while (!Queue_Empty(queue)) {
        Queue_Dequeue(queue);
    }
    free(queue);
}

void Queue_View(Queue* queue) {
    if (queue == NULL || queue->front == NULL) return;

    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data->i);  // DataBox의 필드 가정
        current = current->next;
    }
    printf("\n");
}

void Queue_Sample() {
    printf("큐 생성 및 데이터 추가\n");
    Queue* queue = Queue_Init();
    DataBox* data;

    // 큐에 데이터 추가
    for (int i = 60; i > 0; i -= 3) {
        data = MakeData(i);  // MakeData는 사용자의 DataBox 생성 함수
        Queue_Enqueue(queue, data);
    }
    Queue_View(queue);

    printf("데이터 10개 꺼낸 뒤 그 10개 데이터 출력\n");
    for (int i = 0; i < 10; i++) {
        data = Queue_Dequeue(queue);
        if (data != NULL) {
            printf("%d ", data->i);
            DestroyData(data);  // data를 해제하는 함수
        }
    }
    printf("\n");
    Queue_Destroy(queue);

    printf("큐 삭제 후 새로 초기화\n");
    queue = Queue_Init();
    for (int i = 100; i > 0; i -= 6) {
        data = MakeData(i);
        Queue_Enqueue(queue, data);
    }
    Queue_View(queue);
    Queue_Destroy(queue);
}
