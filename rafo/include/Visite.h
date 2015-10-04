/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni per visite e trasposizioni di grafi
  per entrambe le rappresentazioni supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "Grafo.h"
#include "queue.h"

//definisco una variabile globale da utilizzare per la visita DFS
#ifndef DFSTIME
#define DFSTIME
unsigned int tempoDFS;
#endif

//defiinsco una costante per indicare che un nodo non è stato ancora visitato
#ifndef NON_SCOPERTO
#define NON_SCOPERTO -1
#endif

//definisco una costante per indicare nessun predecessore
#ifndef NESSUNO
#define NESSUNO -1
#endif


//Funzione di interfaccia per la visita BFS
//Chiama la visita BFS utilizzando come parametro l'id del vertice
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - void *sorgente: l'identificatore del vertice sorgente
//output: nessuno
void BFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id);


//Effettua una visita BFS per calcolare i percorsi minimi da una sorgente
//input: - GRAPH grafo: il grafo da visitare
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - unsigned int indiceSorgente: l'indice del vertice sorgente
//output: nessuno
void BFScore(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int sorgente);


//Effettua una DFS sul grafo per calcoare i tempi di scoperta e di completamento
//dei vertici del grafo
//input: - GRAPH grafo: il grafo da visitare
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione
//output: nessuno
void DFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Effettua la visita in profondità su un vertice. Chiamata dalla funzione DFS
//input: - GRAPH grafo: il grafo che si sta visitando
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - unsigned int indiceSorgente: l'indice della sorgente
//output: nessuno
void VisitaDFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int indiceSorgente);


//Calcola il grafo trasposto
//input: - GRAPH grafo: il grafo da trasporre
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con il grafo
//output: il grafo trasposto
GRAPH TrasponiGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Cerca cicli nel grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: 1 se il grafo contiene cicli, 0 altrimenti
int ContieneCicli(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Cerca cicli da un vertice sorgente
//effettua una visita in profondità sul vertice per cercare vertici grigi
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - unsigned int indiceSorgente: la sorgente della visita
//output: 1 se il grafo contiene cicli, 0 altrimenti
int VisitaContieneCicli(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int indiceSorgente);


//Funzione di interfaccia per stampare un cammino tra vertici fornendo due identificatori
//chiama la funzione ScriviCamminoCore che effettua tale verifica
//input: - FILE *fp: l'output su cui scrivere
//       - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - void *idPartenza: l'identificatore del nodo da cui partire
//       - void *idArrivo: l'identificatore del nodo di arrivo
//output: nessuno
void ScriviCammino(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idPartenza, void *idArrivo);


//Scrive un cammino da due vertici del grafo
//input: - FILE *fp: l'output su cui scrivere
//       - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - unsigned int partenza: il vertice da cui partire
//       - unsigned int arrivo: il vertice finale
//output: nessuno
void ScriviCamminoCore(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int partenza, unsigned int arrivo);
