#include "../include/liste.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    L_Ptr alfabeto = NULL;  

   
    for (size_t i = 0; i < 26; i++) {
        printf("A + %zu = %c\n", i, 'A' + i);
        addNodeToTail(&alfabeto, 'A' + i);
    }

    
    printf("Lista originale: ");
    printLista(alfabeto);

   
    reverseList(&alfabeto);

   
    printf("Lista invertita: ");
    printLista(alfabeto);


    removeChar(&alfabeto, 'H');

    printf("Lista senza H: ");
    printLista(alfabeto);

    removeChar(&alfabeto,'Z');

    printf("Lista senza Z: ");
    printLista(alfabeto);


    deleteList(&alfabeto);

    printf("Lista dopo la cancellazione: ");
    printLista(alfabeto);

    return 0;
}
