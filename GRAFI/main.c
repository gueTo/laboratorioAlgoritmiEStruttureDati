/****************************************
	Antonio Guerriero
	N86/000900

INSERIRE DESCRIZIONE CODICE

****************************************/
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "correspondence.h"
#include "grafi.h"
#include "GrafoMatriceAdiacenza.h"
int main(){

    GRAPH* grafo=NULL;
    int dim=8;



    grafo=init(grafo, dim,insertString, copyString, deleteString, compareString, printString, hashingString, collisionString);
GRAPH_OPERATION *op;
op=(GRAPH_OPERATION*)malloc(sizeof(GRAPH_OPERATION));
op->inizializza=initMatriceAdiacenza;
op->eliminaVertice=cancellaVerticeGrafoADJ;
op->inserisciVertice=inserisciVerticeGrafoADJ;
op->inserisciArco=aggiungiArcoGrafoADJ;
op->eliminaArco=rimuoviArcoGrafoADJ;
op->esisteArco=esisteArcoGrafoADJ;
grafo=op->inizializza(grafo);


//    int j=0;
    grafo=inserisciVerticeGrafo(grafo, op, "k", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "a", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "g", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "l", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "cacca", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "pupu", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "enne", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "prova", NULL);
    //printf("%d\n", j++);

    grafo=inserisciVerticeGrafo(grafo, op, "sette", NULL);
    grafo=inserisciVerticeGrafo(grafo, op, "culocane", NULL);
    grafo=inserisciVerticeGrafo(grafo, op, "iphonegrossopiugrosso", NULL);

    grafo=aggiungiArcoGrafo(grafo, op, "a", "g", 7, NULL);
    grafo=aggiungiArcoGrafo(grafo, op, "g", "k", 3, NULL);
    grafo=aggiungiArcoGrafo(grafo, op, "enne", "pupu", 1, NULL);
    grafo=aggiungiArcoGrafo(grafo, op, "a", "a", 0, NULL);
    stampaGrafoMatrice(stdout, grafo);
    grafo=cancellaVerticeGrafo(grafo, op, "a", NULL);

    stampaGrafoMatrice(stdout, grafo);

    grafo=eliminaGrafo(grafo, NULL);
/**/
    return 0;
}

