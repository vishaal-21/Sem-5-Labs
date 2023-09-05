#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
}Queue;

void initialize(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(struct Queue* q) {
    return (q->rear == MAX_SIZE - 1);
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }

    q->items[q->rear] = value;
}

int main() {
    Queue q;
    initialize(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Elements in the queue: ");
    while (!isEmpty(&q)) {
        printf("%d ", q.items[q.front]);
        q.front++;
    }
    printf("\n");

    return 0;
}
