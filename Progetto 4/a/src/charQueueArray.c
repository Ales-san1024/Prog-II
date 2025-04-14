#include <stdio.h>
#include <stdlib.h>
#include "../include/charArrayQueue.h"

CharQueueADT mkQueue() {
  CharQueueADT q;
  q = (CharQueueADT)malloc(sizeof(struct charQueue));

  if (!q) return NULL;
  q->capacity = INITIAL_CAPACITY;
  q->a = (char*)malloc(sizeof(char)*q->capacity);
  if (!q->a) { 
    free(q);
    return NULL;
  }

  q->size = 0;
  q->rear = 0;
  q->front = 0;
  

  return q;
}

void dsQueue(CharQueueADT *pq) {
  if (*pq) {
    free((*pq)->a);
    free(*pq);
    *pq = NULL;
  } 
}

_Bool enqueue(CharQueueADT q, const char e) {
  if (q->capacity == q->size) return 0;
  q->a[q->rear] = e;
  q->size++;
  q->rear = (q->rear + 1) % q->capacity;
  return 1;
}

_Bool dequeue(CharQueueADT q, char*res) {
  if (q->size == 0) return 0;
  *res = q->a[q->front];
  q->front = (q->front + 1)%q->capacity;
  q->size--;
  return 1;  
}

_Bool isEmpty(CharQueueADT q) {
  return q->size == 0;
}

int size(CharQueueADT q) {
  return q->size;
}

_Bool peek(CharQueueADT q, int position, char* res) {
  if (q->size == 0 || position < 0 || position > q->size) return 0;
  *res = q->a[(position + q->front) % q->capacity];
  return 1;
}