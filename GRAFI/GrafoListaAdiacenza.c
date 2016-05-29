#include "data.h"
#include <stdio.h>
#include "grafi.h"
#include "GrafoListaAdiacenza.h"


void printArco(FILE* fp, void* toPrint, void* parameter){
    fprintf(fp, "->%d-%d", ((ARCO_DATA*)(toPrint))->indice, ((ARCO_DATA*)(toPrint))->peso);
}

int compareArco(void* a, void* b, void* parameter){
    return compareInteger(&(((ARCO_DATA*)(a))->indice),&(((ARCO_DATA*)(b))->indice), NULL);
}


void* copyArco(void* cop, void* original, void* parameter){
    ARCO_DATA* ret=(ARCO_DATA*)malloc(sizeof(ARCO_DATA));
    ret->indice=((ARCO_DATA*)(original))->indice;
    ret->peso=((ARCO_DATA*)(original))->peso;
    cop=ret;
    return cop;
}

void* deleteArco(void* toDelete, void* parameter){
    free(toDelete);
    toDelete=NULL;
    return toDelete;
}


GRAPH* initListaAdiacenza(GRAPH* grafo){
    GRAPH_LIST_ADJ* listaAdiacenze=NULL;
    listaAdiacenze=(GRAPH_LIST_ADJ*)malloc(sizeof(GRAPH_LIST_ADJ));
    listaAdiacenze->adj=(LIST*)malloc(sizeof(LIST)*grafo->dimensioneArrayVertici);
    int i=0;
    for(i=0; i<grafo->dimensioneArrayVertici; i++){
        listaAdiacenze->adj[i]=NULL;
    }
    listaAdiacenze->adjOperation=initListOperation(NULL, copyArco, deleteArco, compareArco, printArco, NULL, NULL);
    grafo->rapp=listaAdiacenze;
    return grafo;
}

GRAPH* inserisciVerticeGrafoListaAdiacenza(GRAPH* grafo){
    int i;
//    LIST* temp;

    LIST* nuovo=(LIST*)malloc(sizeof(LIST)*grafo->dimensioneArrayVertici);

    for(i=0; i<grafo->dimensioneArrayVertici; i++){
        nuovo[i]=NULL;
    }
    for(i=0; i<grafo->numVerticiUsati; i++){
        nuovo[i]=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[i];
    }
//    temp=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj;
    ((GRAPH_LIST_ADJ*)(grafo->rapp))->adj=nuovo;
//    free(temp);
    return grafo;
}

GRAPH* cancellaVerticeGrafoListaAdiacenza(GRAPH* grafo, int indice){
    int i;
    LIST scroll;
    ARCO_DATA temp;
    temp.indice=indice;
    temp.peso=0;
    for(i=0; i<grafo->numVerticiUsati; i++){
        scroll=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[i];
        scroll=deleteNodeFromList(scroll, &temp, ((GRAPH_LIST_ADJ*)(grafo->rapp))->adjOperation, NULL);
    }
    scroll=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[indice];
    deleteList(scroll, ((GRAPH_LIST_ADJ*)(grafo->rapp))->adjOperation, NULL);
    ((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[indice]=NULL;
    return grafo;
}

GRAPH* aggiungiArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a, int peso){
    ARCO_DATA temp;
    temp.indice=a;
    temp.peso=peso;
    ((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[da]=insertNewNode(((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[da], &temp, ((GRAPH_LIST_ADJ*)(grafo->rapp))->adjOperation, NULL);
    return grafo;
}

GRAPH* rimuoviArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a){
    LIST scroll;
    ARCO_DATA temp;
    temp.indice=a;
    temp.peso=0;
    scroll=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[da];
    scroll=deleteNodeFromList(scroll, &temp, ((GRAPH_LIST_ADJ*)(grafo->rapp))->adjOperation, NULL);
    return grafo;
}

int esisteArcoGrafoListaAdiacenza(GRAPH* grafo, int da, int a){
    LIST scroll;
    ARCO_DATA temp;
    temp.indice=a;
    temp.peso=0;
    scroll=((GRAPH_LIST_ADJ*)(grafo->rapp))->adj[da];
    if(searchNode(scroll, &temp, ((GRAPH_LIST_ADJ*)(grafo->rapp))->adjOperation, NULL)!=NULL)
        return 1;
    return 0;
}

