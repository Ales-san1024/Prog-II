#include "../include/ram.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>

int main() {
  printf("initram()...\n");
  RAM ram = initram(1024);
  printNodo(ram);
  assert(ram);
  RAM bigram = initram(1048576);
  assert(bigram);
  
  printf("allocram()...\n");
  RAM insert = allocram(256, ram);
  assert(insert->s == OCCUPATO);
  assert(insert->parent);
  assert(insert->KB == 256);
  assert(!(insert->lbuddy));
  assert(!(insert->rbuddy));
  RAM i2 = allocram(256, ram);
  RAM i3 = allocram(256, ram);
  RAM i4 = allocram(256, ram);
  RAM failed = allocram(256, ram);
  printRAM(ram, 1);
  assert(i2 && i3 && i4 && !failed);

  RAM insert_big = allocram(256, bigram);
  printf("bigram\n");
  printRAM(bigram,1);
  printf("OK\n");
  
  printf("deallocram()...\n");
  Risultato deall = deallocram(insert);
  Risultato deall2 = deallocram(i2);
  Risultato deall3 = deallocram(i3);
  Risultato deall4 = deallocram(i4);

  printRAM(ram, 1);
  assert(deall == OK);
  assert(ram->lbuddy == NULL);
  assert(ram->rbuddy == NULL);
  assert(deall == deall2 && deall2 == deall3 && deall3 == deall4 && deall == OK);
  printf("OK\n");
  printf("numfree()...\n");
  insert = allocram(256, ram);
  printRAM(ram, 1);
  int space = numfree(ram);
  assert(space == 768);
  printf("OK\n");
  
  printf("ram2str()...\n");
  char *s1 = ram2str(ram);
  printf("%s\n", s1);
  char* s2 = ram2str(bigram);
  printf("%s\n", s2);
  
  printf("str2ram()...\n");
  RAM s2r_1 = str2ram(s1);
  RAM s2r_2 = str2ram(s2);
  printf("ram\n");
  printRAM(s2r_1,1);
  printf("bigram\n");
  printRAM(s2r_2,1);
  

  freeram(&ram);
  freeram(&bigram);
  assert(!ram);
  assert(!bigram);
  printf("All tests passed\n");
  return 0;
}