/*
  GESTIONE DI LISTE ORDINATE      
  Funzioni per la gestione di liste    
  generiche ordinate in senso crescente          
                                      
  di Francesco Altiero, matr.566/2258  
  email: auronisback@hotmail.com       */

#include "include\list.h"

//Crea una struttura di tipo OPERAZIONI
//input: - void *(*AllocaDato)(void *, void *): funzione di allocazione del dato della lista
//       - void (*StampaDato)(FILE *, void *, void *): funzione di stampa del dato della lista
//       - int (*ComparaDati)(void *, void *, void *): funzione di comparazione dei dati della lista
//       - void *(*GestisciCollisione)(void *, void *): funzione per la gestione delle collisioni
//       - void (*DeallocaDato)(void *, void *): funzione per la deallocazione di un dato della lista
//       - void *(*LeggiDaInput)(void *, void *): funzione che specifica l'input da utilizzare
//       - unsigned long (*FunzioneHash)(void *, void *): la funzione di hash per l'elemento
//output: la struttura che contiene il pool di funzioni per la gestione
OPERAZIONI InserisciFunzioni(void *(*AllocaDato)(void *, void *), void (*StampaDato)(FILE *, void *, void *), 
                                  int (*ComparaDati)(void *, void *, void *),  void *(*GestisciCollisione)(void *, void *),
                                  void (*DeallocaDato)(void *, void *), void *(*LeggiDaInput)(void *, void *),
                                  unsigned long (*FunzioneHash)(void *, void *))
{
  OPERAZIONI fun;
  fun.AllocaDato = AllocaDato;
  fun.StampaDato = StampaDato;
  fun.ComparaDati = ComparaDati;
  fun.GestisciCollisione = GestisciCollisione;
  fun.DeallocaDato = DeallocaDato;
  fun.LeggiDaInput = LeggiDaInput;
  fun.FunzioneHash = FunzioneHash;
  return fun;
}


//Inizializza la lista
//input: nessuno
//output: una lista vuota
LIST InizializzaLista()
{
  return NULL;
}


//Controlla se la LIST è vuota
//input: LIST lista: la lista da controllare
//output: restituisce TRUE se la lista è vuota, FALSE altrimenti
int ListaVuota(LIST lista)
{
  return (lista == NULL);
}


//Alloca un nodo da inserire nella lista
//input: void *x: il dato da memorizzare nel nodo
//output: il nodo costruito
LIST_NODE *AllocaNodo(void *x)
{
  LIST_NODE *ret;
  ret = (LIST_NODE *)malloc(sizeof(LIST_NODE));
  ret->info = x;
  return ret;
}

//Dealloca un nodo della lista
//input: - OPERAZIONI fun: il pool di funzioni per la gestione dei dati
//       - LIST_NODE *x: il nodo da deallocare
//       - void *param: altri parametri utili per la gestione
//output: nessuno
void DeallocaNodo(OPERAZIONI fun, LIST_NODE *x, void *param)
{
  fun.DeallocaDato(x->info, param);
  free(x);
}


//Inserisce un nuovo nodo nella lista preservando l'ordine
//input: - LIST lista: la lista a cui aggiungere il nodo
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - LIST_NODE *node: il nodo da inserire
//       - void *param: altri paramentri utili per la gestione
//output: la lista modificata
LIST InserisciInLista(LIST lista, OPERAZIONI fun, LIST_NODE *node, void *param)
{
  //se la lista è vuota inserisce il nodo
  if(ListaVuota(lista))
  {
    node->next = lista;
    lista = node;
  }
  //se il secondo nodo è maggiore del primo
  else if(fun.ComparaDati(lista->info, node->info, param) < 0)
    lista->next = InserisciInLista(lista->next, fun, node, param);
  //se i valori sono uguali chiama il gestore delle collisioni
  else 
  {  
    if(fun.ComparaDati(lista->info, node->info, param) == 0)
      node->info = fun.GestisciCollisione(node->info, param);
    //se l'info del nodo non è nullo lo inserisco
    if(node->info != NULL)
    {
      node->next = lista;
      lista = node;    
    }
    //in caso contrario dealloca il nodo
    else
      free(node);
  }
  
  return lista;
}


