#ifndef _GRAFO_MATRICE_ADIACENZA_H_
    #define _GRAFO_MATRICE_ADIACENZA_H_


    #include "grafi.h"

    typedef struct GRAPH_MATR_ADJ{
        int** rapp;
    }GRAPH_MATR_ADJ;


    GRAPH* initMatriceAdiacenza(GRAPH* grafo);
    GRAPH* inserisciVerticeGrafoMatriceAdiacenza(GRAPH* grafo);
    GRAPH* cancellaVerticeGrafoMatriceAdiacenza(GRAPH* grafo, int indice);
    GRAPH* aggiungiArcoGrafoMatriceAdiacenza(GRAPH* grafo, int da, int a, int peso);
    GRAPH* rimuoviArcoGrafoMatriceAdiacenza(GRAPH* grafo, int da, int a);
    int esisteArcoGrafoMatriceAdiacenza(GRAPH* grafo, int da, int a);

#endif
