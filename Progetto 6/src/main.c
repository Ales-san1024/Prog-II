#include "../include/ram.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>

int main() {
  RAM ram = initram(1024);
  printNodo(ram);
  RAM insert = allocram(256, ram);
  printf("Insert...\n");
  printNodo(insert);
  assert(insert->s == OCCUPATO);
  assert(insert->parent);
  assert(insert->KB == 256);
  assert(!(insert->lbuddy));
  assert(!(insert->rbuddy));
  printf("OK\n");
  RAM curr = insert;
  while (curr)
  {
    printNodo(curr);
    curr = curr->parent;
  }
  
  return 0;
}