//Cancella l'elemento uguale ad info nella lista
//input: - LIST lista: la lista in cui cancellare
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *info: il valore da cancellare
//       - void *param: altri paramenti utili per la gestione
//output: la lista modificata
LIST CancellaDallaLista(LIST lista, OPERAZIONI fun, void *info, void *param)
{
  LIST_NODE *tmp;
  //se la lista non è ancora terminata cerca il valore da cancellare
  if(!ListaVuota(lista))
  {
    //printf("Corrente: %d <- %d\n", *(int *)lista->info, *(int *)info);
    if(fun.ComparaDati(lista->info, info, param) < 0)
      lista->next = CancellaDallaLista(lista->next, fun, info, param);
    
    //se la chiave viene trovata
    else if(fun.ComparaDati(lista->info, info, param) == 0)
    {
      tmp = lista;
      lista = lista->next;
      DeallocaNodo(fun, tmp, param);
    }
  }
  //ritorna il nodo corrente (modificato se necessario)
  return lista;
}


//Cancella interamente la lista
//input: - LIST lista: la lista da cancellare
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *param: altri paramentri utili per la gestione
//return: la lista svuotata
LIST DeallocaLista(LIST lista, OPERAZIONI fun, void *param)
{
  LIST tmp;
  if(!ListaVuota(lista))
  {
    //aggiorna i puntatori e dealloca il nodo
    tmp = lista;
    lista = lista->next;
    DeallocaNodo(fun, tmp, param);//chiama la funzione di deallocazione sul'elemento corrente
    lista = DeallocaLista(lista, fun, param);
  }
  return lista;
}


//Stampa la lista
//input: - FILE *fp: l'output su cui scrivere
//       - LIST lista: la lista
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *param: altri parametri utili per la gestione
//return: niente
void StampaLista(FILE *fp, LIST lista, OPERAZIONI fun, void *param)
{
  //finchè la lista non è terminata
  if(!ListaVuota(lista))
  {
    //chiama la funzione di stampa sul nodo corrente e prosegue
    fun.StampaDato(fp, lista->info, param);
    StampaLista(fp, lista->next, fun, param);
  }
  //quando la lista è terminata va a capo
  else
    printf("\n");
}


//Inserisce un numero di elementi definito dall'utente nella lista da un 
//input determinato dalla funzione di input del pool di funzioni
//input: - LIST l: la lista in cui inserire
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - int n: il numero di dati da leggere
//       - void *source: il parametro da passare alla funzione di lettura
//       - void *param: altri parametri utili per la gestione
//output: la lista modificata
LIST GetDato(LIST lista, OPERAZIONI fun, int n, void *source, void *param)
{
  int i;
  LIST_NODE *node;
  for(i = 0; i < n; i++)
  {
    //leggo il dato da input, lo alloco in un nodo
    node = AllocaNodo(fun.LeggiDaInput(source, param));
    
    //se il nodo contiene un dato valido lo inserisco
    if(node->info != NULL)
      lista = InserisciInLista(lista, fun, node, param);
  }
  return lista;
}


//Cerca un valore nella lista e ne restituisce il puntatore
//input: - LIST lista: la lista in cui cercare
//       - OPERAZIONI fun: le funzioni per la gestione della lista
//       - void *key: il nodo del nodo da ricercare
//       - void *param: altri parametri utili per la gestione
//output: il puntatore all'elemento ricercato o NULL se l'elemento non è presente
void *CercaNellaLista(LIST lista, OPERAZIONI fun, void *key, void *param)
{
  void *ret;
  ret = NULL;
  //se la lista non è vuota
  if(!ListaVuota(lista))
  {
    //se il valore ricercato non è quello richiesto scorre ricorsivamente la lista
    if(fun.ComparaDati(lista->info, key, param) < 0)
      ret = CercaNellaLista(lista->next, fun, key, param);
    //se l'elemento è stato trovato lo restituisce
    else if(fun.ComparaDati(lista->info, key, param) == 0)
      ret = lista->info;
  }
  return ret;
}


//Inserisce un elemento in testa alla lista
//input: - LIST lista: la lista in cui inserire
//       - void *id: l'id del nodo da inserire
//output: la lista modificata
LIST PushLista(LIST lista, void *id)
{
  LIST_NODE *nodoLista;
  //inserisco l'id in un nodo
  nodoLista = AllocaNodo(id);
  //faccio puntare il nodo al primo elemento della lista
  nodoLista->next = lista;
  //e lo restituisco come nuova testa
  return nodoLista;
}


//Estrae l'elemento dalla testa della lista
//input: - LIST *listaPtr: un puntatore alla testa della
//                         lista che verrà modificato
//output: un puntatore al campo info del nodo estratto
void *PopLista(LIST *lista)
{
  void *ret;
  //se c'è almeno un alemento da estrarre
  if(!ListaVuota(*lista))
  {
    //assegno l'indirizzo della testa al valore di ritorno
    ret = (*lista)->info;
    //modifico la testa per farla puntare all'elemento successivo
    *lista = (*lista)->next;
  }
  else
    ret = NULL;
  return ret;
}
