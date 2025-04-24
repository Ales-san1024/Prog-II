#include "../include/linkedListQueue.h"
#include <stdio.h>
#include <stdlib.h>

CharQueueADT mkQueue() {
  CharQueueADT q;
  q = (CharQueueADT)malloc(sizeof(struct charQueue));
  if (!q) return NULL;
  q->front = NULL;
  q->rear = NULL;
  q->size = 0;
  return q;
}

void dsQueue(CharQueueADT *pq) {
  if (*pq) {

    ListNodePtr next;
    while ((*pq)->front) {
      next = (*pq)->front->next;
      free((*pq)->front);
      (*pq)->front = next;
    }
    free(*pq);
    *pq = NULL;
  }
}


_Bool enqueue(CharQueueADT q, const char e) {
  ListNodePtr node;
  node = (ListNodePtr)malloc(sizeof(ListNode));
  if (!node) return 0;
  node->data = e;
  node->next = NULL;

  if (q->rear) {

    q->rear->next = node;
  } else {
    q->front = node;
  }
  q->rear = node;
  (q->size)++;
  return 1;
}

_Bool dequeue(CharQueueADT q, char*res) {
  if (!(q->front)) return 0;

  *res = q->front->data;
  ListNodePtr node = q->front->next;
  free(q->front);
  q->front = node;
  (q->size)--;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  return 1;
}

_Bool isEmpty(CharQueueADT q) {
  return q->size == 0;
}

int size(CharQueueADT q) {
  if (q) return q->size;
  else return 0;
}

_Bool peek(CharQueueADT q, int position, char* res) {
  size_t i = 0;
  ListNodePtr curr = q->front;
  while (i < position && curr) {
    curr = curr->next;
    i++;
  }
  if (!curr) return 0;
  *res = curr->data;
  return 1;
}
