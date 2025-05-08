/**
 * File non necessario, fatto solo per fare i vari test
 */


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
  printf("[Stato: %s | Lbuddy: %s | Rbuddy: %s | Parent: %s | KB: %d]\n", 
    stato,
    r->lbuddy? "SI" : "NO", 
    r->rbuddy? "SI" : "NO", 
    r->parent? "SI" : "NO", 
    r->KB);
}

void printRAM(RAM r, int depth) {
  if (!r) return;
  
  printf("%d: ",depth);
  printNodo(r);
  if (r->lbuddy) {
     printRAM(r->lbuddy, depth + 1);
     printRAM(r->rbuddy,depth + 1);
  }
}