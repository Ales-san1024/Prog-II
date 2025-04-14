#ifndef LISTE
#define LISTE

typedef struct lista {
  char lettera;
  struct lista* next;
} Lista, *L_Ptr;


/**
 * @brief Stampa ogni elemento di una lista dalla testa alla coda.
 * 
 * Questa funzione stampa ogni carattere contenuto nei nodi della lista
 * a partire dal primo nodo (head) fino all'ultimo (tail).
 * 
 * @param l Puntatore alla testa della lista. Se la lista è vuota, non stampa nulla.
 */
void printLista(L_Ptr l);


/**
 * @brief Aggiunge un elemento in coda alla lista.
 * 
 * Questa funzione aggiunge un nodo con un carattere specificato alla fine
 * della lista. Se la lista è vuota, crea il primo nodo.
 * 
 * @param l Puntatore alla testa della lista. Il puntatore sarà aggiornato 
 *          se necessario per mantenere la lista collegata correttamente.
 * @param c Il carattere da aggiungere come nuovo nodo alla lista.
 */
void addNodeToTail(L_Ptr* l, char c);



/**
 * 
 * @brief Elimina l'intera lista e libera la memoria
 * 
 * Questa funzione elimina ogni elemento della lista a partire dal
 * fondo 
 * 
 * @param l puntatore alla testa della lista. Al termine della funzione
 *          l sarà settato a NULL.
 * 
 */
void deleteList(L_Ptr* l);


/**
 * 
 * @brief Inverte l'ordine della lista
 * 
 * Questa funzione inverte l'ordine degli elementi della lista
 * es: a->b->c  =>  c->b->a
 * 
 * @param l puntatore alla testa della lista. Al termine della 
 *          funzione l punterà alla coda, che sarà la nuova
 *          testa.
 */

void reverseList(L_Ptr* l);


/**
 * 
 * @brief Rimuove la prima istanza di un carattere dalla lista
 * 
 * Questa funzione rimuove dalla lista la prima apparizione di un 
 * carattere c
 * 
 * @param l puntatore alla testa della lista. Al termine della
 *          funzione l potrà essere invariata o puntare al secondo
 *          elemento, qualora l'elemento da eliminare sia in testa
 * @param c il carattere da eliminare
 * 
 * @return true: se c è stato rimosso
 *         false: se c non è stato rimosso 
 */
_Bool removeChar(L_Ptr* l, char c);

#endif