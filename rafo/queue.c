/*
  FUNZIONI PER LA GESTIONE DI UNA CODA
  TRAMITE LISTA CONCATENATA
  Implementazione delle funzioni di gestione
  di una coda di tipo FIFO.

  di Francesco Altiero, matr.566/2258
  email: auronisback@hotmail.com  */

#include "include\queue.h"

//Inizializza la coda
//input: QUEUE coda: la coda da inizializzare
//output: la coda inizializzata
QUEUE InizializzaCoda(QUEUE coda)
{
  coda.fronte = NULL;
  coda.retro = NULL;
  return coda;
}


//Controlla se la coda è vuota
//input: QUEUE coda: la coda
//output: 1 se la coda è vuota, 0 altrimenti
int CodaVuota(QUEUE coda)
{
  return !coda.fronte;
}


//Inserisce un elemento sul retro della coda
//input: - QUEUE coda: la coda in cui inserire
//       - void *elem: l'elemento da inserire
//output: la coda modificata
QUEUE Accoda(QUEUE coda, void *elem)
{
  QUEUE_NODE *nodo;

  //alloco memoria e compongo per il nodo
  nodo = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));
  nodo->info = elem;
  nodo->next = NULL;

  //se la lista è vuota faccio puntare fronte e retro al primo elemento
  if(CodaVuota(coda))
  {
    coda.fronte = nodo;
    coda.retro = nodo;
  }
  //se non è così faccio puntare il nodo puntato da retro al nodo da inserire
  //ed aggiorno il valore del retro al nuovo nodo
  else
  {
    (coda.retro)->next = nodo;
    coda.retro = nodo;
  }
  return coda;
}


//Estrae il primo elemento della coda
//input: QUEUE *coda: un puntatore alla coda
//                    TALE VALORE VERRA' MODIFICATO
//output: l'elemento estratto, NULL se la coda è vuota
void *Decoda(QUEUE *coda)
{
  void *ret;
  QUEUE_NODE *tmp;
  //se la coda non è vuota
  if(!CodaVuota(*coda))
  {
    tmp = coda->fronte;
    //se si deve estrarre l'ultimo elemento pongo a NULL il puntatore al retro
    if(coda->fronte == coda->retro)
      coda->retro = NULL;
    //estraggo l'elemento in testa ed aggiorno i puntatori
    coda->fronte = coda->fronte->next;
    ret = tmp->info;
    //dealloco il nodo
    free(tmp);
  }
  else
    ret = NULL;
  return ret;
}



