#include <stdio.h>
#include <stdlib.h>
#include "../include/ram.h"
#include <string.h>
#include <ctype.h>



RAM initram(int M) {
  RAM r = (RAM)malloc(sizeof(struct nodo));
  if (!r) return NULL;
  r->lbuddy = NULL;
  r->rbuddy = NULL;
  r->s = LIBERO;
  r->KB = M;
  r->parent =  NULL;
  return r;
}

RAM allocram(int K, RAM ram) {
  if (K < 0 || !ram || ram->KB < K) return NULL;
  
  if (ram->s == LIBERO) {
    if (K <= ram->KB/2) {
      ram->lbuddy = initram(ram->KB/2);
      ram->rbuddy = initram(ram->KB/2);
      ram->lbuddy->parent = ram;
      ram->rbuddy->parent = ram;
      ram->s = INTERNO;
      return allocram(K, ram->lbuddy);
    }
    ram->s = OCCUPATO;
    return ram;

  }

  if (ram->s == OCCUPATO) {
    return NULL;
  }

  if (ram->s == INTERNO) {
    RAM ret = allocram(K, ram->lbuddy);
    return ret? ret : allocram(K, ram->rbuddy);

  }
}


Risultato deallocram(RAM ram) {
  return OK;
}


int numfree(RAM ram) {
  return 0;
}


char* ram2str(RAM ram) {
  return NULL;
}


RAM str2ram(char *str) {
  return NULL;
}

Risultato freeram(RAM* ramptr) {
  return OK;
} 