#include "../include/charArrayQueue.h"
#include <stdio.h>


int main() {
  CharQueueADT queue = mkQueue();
  for (int i = 0; i < queue->capacity + 1; i++) {
    printf("%d: %d\n", i, enqueue(queue, 'A'+i));
  }
  char c;
  dequeue(queue, &c);
  printf("%c\n", c);

  peek(queue, 1, &c);
  printf("[Expected: C Got:%c]\n", c);

  dsQueue(&queue);
  if (!queue) puts("Elimination Succeded");
}