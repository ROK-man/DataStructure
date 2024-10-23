#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../DataBox.h"

typedef struct QueueNode {
    DataBox* data;
    struct QueueNode* next;  // ���� ��带 ����Ű�� ������
} QueueNode;

typedef struct Queue {
    QueueNode* front;  // ť�� ���� �տ� �ִ� ���
    QueueNode* rear;   // ť�� ���� �ڿ� �ִ� ���
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
        queue->rear->next = newNode;  // ���� rear�� next�� �� ��带 ����Ŵ
        queue->rear = newNode;        // rear�� �� ���� ����
    }
    queue->size++;
}

DataBox* Queue_Dequeue(Queue* queue) {
    if (Queue_Empty(queue)) return NULL;

    QueueNode* temp = queue->front;  // ������ ��� �ӽ� ����
    DataBox* data = temp->data;
    queue->front = queue->front->next;  // front�� ���� ���� ����

    if (queue->front == NULL) {  // ���� ť�� ����ٸ� rear�� NULL��
        queue->rear = NULL;
    }

    free(temp);  // ������ ��� �޸� ����
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
        printf("%d ", current->data->i);  // DataBox�� �ʵ� ����
        current = current->next;
    }
    printf("\n");
}

void Queue_Sample() {
    printf("ť ���� �� ������ �߰�\n");
    Queue* queue = Queue_Init();
    DataBox* data;

    // ť�� ������ �߰�
    for (int i = 60; i > 0; i -= 3) {
        data = MakeData(i);  // MakeData�� ������� DataBox ���� �Լ�
        Queue_Enqueue(queue, data);
    }
    Queue_View(queue);

    printf("������ 10�� ���� �� �� 10�� ������ ���\n");
    for (int i = 0; i < 10; i++) {
        data = Queue_Dequeue(queue);
        if (data != NULL) {
            printf("%d ", data->i);
            DestroyData(data);  // data�� �����ϴ� �Լ�
        }
    }
    printf("\n");
    Queue_Destroy(queue);

    printf("ť ���� �� ���� �ʱ�ȭ\n");
    queue = Queue_Init();
    for (int i = 100; i > 0; i -= 6) {
        data = MakeData(i);
        Queue_Enqueue(queue, data);
    }
    Queue_View(queue);
    Queue_Destroy(queue);
}
