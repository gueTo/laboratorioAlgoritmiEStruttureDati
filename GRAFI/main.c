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
#include "GrafoListaAdiacenza.h"
#include "GrafoMatriceAdiacenza.h"
int main(){

    GRAPH* grafo=NULL;
    int dim=5;


    grafo=init(grafo, dim, insertString, copyString, deleteString, compareString, printString, hashingString, collisionString);

GRAPH_OPERATION *op;
op=(GRAPH_OPERATION*)malloc(sizeof(GRAPH_OPERATION));
op->inizializza=initMatriceAdiacenza;
op->eliminaVertice=cancellaVerticeGrafoMatriceAdiacenza;
op->inserisciVertice=inserisciVerticeGrafoMatriceAdiacenza;
op->inserisciArco=aggiungiArcoGrafoMatriceAdiacenza;
op->eliminaArco=rimuoviArcoGrafoMatriceAdiacenza;
op->esisteArco=esisteArcoGrafoMatriceAdiacenza;
grafo=op->inizializza(grafo);
//    int j=0;
    grafo=inserisciVerticeGrafo(grafo, op, "k", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "a", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "g", NULL);
    //printf("%d\n", j++);
    grafo=inserisciVerticeGrafo(grafo, op, "l", NULL);
    //printf("%d\n", j++);/*
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
    grafo=inserisciVerticeGrafo(grafo, op, "iphonegrosso", NULL);
    printCorrespondenceTable(stdout, grafo->correspondence, grafo->operationID, grafo->operationInt, NULL);
    GRAPH_NODE* k;
    k=cercaVerticeGrafo(grafo, "l", NULL);
/*    printf("%d\n", k==NULL);

    printString(stdout, k->id, NULL);
  */
    grafo=aggiungiArcoGrafo(grafo, op, "a", "k", 3, NULL);
    printf("%d\n", esisteArcoGrafo(grafo, op, "a", "k", NULL));
    grafo=rimuoviArcoGrafo(grafo, op, "a", "k", NULL);
    stampaGrafoMatrice(stdout, grafo);
    grafo=eliminaGrafo(grafo, NULL);
    //grafo=aggiungiArcoGrafo(grafo, grafo->operationID, "a", "g", 3, NULL);

return 0;
}


