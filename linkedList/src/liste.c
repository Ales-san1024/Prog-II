#include "../include/liste.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printLista(L_Ptr l) {
  //Lista Vuota
  if(l == NULL) {
    puts("");
    return;
  }
  printf("%c", l->lettera);
  printLista(l->next);
}

void addNodeToTail(L_Ptr* l, char c) {
  
  
  if(!(*l)) {
    *l = (L_Ptr)malloc(sizeof(Lista));
    (*l)->lettera = c;
    (*l)->next = NULL;
    return;
  }
  addNodeToTail(&((*l)->next), c);
}

void deleteList(L_Ptr* l) {
  if (!(*l)) {
    return;
  }
  deleteList(&((*l)->next));
  free((*l));
  *l = NULL;
  return;
}

void reverseList(L_Ptr* l) {
 

  //Lista di 0-1 elementi non si fa nulla
  if (!(*l) || !((*l)->next)) {
    return;
  }

  L_Ptr prev = NULL;
  L_Ptr curr = *l;
  L_Ptr next = NULL;
  

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *l = prev;
}

_Bool removeChar(L_Ptr* l, char c) {
  L_Ptr prev = NULL;
  L_Ptr curr = *l;
  while (curr && curr->lettera != c) {
    prev = curr;
    curr = curr->next;
  }

  if (!curr) return false;
  
  if (!prev) *l = curr->next;
  else prev->next = curr->next;
  
  free(curr);
  return true;
}