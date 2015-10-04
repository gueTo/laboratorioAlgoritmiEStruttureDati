/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Header per la gestione di rappresentazioni
  di archi mediante matrice di adiacenza
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com                       */
  
#include "Grafo.h"
//incluso per il valore infinito
#include <math.h>

//definisco il valore standard per indicare l'assenza di archi
#ifndef NESSUN_ARCO
#define NESSUN_ARCO INFINITY
#endif

//Inizializza la matrice di adiacenza
//input: GRAPH grafo: il grafo di cui inizializzare la matrice
//output: la matrice delle adiacenze
void *InizializzaParametroMatriceAdj(GRAPH grafo);


//Se nel grafo è stato inserito un vertice di troppo modifico la matrice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice di cui inizializzare il parametro
//output: la matrice (modificata quando necessario)
void *InizializzaParametroVerticeMatriceAdj(GRAPH grafo, unsigned int indiceVertice);


//Inserisce un arco nella matrice delle adiacenze relativamente al vertice
//input: - GRAPH grafo: il grafo
//       - void *paramRappr: il parametro della rappresentazione del grafo
//       - unsigned int indiceVertice: il vertice in cui inserire l'arco
//       - GRAPH_ARC arco: l'arco da inserire
//output: il valore NULL
void *InserisciArcoMatriceAdj(GRAPH grafo, void *paramRappr, unsigned int indiceVertice, GRAPH_ARC arco);


//Inizializza l'iteratore per lo scorrimento degli archi nella rappresentazione a matrice
//tale iteratore non è altro che un puntatore ad intero in cui memorizzare l'indice dell'ultimo
//arco letto (ossia dell'ultima colonna) relativa al vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice a cui inizializzare l'iteratore
//output: un puntatore all'intero 0
void *InizializzaIteratoreMatriceAdj(GRAPH grafo, unsigned int indiceVertice);


//Restituisce il primo arco non letto di un vertice
//necessita dell'iteratore
//input: - GRAPH grafo: il grafo, qui non utilizzato
//       - unsigned int indiceVertice: il vertice di cui leggere l'arco successivo, qui
//                                     non utilizzato ed inserito per specifiche
//       - void *iter: un puntatore all'iteratore                  
GRAPH_ARC GetArcoSuccessivoMatriceAdj(GRAPH grafo, unsigned int indiceVertice, void *iter);


//Cerca un arco nella matrice delle adiacenze
//input: - GRAPH grafo: il grafo in cui cercare
//       - unsigned int indiceVertice: il vertice a cui eliminare l'arco
//       - unsigned int indiceArco: l'identificatore del nodo verso cui l'arco da eliminare punta
//output: 1 se l'arco tra i due vertici esiste, 0 altrimenti
int EsisteArcoMatriceAdj(GRAPH grafo, unsigned int indiceVertice, unsigned int indiceArco);


//Ottimizza il parametro della rappresentazione
//utilizzato in caso di eccessiva disparità tra dimensione dell'array di vertici e
//dell'effettivo numero di vertici. Sposta la riga e la colonna di primoIndice sulla
//riga e sulla colonna secondoIndice
//input: - GRAPH grafo: il grafo
//       - unsigned int da: l'indice da cui stpostare
//       - unsigned int verso: l'indice verso cui spostare
//output: il grafo modificato
GRAPH OttimizzaArchiMatriceAdj(GRAPH grafo, unsigned int da, unsigned int verso);


//Cancella un arco dalla matrice di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceNodo: il vertice a cui cancellare l'arco
//       - unsigned int indiceArco: l'indice del nodo a cui l'arco punta
//output: nessuno
void CancellaArcoMatriceAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice);


//Traspone gli archi di un grafo
//input: - GRAPH grafo: il grafo i cui archi vanno trasposti
//       - GRAPH trasposto: il grafo verso cui trasporre gli archi
//output: il grafo trasposto
GRAPH TrasponiArchiMatriceAdj(GRAPH grafo, GRAPH trasposto);


//Dealloca il parametro rappresentativo del nodo
//non fa niente
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: il vertice di cui deallocare la lista
//output: il valore NULL
void *DeallocaParametroVerticeMatriceAdj(GRAPH grafo, unsigned int indiceVertice);


//Dealloca la matrice delle adiacenze
//input: - GRAPH grafo: il grafo
//output: un puntatore a NULL
void *DeallocaParametroMatriceAdj(GRAPH grafo);
