/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Prototipi e macro per la gestione dell'I/O di grafi
  per entrambe le rappresentazioni supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "Grafo.h"

//definisco una macro per riavvolgere di un carattere un file pointer
#ifndef UNO_INDIETRO
#define UNO_INDIETRO(fp) fseek(fp, -1, SEEK_CUR)
#endif

//Legge un grafo da un file e lo memorizza
//input: - FILE *fp: il puntatore al file da cui leggere
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - OPERAZIONI funzioniId: le funzioni per gestire gli identificativi
//output: il grafo memorizzato
GRAPH LeggiGrafoDaFile(FILE *fp, GRAPH_FUNC funzioniGrafo, OPERAZIONI *funzioniId);


//Legge i vertici da un file e li memorizza
//input: - FILE *fp: il puntatore al file da cui leggere
//       - GRAPH grafo: il grafo da aggiornare
//       - GRAPH_FUNC funzioniGrafo: le funzioni utilizzate per la rappresentazione
//       - unisgned int ultimoIndice: l'ultimo nodo inserito nell'array di vertiti
//output: la posizione dell'ultimo vertice memorizzato nell'array dei vertici
unsigned int LeggiVerticiDaFile(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int ultimoIndice);


//Legge gli archi da un file e li memorizza
//input: - FILE *fp: il puntatore al file da cui leggere
//       - GRAPH grafo: il grafo da cui leggere gli archi
//       - unsigned int indiceVertice: il vertice a cui aggiungere gli archi
//       - GRAPH_FUNC: le funzioni da utilizzare con la rappresentazione del grafo
//       - unsigned int ultimoIndice: l'ultimo nodo inserito nell'array
//output: la posizione dell'ultimo vertice memorizzato nell'array dei vertici
unsigned int LeggiAdiacenzeDaFile(FILE *fp, GRAPH grafo, unsigned int indiceVertice, GRAPH_FUNC funzioniGrafo, unsigned int ultimoIndice);


//Stampa il grafo
//input: GRAPH grafo: il grafo da stampare
//output: nessuno
void ScriviGrafo(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniRappresentazione);

//Salta caratteri nel file fino al primo non bianco
//in modo che il successivo carattere letto nel file sia
//diverso da ' ' e da una newline
//input: FILE *fp: il file da cui leggere
//output: nessuno
void SaltaCaratteriBianchi(FILE *fp);
