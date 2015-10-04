/*
  GESTIONE DI LISTE ORDINATE      
  Prototipi e definizioni per la gestione 
  di liste generiche ordinate
                                      
  di Francesco Altiero, matr.566/2258  
  email: auronisback@hotmail.com          */
  
#include <stdio.h>
#include <time.h>
#ifndef DIM
#define DIM 255
#endif

#ifndef MAX_LENGTH
#define MAX_LENGTH 15
#endif

#ifndef MAX_RAND_STRING_LENGTH
#define MAX_RAND_STRING_LENGTH 15
#endif

#ifndef LIST_NODE
#define LIST_NODE LIST_NODE
//definizione dei nodi della LIST
typedef struct LIST_NODE
{
  void *info;
  struct LIST_NODE *next;
} LIST_NODE;
#endif

#ifndef OPERAZIONI
#define OPERAZIONI OPERAZIONI
//definizione della struttura delle funzioni utilizzate dalla stringa
typedef struct {
  void *(*AllocaDato)(void *info, void *param); //funzione di allocazione
  void (*StampaDato)(FILE *fp, void *info, void *param); //funzione di stampa
  int (*ComparaDati)(void *x, void *y, void *param); //funzione di confronto, restituisce
                                      //0 se i due parametri sono uguali
                                      //1 se il primo è maggiore del secondo
                                      //-1 altrimenti
  void *(*GestisciCollisione)(void *info, void *param); //funzione per la gestione di collisioni
  void (*DeallocaDato)(void *info, void *param); //funzione di deallocazione di un nodo
  void *(*LeggiDaInput)(void *source, void *param); //funzione di lettura di un dato da input
  unsigned long (*FunzioneHash)(void *info, void *param); //funzione di hash dell'elemento
} OPERAZIONI;
#endif

#ifndef LIST
#define LIST LIST
//definizione del link ad un nodo
typedef LIST_NODE * LIST;
#endif

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
                                  unsigned long (*FunzioneHash)(void *, void *));


//Inizializza la lista
//input: nessuno
//output: una lista vuota
LIST InizializzaLista();


//Controlla se la LIST è vuota
//input: LIST lista: la lista da controllare
//output: restituisce TRUE se la lista è vuota, FALSE altrimenti
int ListaVuota(LIST lista);


//Alloca un nodo da inserire nella lista
//input: - void *x: il dato a cui il nodo punterà
//output: il nodo costruito
LIST_NODE *AllocaNodo(void *x);


//Dealloca un nodo della lista
//input: - OPERAZIONI fun: il pool di funzioni per la gestione dei dati
//       - LIST_NODE *x: il nodo da deallocare
//       - void *param: altri parametri utili per la gestione
//output: nessuno
void DeallocaNodo(OPERAZIONI fun, LIST_NODE *x, void *param);

//Inserisce la chiave key nella lista l preservando l'ordine. Utilizza
//la funzione di comparazione minore contenuta nella struttura funzioni
//input: - LIST lista: la lista a cui aggiungere il nodo
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - LIST_NODE *node: il nodo da inserire
//       - void *param: altri paramentri utili per la gestione
//output: la lista modificata
LIST InserisciInLista(LIST lista, OPERAZIONI fun, LIST_NODE *node, void *param);


//Cancella l'elemento uguale ad info nella lista
//input: - LIST lista: la lista in cui cancellare
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *info: il valore da cancellare
//       - void *param: altri paramenti utili per la gestione
//output: la lista modificata
LIST CancellaDallaLista(LIST lista, OPERAZIONI fun, void *info, void *param);


//Cancella interamente la lista
//input: - LIST lista: la lista da cancellare
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *param: altri paramentri utili per la gestione
//return: la lista svuotata
LIST DeallocaLista(LIST lista, OPERAZIONI fun, void *param);


//Stampa la lista
//input: - FILE *fp: l'output su cui scrivere
//       - LIST lista: la lista
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - void *param: altri parametri utili per la gestione
//return: niente
void StampaLista(FILE *fp, LIST lista, OPERAZIONI fun, void *param);

//Inserisce un numero di elementi definito dall'utente nella lista da un 
//input determinato dalla funzione di input del pool di funzioni
//input: - LIST l: la lista in cui inserire
//       - OPERAZIONI fun: il pool di operazioni da utilizzare sulla lista
//       - int n: il numero di dati da leggere
//       - void *source: il parametro da passare alla funzione di lettura
//       - void *param: altri parametri utili per la gestione
//output: la lista modificata
LIST GetDato(LIST lista, OPERAZIONI fun, int n, void *source, void *param);


//Cerca un valore nella lista e ne restituisce il puntatore
//input: - LIST lista: la lista in cui cercare
//       - OPERAZIONI fun: le funzioni per la gestione della lista
//       - void *key: il nodo del nodo da ricercare
//       - void *param: altri parametri utili per la gestione
//output: il puntatore all'elemento ricercato o NULL se l'elemento non è presente
void *CercaNellaLista(LIST lista, OPERAZIONI fun, void *key, void *param);


//Inserisce un elemento in testa alla lista
//input: - LIST lista: la lista in cui inserire
//       - void *id: l'id del nodo da inserire
//output: la lista modificata
LIST PushLista(LIST lista, void *id);


//Estrae l'elemento dalla testa della lista
//input: - LIST *listaPtr: un puntatore alla testa della
//                         lista che verrà modificato
//output: un puntatore al campo info del nodo estratto
void *PopLista(LIST *lista);
