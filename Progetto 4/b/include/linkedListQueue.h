#ifndef GUARD_CharQueue
#define GUARD_CharQueue

#include "charQueueADT.h"

typedef struct listNode ListNode, *ListNodePtr;
struct listNode {
   char data;
   ListNodePtr next;
};

struct charQueue {
    ListNodePtr front; /* Punta al primo nodo della lista, che contiene l'elemento in testa alla coda, se la coda è vuota vale NULL */
    ListNodePtr rear; /* Punta all'ultimo nodo della lista, che contiene l'elemento in fondo alla coda, se la coda è vuota vale NULL */
    int size;
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
};

#endif