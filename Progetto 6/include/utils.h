/**
 * File non necessario, fatto solo per fare i vari test
 */
#ifndef UTILS_H
#define UTILS_H

#include "ram.h"
/**
 * @brief stampa il contenuto di un nodo
 * 
 * @param r puntatore al nodo
 */
void printNodo(RAM r);
/**
 * @brief stampa tutti i nodi della RAM partendo dal nodo più alto
 * 
 * @param r 
 */
void printRAM(RAM r,int depth);
#endif
