#include "../include/ram.h"
#include "../include/utils.h"
#include <stdio.h>

void printNodo(RAM r) {
  const char *stato;
  switch (r->s) {
    case LIBERO : 
      stato = "LIBERO";
      break;
    
    case OCCUPATO :
      stato = "OCCUPATO";
      break;
    
    default :
      stato = "INTERNO";
      break;
     
  };
  printf("[Stato: %s, Lbuddy: %s, Rbuddy: %s, Parent: %s, KB: %d]\n", 
    stato,
    r->lbuddy? "SI" : "NO", 
    r->rbuddy? "SI" : "NO", 
    r->parent? "SI" : "NO", 
    r->KB);
}