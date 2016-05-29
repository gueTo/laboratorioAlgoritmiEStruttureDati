/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Header per la gestione di rappresentazioni
  di archi mediante liste di adiacenza

  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com                       */

#include "Grafo.h"


//Inizializza la struttura LIST_ADJ che contiene
//un puntatore alle funzioni da utilizzare con le liste di archi
//ed un array di liste relative ai vertici del grafo
#ifndef LIST_ADJ
#define LIST_ADJ LIST_ADJ
typedef struct
{
  OPERAZIONI *fun; //le funzioni da utilizzare per le liste di archi definite
                   //in questo header
  LIST *liste; //l'array delle liste di adiacenza

} LIST_ADJ;
#endif


//Inizializza le funzioni da utilizzare per le liste di archi
//input: GRAPH grafo: il grafo di cui inizializzare le funzioni (non utilizzato qui)
//output: un puntatore alla struttura con le funzioni per la gestione delle liste di archi
void *InizializzaParametroListaAdj(GRAPH grafo);


//Inizializza le liste di adiacenza di ogni vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice di cui inizializzare il parametro
//output: la struttura LIST_ADJ modificata
void *InizializzaParametroVerticeListaAdj(GRAPH grafo, unsigned int indiceVertice);


//Inserisce un arco nella lista di adiacenze del vertice
//input: - GRAPH grafo: il grafo
//       - void *paramRappr: il parametro della rappresentazione
//       - unsigned int indiceVertice: il vertice in cui inserire l'arco
//       - GRAPH_ARC arco: l'arco da inserire
//output: il parametro del nodo (ossia la lista delle adiacenze) modificato
void *InserisciArcoListaAdj(GRAPH grafo, void *paramRappr, unsigned int indiceVertice, GRAPH_ARC arco);


//Inizializza l'iteratore per lo scorrimento degli archi nelle liste di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice a cui inizializzare l'iteratore
//output: l'iteratore che punta al primo elemento della lista di adiacenza del vertice
void *InizializzaIteratoreListaAdj(GRAPH grafo, unsigned int indiceVertice);


//Restituisce il primo arco non letto di un nodo
//necessita dell'iteratore
//input: - GRAPH grafo: il grafo, qui non utilizzato
//       - unsigned int indiceVertice: il vertice di cui leggere l'arco successivo, qui
//                                     non utilizzato ed inserito per specifiche
//       - void *iter: un puntatore all'iteratore
//output: l'arco successivo
GRAPH_ARC GetArcoSuccessivoListaAdj(GRAPH grafo, unsigned int indiceVertice, void *iter);


//Cerca un arco nella lista di adiacenza
//input: - GRAPH grafo: il grafo in cui cercare
//       - unsigned int indiceVertice: il vertice a cui eliminare l'arco
//       - unsigned int indiceArco: l'identificatore del nodo verso cui l'arco da eliminare punta
//output: 1 se l'arco esiste, 0 altrimenti
int EsisteArcoListaAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice);


//Ottimizza le liste di archi, in seguito ad un'ottimizzazione dell'array di vertici
//input: - GRAPH grafo: il grafo
//       - unsigned int vecchioIndice: il valore dell'indice obsoleto
//       - unsigned int nuovoIndice: il valore del nuovo indice del vertice
//output: il grafo modificato (se necessario)
GRAPH OttimizzaArchiListaAdj(GRAPH grafo, unsigned int vecchioIndice, unsigned int nuovoIndice);

//Cancella un arco dalla lista di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceNodo: il vertice a cui cancellare l'arco
//       - unsigned int indiceArco: l'indice del nodo a cui l'arco punta
//output: nessuno
void CancellaArcoListaAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice);


//Traspone gli archi di un grafo
//input: - GRAPH grafo: il grafo i cui archi vanno trasposti
//       - GRAPH trasposto: il grafo verso cui trasporre gli archi
//output: il grafo trasposto
GRAPH TrasponiArchiListaAdj(GRAPH grafo, GRAPH trasposto);


//Dealloca la lista di adiacenza di un vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: il vertice di cui deallocare la lista
//output: il valore NULL
void *DeallocaParametroVerticeListaAdj(GRAPH grafo, unsigned int indiceVertice);


//Dealloca il puntatore alle funzioni per la gestione delle liste di adiacenza
void *DeallocaParametroListaAdj(GRAPH grafo);


/* FUNZIONI PER LA GESTIONE DELLE LISTE DI ADIACENZA DI ARCHI */
//Calcola la funzione Hash di un arco
//input: - void *str: l'arco da calcolare
//       - void *param: parametro inserito per specifiche e non utilizzato
//output: il codice hash dell'arco
unsigned long HashArchi(void *str, void *param);


//Alloca memoria per una Arco
//input: - void *x: l'arco da allocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: l'arco allocato
void *AllocaArco(void *x, void *param);

//Compara due stringhe. Utilizza la funzione strcmp
//input: - void *x: il primo arco
//       - void *y: il secondo arco
///      - void *param: parametro non utilizzato inserito per specifiche
//output: 0 se gli archi sono uguali, -1 se il primo
//        è maggiore della seconda, 1 altrimenti
int ComparaArchi(void *x, void *y, void *param);

//Stampa una Arco
//input: - FILE *fp: l'output su cui scrivere
//       - void *arco: l'arco da stampare
//       - void *funzioniId: le funzioni di gestione dell'identificatore
//output: nessuno
void StampaArco(FILE *fp, void *arco, void *funzioniId);

//Gestisce le collisioni tra stringhe
//non si ammettono ripetizioni di stringhe
//e pertanto tale funzione restituirà NULL
//input: - void *arco: la Arco che ha causato la collisione
//       - void *param: parametro non utilizzato
//output: il valore NULL
void *GestisciCollisioneArco(void *arco, void *param);

//Dealloca una Arco
//input: - void *x: l'arco da deallocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void DeallocaArco(void *x, void *param);

//Legge un valore arco da file
//input: void *fp: un puntatore al file
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista
void *LeggiArcoDaInput(void *fp, void *param);

