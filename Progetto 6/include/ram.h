#ifndef ram_h
#define ram_h

typedef enum risultato {OK, NOK} Risultato;
typedef struct nodo *RAM;           
typedef enum stato {INTERNO, LIBERO, OCCUPATO} Stato;
struct nodo {
    int KB;    // la quantità di memoria contenuta nel nodo 
    Stato s;    // stato del nodo: interno, libero, occupato
    RAM parent; // la struttura padre
    RAM lbuddy, rbuddy; // i successori, avranno dimensione KB/2
};    

/**
* @brief Crea una struttura RAM con una certa quantità di memoria  
* @param M la quantità di memoria voluta, espressa in KB (deve essere una potenza di 2, maggiore o uguale a 1)
* @return Il puntatore alla struttura creata, oppure NULL in caso di errore
*/
RAM initram(int M); 

/**
* @brief Tenta di allocare una data quantità di memoria entro una RAM
* @param K la quantità di memoria richiesta, in KB
* @param ram la RAM entro cui cercare la memoria richiesta
* @return Il puntatore al nodo che può ospitare la quantità richiesta, oppure NULL se non trovato
*/
RAM allocram(int K, RAM ram);

/**
* @brief Libera un nodo RAM precedentemente ottenuto con allocram    
* @param ram il nodo RAM da liberare
* @return Il successo della operazione
*/
Risultato deallocram(RAM ram);

/**
* @brief calcola il numero di KB di memoria ancora liberi all'interno di una struttura RAM    
* @param ram la struttura RAM 
* @return La quantità di memoria libera, oppure -1 in caso di errore
*/
int numfree(RAM ram);

/**
* @brief crea una rappresentazione dello stato interno della RAM sotto forma di una stringa (in un formato a piacere, 
* purchè completo di tutte le informazioni, ovvero tale che si possa ricreare dalla stringa esattamente lo stesso stato)
* @param ram la struttura RAM di cui creare la stringa
* @return la stringa creata, vuota in caso di RAM nulla o errore
*/
char* ram2str(RAM ram);

/**
* @brief ricostruisce una struttura RAM a partire dalla sua rappresentazione sotto forma di stringa creata da ram2str 
* @param str  la stringa che contiene la rappresentazione della RAM, eventualmente vuota
* @return la RAM creata, oppure NULL in caso di errore o stringa vuota
*/
RAM str2ram(char *str);

/**
* @brief cancella dallo heap la struttura dati di un nodo RAM e di tutti i suoi figli  
* @param ram il nodo RAM da cancellare
* @return Restituisce OK se la funzione ha effettivamente liberato della memoria, NOK altrimenti
*/
Risultato freeram(RAM* ramptr); 

#endif