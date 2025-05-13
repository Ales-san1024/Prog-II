#include <stdio.h>
#include <stdlib.h>
#include "../include/ram.h"
#include <string.h>
#include <ctype.h>



int is_power_of_two(int n) {
  return (n > 0) && ((n & (n - 1)) == 0);
}


RAM initram(int M) {
  if (M < 0 || !is_power_of_two(M)) return NULL;
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
  if (K <= 0 || !ram || ram->KB < K) return NULL;
  
  if (ram->s == LIBERO) {
    if (K <= ram->KB/2) {
      ram->lbuddy = initram(ram->KB/2);
      ram->rbuddy = initram(ram->KB/2);
      if (!ram->lbuddy || !ram->rbuddy) return NULL;
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

  
  RAM ret = allocram(K, ram->lbuddy);
  return ret? ret : allocram(K, ram->rbuddy);

  
}


Risultato deallocram(RAM ram) {
  if (!ram || ram->s != OCCUPATO) return NOK;

  ram->s = LIBERO;
  RAM parent = ram->parent;
  while (parent && parent->lbuddy->s == LIBERO && parent->rbuddy->s == LIBERO) {
    free(parent->lbuddy);
    parent->lbuddy = NULL;
    free(parent->rbuddy);
    parent->rbuddy = NULL;
    parent->s = LIBERO;
    parent = parent->parent;
  }
  

  return OK;
}


int numfree(RAM ram) {
  if (!ram) return -1;
  
  if (ram->s == OCCUPATO) return 0;

  if (ram->s == LIBERO) return ram->KB;

  
  return numfree(ram->lbuddy) + numfree(ram->rbuddy);
  
}


void ram2strR(RAM ram, char* dest, size_t* pos) {
  if (!ram) return;

  
  *pos += sprintf(dest + *pos, "(%d:%c",
                  ram->KB,
                  ram->s == OCCUPATO ? 'O' :
                  ram->s == LIBERO ? 'L' : 'I');

  
  if (ram->s == INTERNO) {
    dest[(*pos)++] = ' ';
    ram2strR(ram->lbuddy, dest, pos);
    dest[(*pos)++] = ' ';
    ram2strR(ram->rbuddy, dest, pos);
  }

  
  dest[(*pos)++] = ')';
  dest[*pos] = '\0';
}

char* ram2str(RAM ram) {

  size_t bufsize = 4096;
  char *dest = (char*)malloc(bufsize);
  if (!dest) return NULL;
  *dest = '\0';
  if (!ram) return dest;
  size_t pos = 0; 
  ram2strR(ram, dest, &pos); 
  dest[pos] = '\0';

  return dest;
}
RAM str2ramR(char **str) {
  if (**str == ' ') (*str)++;
  if (**str == '(') (*str)++;
  
  
  int KB = 0;
  while (**str >= '0' && **str <= '9') {
    KB *= 10;
    KB += **str - '0';
    (*str)++;
  }
  
  RAM ram = initram(KB);
  if (!ram) return NULL;

  (*str)++; //salta i ':'

  if (**str == 'O') ram->s = OCCUPATO;
  else if (**str == 'I') ram->s = INTERNO;
  (*str)++;

  if (ram->s == INTERNO) {

    if (**str == ' ') (*str)++; //salta lo spazio
    ram->lbuddy = str2ramR(str);
    ram->lbuddy->parent = ram;
    
    (*str)++;
    
    ram->rbuddy = str2ramR(str);
    ram->rbuddy->parent = ram;
  }

  
  
  if (**str == ')') (*str)++;
  return ram;
}
RAM str2ram(char *str) {
  if (!str) return NULL;

  return str2ramR(&str);
}

Risultato freeram(RAM* ramptr) {
  if (!ramptr || !*ramptr) return NOK;

  freeram(&((*ramptr)->lbuddy)); //se lbuddy non esiste freeram ritorna NOK e basta
  freeram(&((*ramptr)->rbuddy));
  free(*ramptr);
  *ramptr = NULL;
  return OK;
} 