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

_Bool enqueue(CharQueueADT q, const char e){
    if (q == NULL || q->size == q->capacity) {
        return 0; 
    }else{
        q->a[q->rear] = e;
        q->rear = (q->rear + 1) % (q->capacity);
        (q->size) ++;
        if(q->size == (q->capacity)){
            int new_capacity = (q->capacity)*2;
            char* new_array = malloc(sizeof(char) * new_capacity);
            for(int i = 0; i < q->size; i++){
                new_array[i] = q->a[(q->front + i) % q->capacity];
            }
            free(q->a);
            q->a = new_array;
            q->capacity = new_capacity;
            q->front = 0;
            q->rear = q->size;
        }
        return 1;
}

}

/** @brief Toglie e restituisce l'elemento in testa alla coda, restituisce esito 0/1 */
_Bool dequeue(CharQueueADT q, char*res){
    if (q == NULL || q->size == 0) {
        return 0; 
    }else{
        *res = (q->a[q->front]);
        (q->front) = (q->front + 1) % (q->capacity);
        (q->size)--;
        if(q->size < (q->capacity)/4 && q->capacity>INITIAL_CAPACITY){
            int new_capacity = q->capacity / 2;
            char* new_array = malloc(sizeof(char) * new_capacity);            
            for(int i = 0; i < q->size; i++){
                new_array[i] = q->a[(q->front + i) % q->capacity];
            }
            free(q->a);
            q->a = new_array;
            q->capacity = new_capacity;
            q->front = 0;
            q->rear = q->size;
        }
        return 1;
 }
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
