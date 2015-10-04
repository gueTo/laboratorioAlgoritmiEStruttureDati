/* 
  FUNZIONI PER LA GESTIONE DI UNA CODA 
       TRAMITE LISTA CONCATENATA
  Strutture e prototipi funzione per
  gestione di una coda di tipo FIFO.
  
  di Francesco Altiero, matr.566/2258
  email: auronisback@hotmail.com      */

#include <stdio.h>
//definisco un nodo della coda
//come in campo info generico ed un
//puntatore all'elemento successivo
#ifndef QUEUE_NODE
#define QUEUE_NODE QUEUE_NODE
typedef struct QUEUE_NODE
{
  void *info;
  struct QUEUE_NODE *next;
} QUEUE_NODE;
#endif

//definisco il tipo coda
//come un puntatore alla testa
//ed uno alla coda della coda
#ifndef QUEUE
#define QUEUE QUEUE
typedef struct
{
  QUEUE_NODE *fronte;
  QUEUE_NODE *retro;
} QUEUE;
#endif


//Inizializza la coda
//input: QUEUE coda: la coda da inizializzare
//output: la coda inizializzata
QUEUE InizializzaCoda(QUEUE coda);


//Controlla se la coda è vuota
//input: QUEUE coda: la coda
//output: 1 se la coda è vuota, 0 altrimenti
int CodaVuota(QUEUE coda);

//Inserisce un elemento in testa
//input: - QUEUE coda: la coda in cui inserire
//       - void *elem: l'elemento da inserire
//output: la coda modificata
QUEUE Accoda(QUEUE coda, void *elem);


//Estrae l'ultimo elemento della coda
//input: QUEUE *coda: un puntatore alla coda
//                    TALE VALORE VERRA' MODIFICATO
//output: l'elemento estratto, NULL se la coda è vuota
void *Decoda(QUEUE *coda);
