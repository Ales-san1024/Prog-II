#include <stdio.h>
#include <stdlib.h>
#include "../include/linkedListQueue.h"

int main() {
    CharQueueADT q = mkQueue();
    if (q) {

      printf("[Expected: 0 Got: %d]\n", isEmpty(q));
  
      printf("[Expected: 1 Got: %d]\n", enqueue(q, 'A'));
      printf("[Expected: 1 Got: %d]\n", enqueue(q, 'B'));
      printf("[Expected: 1 Got: %d]\n", enqueue(q, 'C'));
  
      printf("[Expected: 0 Got: %d]\n", isEmpty(q));
  
      printf("[Expected: 3 Got: %d]\n", size(q));
  
      char peekRes;
      printf("[Expected: 1 Got: %d]\n", peek(q, 0, &peekRes));
      printf("[Expected: 'A' Got: '%c']\n", peekRes);
  
      printf("[Expected: 1 Got: %d]\n", peek(q, 1, &peekRes));
      printf("[Expected: 'B' Got: '%c']\n", peekRes);
  
      printf("[Expected: 1 Got: %d]\n", peek(q, 2, &peekRes));
      printf("[Expected: 'C' Got: '%c']\n", peekRes);
  
      char dequeued;
      printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
      printf("[Expected: 'A' Got: '%c']\n", dequeued);
      printf("[Expected: 2 Got: %d]\n", size(q));
  
      printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
      printf("[Expected: 'B' Got: '%c']\n", dequeued);
      printf("[Expected: 1 Got: %d]\n", size(q));
  
      printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
      printf("[Expected: 'C' Got: '%c']\n", dequeued);
      printf("[Expected: 0 Got: %d]\n", isEmpty(q));
  
      printf("[Expected: 0 Got: %d]\n", dequeue(q, &dequeued));
  
      printf("[Expected: 0 Got: %d]\n", size(q));
  
      dsQueue(&q);
      printf("[Expected: 1 Got: %d]\n", q == NULL);
  
      return 0;
    }
}
