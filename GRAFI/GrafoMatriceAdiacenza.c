#include "grafi.h"
#include "GrafoMatriceAdiacenza.h"

GRAPH* initMatriceAdiacenza(GRAPH* grafo){
    GRAPH_MATR_ADJ* prova=NULL;
    int j;
    int k=0;
    if(grafo!=NULL){
        prova=(GRAPH_MATR_ADJ*)malloc(sizeof(GRAPH_MATR_ADJ));
        prova->rapp=(int**)malloc(sizeof(int*)*grafo->dimensioneArrayVertici);
        for(j=0; j<grafo->dimensioneArrayVertici; j++){
            prova->rapp[j]=(int*)malloc(sizeof(int)*grafo->dimensioneArrayVertici);
        }
        for(j=0; j<grafo->dimensioneArrayVertici; j++){
            for(k=0; k<grafo->dimensioneArrayVertici; k++){
                prova->rapp[j][k]=NESSUN_ARCO;
            }
        }
        grafo->rapp=prova;
    }
    return grafo;
}

GRAPH* inserisciVerticeGrafoADJ(GRAPH* grafo){
    int j, k;
    int** nuovaMatrice;
    if(grafo!=NULL){
        nuovaMatrice=(int**)malloc(sizeof(int*)*grafo->dimensioneArrayVertici);
        for(j=0; j<grafo->dimensioneArrayVertici; j++)
            nuovaMatrice[j]=(int*)malloc(sizeof(int)*grafo->dimensioneArrayVertici);
        for(j=0; j<grafo->dimensioneArrayVertici; j++){
            for(k=0; k<grafo->dimensioneArrayVertici; k++){
                nuovaMatrice[j][k]=NESSUN_ARCO;//NESSUN_ARCO;
            }
        }
        for(j=0; j<grafo->numVerticiUsati; j++){
            for(k=0; k<grafo->numVerticiUsati; k++){
                nuovaMatrice[j][k]=((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[j][k];
            }
        }
        ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp=nuovaMatrice;
    }
        //free(grafo->vertici);
    return grafo;
}

GRAPH* cancellaVerticeGrafoADJ(GRAPH* grafo, int indice){
    int i;
    for(i=0; i<grafo->numVerticiUsati; i++){
        ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[i][indice]=NESSUN_ARCO;
        ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[indice][i]=NESSUN_ARCO;
    }
    return grafo;
}

GRAPH* aggiungiArcoGrafoADJ(GRAPH* grafo, int da, int a, int peso){
    ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[da][a]=peso;
    return grafo;
}

GRAPH* rimuoviArcoGrafoADJ(GRAPH* grafo, int da, int a){
    ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[da][a]=NESSUN_ARCO;
    return grafo;
}

int esisteArcoGrafoADJ(GRAPH* grafo, int da, int a){
    if(((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[da][a]==NESSUN_ARCO){
        return 1;
    }
    return 0;
}
