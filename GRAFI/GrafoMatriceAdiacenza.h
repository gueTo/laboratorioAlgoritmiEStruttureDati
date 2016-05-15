#ifndef _GRAFO_MATRICE_ADIACENZA_H_
    #define _GRAFO_MATRICE_ADIACENZA_H_


#include "grafi.h"

typedef struct GRAPH_MATR_ADJ{
    int** rapp;
}GRAPH_MATR_ADJ;


GRAPH* initMatriceAdiacenza(GRAPH* grafo);
GRAPH* inserisciVerticeGrafoADJ(GRAPH* grafo);
GRAPH* cancellaVerticeGrafoADJ(GRAPH* grafo, int indice);
GRAPH* aggiungiArcoGrafoADJ(GRAPH* grafo, int da, int a, int peso);
GRAPH* rimuoviArcoGrafoADJ(GRAPH* grafo, int da, int a);
int esisteArcoGrafoADJ(GRAPH* grafo, int da, int a);

#endif
