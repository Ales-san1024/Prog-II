#include "../include/ram.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>

int main() {
  RAM ram = initram(1024);
  printNodo(ram);
  RAM insert = allocram(256, ram);
  
  printf("allocram()...\n");
  printRAM(ram, 1);
  assert(insert->s == OCCUPATO);
  assert(insert->parent);
  assert(insert->KB == 256);
  assert(!(insert->lbuddy));
  assert(!(insert->rbuddy));
  printf("OK\n");
  
  printf("deallocram()...\n");
  Risultato deall = deallocram(insert);
  printRAM(ram, 1);
  assert(deall == OK);
  assert(ram->lbuddy == NULL);
  assert(ram->rbuddy == NULL);
  printf("OK\n");

  printf("numfree()...\n");
  insert = allocram(256, ram);
  int space = numfree(ram);
  assert(space == 768);
  printf("OK\n");
  return 0;
}