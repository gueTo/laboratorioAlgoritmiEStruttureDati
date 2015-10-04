/*  GESTIONE DI UNA HASH TABLE CONCATENATA
  Prototipi e definizioni per la gestione di 
  una tabella hash con metodo di risoluzione 
  delle collisioni tramite lista
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "list.h"

//definisco la struttura tabella hash come un insieme
//di dimensione, 
#ifndef HASH_TABLE
#define HASH_TABLE HASH_TABLE
typedef struct
{
  unsigned int dimensione; //la dimensione della tabella
  OPERAZIONI *funzioniLista; //le funzioni utilizzate nelle liste
  LIST *tabella; //l'array di liste con i valori
} HASH_TABLE;
#endif

//Inizializza la tabella hash
//input: - unsigned int dimensione: la dimensione della tabella
//       - OPERAZIONI *funzioniLista: le funzioni utilizzate dalle liste
//output: la tabella hash inizializzata
HASH_TABLE InizializzaTabella(unsigned int dimensione, OPERAZIONI *funzioniLista);


//Inserisce un elemento nella tabella hash
//input: - HASH_TABLE tabellaHash: la tabella in cui inserire
//       - void *key: l'elemento da inserire nella tabella
//       - void *param: altri parametri per la gestione
//output: la tabella modificata
HASH_TABLE InserisciElementoTabella(HASH_TABLE tabellaHash, void *id, void *param);


//Cerca un elemento nella tabella hash
//input: - HASH_TABLE tabellaHash: la tabella in cui cercare
//       - void *key: la chiave dell'elemento da ricercare
//       - void *param: altri parametri per la gestione
//output: un puntatore all'elemento della tabella
void *CercaNellaTabella(HASH_TABLE tabellaHash, void *key, void *param);


//Cancella un elemento dalla tabella
//input: - HASH_TABLE tabellaHash: la tabella nella quale cancellare
//       - void *key: l'elemento da cancellare dalla tabella
//       - void *param: altri parametri per la gestione
//output: nessuno
void CancellaDallaTabella(HASH_TABLE tabellaHash, void *key, void *param);


//Stampa la tabella
//input: - FILE *fp: l'output su cui stampare
//       - HASH_TABLE tabellaHash: la tabella da stampare
//       - void *param: altri parametri per la gestione
//output: nessuno
void StampaTabella(FILE *fp, HASH_TABLE tabellaHash, void *param);


//Dealloca le strutture della tabella hash
//input: - HASH_TABLE tabellaHash: la tabella da deallocare
//       - void *param: altri parametri per la gestione
//output: la tabella hash deallocata
HASH_TABLE DeallocaTabella(HASH_TABLE tabellaHash, void *param);


//Ottimizza la tabella hash ricostruendo la tabella per ridurre
//il livello di collisione medio dei dati
//input: - HASH_TABLE tabellaHash: la tabella hash
//       - unsigned int n: il numero degli elementi memorizzati nella tabella
//       - void *param: altri parametri per la gestione dei dati
//output: la tabella hash modificata
HASH_TABLE OttimizzaTabella(HASH_TABLE tabellaHash, unsigned int n, void *param);
