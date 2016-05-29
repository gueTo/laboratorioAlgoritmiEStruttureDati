#ifndef _GRAFO_LISTA_ADIACENZA_H_
    #define _GRAFO_LISTA_ADIACENZA_H_


    #include <stdio.h>
    #include "data.h"
    #include "grafi.h"

    typedef struct ARCO_DATA{
        int indice;
        int peso;
    }ARCO_DATA;

    typedef struct GRAPH_LIST_ADJ{
        LIST* adj;
        LIST_OPERATION* adjOperation;
    }GRAPH_LIST_ADJ;


    void printArco(FILE* fp, void* toPrint, void* parameter);
    int compareArco(void* a, void* b, void* parameter);
    void* copyArco(void* cop, void* original, void* parameter);
    void* deleteArco(void* toDelete, void* parameter);

    GRAPH* initListaAdiacenza(GRAPH* grafo);
    GRAPH* inserisciVerticeGrafoListaAdiacenza(GRAPH* grafo);
    GRAPH* cancellaVerticeGrafoListaAdiacenza(GRAPH* grafo, int indice);
    GRAPH* aggiungiArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a, int peso);
    GRAPH* rimuoviArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a);
    int esisteArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a);

#endif
