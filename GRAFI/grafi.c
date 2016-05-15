#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "correspondence.h"
#include "list.h"
#include "grafi.h"
#include "GrafoMatriceAdiacenza.h"


GRAPH_NODE* nuovoVertice(GRAPH* grafo, GRAPH_NODE* nodo, void* id){
    nodo=(GRAPH_NODE*)malloc(sizeof(GRAPH_NODE));
    nodo->id=grafo->operationID->fcopy(nodo->id, id, NULL);
    nodo->color=WHITE;
    return nodo;
}


GRAPH* inserisciVerticeGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* id, void* parameter){
    int nuovoIndice;
    int i;
    //int j, k;
    CORRESPONDENCE* nuovaCorrispondenza;
    GRAPH_NODE** nuovo;
  //  int**nuovaMatrice;
    if(grafo!=NULL){
        if(listIsEmpty(grafo->listaNodiLiberi)){
            grafo->dimensioneArrayVertici=grafo->dimensioneArrayVertici*2+1;
            nuovo=(GRAPH_NODE**)malloc(sizeof(GRAPH_NODE*)*grafo->dimensioneArrayVertici);
            for(i=0; i<grafo->dimensioneArrayVertici; i++){
                nuovo[i]=NULL;
            }
            for(i=0; i<grafo->numVerticiUsati; i++){
                nuovo[i]=nuovoVertice(grafo, nuovo[i], id);
                /**eccetera**/
            }
            for(i=grafo->dimensioneArrayVertici-1; i>=grafo->numVerticiUsati; i--){
                grafo->listaNodiLiberi=push(grafo->listaNodiLiberi, grafo->operationInt, &i, NULL);
            }

            for(i=0; i<grafo->numVerticiUsati; i++){
                if(grafo->vertici[i]!=NULL){
                    grafo->vertici[i]->id=grafo->operationID->funfree(grafo->vertici[i]->id, NULL);
                    free(grafo->vertici[i]);
                }
            }
            grafo->vertici=nuovo;

            grafo=operation->inserisciVertice(grafo);
        }
        nuovoIndice=*(int*)(top(grafo->listaNodiLiberi)->element);
        grafo->listaNodiLiberi=pop(grafo->listaNodiLiberi);
        grafo->vertici[nuovoIndice]=nuovoVertice(grafo, grafo->vertici[nuovoIndice], id);
        grafo->numVerticiUsati++;
        nuovaCorrispondenza=newCorrespondence(id, nuovoIndice, grafo->correspondence->correspondenceID->l_operation->cpy, NULL);
        grafo->correspondence=insertIntoCorrespondenceTable(grafo->correspondence, nuovaCorrispondenza, NULL);
    }
    return grafo;
}

GRAPH_NODE* cercaVerticeGrafo(GRAPH* grafo, void* ID, void* parameter){
    CORRESPONDENCE* find=NULL;
    if(grafo!=NULL){
        find=searchIDIntoCorrespondenceTable(grafo->correspondence, ID, parameter);
        if(find!=NULL){
            return grafo->vertici[find->index];
        }
    }
    return NULL;
}

GRAPH* cancellaVerticeGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* ID, void* parameter){
    CORRESPONDENCE* find=NULL;
    int indice;
//    int i;
    if(grafo!=NULL){
        find=searchIDIntoCorrespondenceTable(grafo->correspondence, ID, parameter);
        if(find!=NULL){
            indice=find->index;
            grafo->correspondence=removeFromCorrespondenceTableByID(grafo->correspondence, ID, parameter);

            grafo->vertici[indice]=grafo->operationID->funfree(grafo->vertici[indice]->id, parameter);
            free(grafo->vertici[indice]);
            grafo->vertici[indice]=NULL;
            grafo=operation->eliminaVertice(grafo, indice);
            grafo->numVerticiUsati--;
        }
    }
    return grafo;
}

GRAPH* aggiungiArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, int peso, void* parameter){
    CORRESPONDENCE *findDa=NULL;
    CORRESPONDENCE *findA=NULL;
    if(grafo!=NULL){
        findA=searchIDIntoCorrespondenceTable(grafo->correspondence, a, parameter);
        if(findA!=NULL){
            findDa=searchIDIntoCorrespondenceTable(grafo->correspondence, da, parameter);
            if(findDa!=NULL){
                grafo=operation->inserisciArco(grafo, findDa->index, findA->index, peso);
                //((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[findDa->index][findA->index]=peso;
            }
        }
    }
    return grafo;
}

GRAPH* rimuoviArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, void* parameter){
    CORRESPONDENCE *findDa=NULL;
    CORRESPONDENCE *findA=NULL;
    if(grafo!=NULL){
        findA=searchIDIntoCorrespondenceTable(grafo->correspondence, a, parameter);
        if(findA!=NULL){
            findDa=searchIDIntoCorrespondenceTable(grafo->correspondence, da, parameter);
            if(findDa!=NULL){
                grafo=operation->eliminaArco(grafo, findDa->index, findA->index);
                //((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[findDa->index][findA->index]=NESSUN_ARCO;
            }
        }
    }
    return grafo;
}

int esisteArcoGrafo(GRAPH* grafo, GRAPH_OPERATION* operation, void* da, void* a, void* parameter){
    CORRESPONDENCE* findDa=NULL;
    CORRESPONDENCE* findA=NULL;
    if(grafo!=NULL){
        findDa=searchIDIntoCorrespondenceTable(grafo->correspondence, da, parameter);
        if(findDa!=NULL){
            findA=searchIDIntoCorrespondenceTable(grafo->correspondence, a, parameter);
            if(findA!=NULL){
                return operation->esisteArco(grafo, findDa->index, findA->index);
            }
        }
    }
    return 0;
}

void stampaGrafoMatrice(FILE* fp, GRAPH* grafo){
    int i, j;
    if(grafo!=NULL){
        if(grafo->rapp!=NULL){
            for(i=0; i<grafo->numVerticiUsati; i++){
                for(j=0; j<grafo->numVerticiUsati; j++){
                    if(((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[i][j]!=NESSUN_ARCO)
                        fprintf(fp, "%d ", ((GRAPH_MATR_ADJ*)(grafo->rapp))->rapp[i][j]);
                    else fprintf(fp, "X ");
                }
                fprintf(fp, "\n");
            }
        }
    }
}

GRAPH* eliminaGrafo(GRAPH* grafo, void* parameter){
    int i=0;
    if(grafo!=NULL){
        for(i=0; i<grafo->numVerticiUsati; i++){
            if(grafo->vertici[i]!=NULL){
                grafo->vertici[i]->id=grafo->operationID->funfree(grafo->vertici[i]->id, NULL);
                free(grafo->vertici[i]);
            }
        }
        //free(grafo->vertici);
        freeCorrespondenceTable(grafo->correspondence, NULL);
        grafo->listaNodiLiberi=deleteList(grafo->listaNodiLiberi, grafo->operationInt, NULL);
        free(grafo->operationID);
        free(grafo->operationInt);
        free(grafo);
        grafo=NULL;
    }
    return grafo;
}

CORRESPONDENCE_TABLE* initCorrGraph(GRAPH* grafo, HASH_OPERATION* hash_id, LIST_OPERATION* list_id){
    HASH_OPERATION* h_id, *h_index;
    LIST_OPERATION* l_id, *l_index;
//    h_id=initHashOperation(hashCorrespondenceID, collisionString);
//    l_id=initListOperation(insertString, copyString, deleteString, compareString, printString);
    h_index=initHashOperation(hashCorrespondenceIndex, collisionInteger);
    l_index=initListOperation(insertInteger, copyInteger, deleteInteger, compareInteger, printInteger);
    grafo->correspondence=initCorresponcendeTable(grafo->dimensioneArrayVertici, list_id, l_index, hash_id, h_index);
    return grafo->correspondence;
}


GRAPH* init(GRAPH* graf,int dim, FUNINS ins, FUNCPY cpy, FUNDEL del, FUNCOM comp, FUNPRINT pri, FUNHASH has, FUNCOLLISION coll){
    int i=1;
    HASH_OPERATION* h_id;
    LIST_OPERATION* l_id;
    GRAPH* grafo=NULL;
    grafo=(GRAPH*)malloc(sizeof(GRAPH));

    grafo->operationInt=initListOperation(insertInteger, copyInteger, deleteInteger, compareInteger, printInteger);
    grafo->operationID=initFUNCTDATA_2(ins, cpy, NULL, comp, NULL, pri, del);
    grafo->dimensioneArrayVertici=dim;
    grafo->vertici=(GRAPH_NODE**)malloc(sizeof(GRAPH_NODE*));
    for(i=0; i<grafo->dimensioneArrayVertici; i++){
        grafo->vertici[i]=NULL;
    }

    grafo->numVerticiUsati=0;
    grafo->listaNodiLiberi=NULL;
    for(i=grafo->dimensioneArrayVertici-1; i>=0; i--){
        grafo->listaNodiLiberi=push(grafo->listaNodiLiberi, grafo->operationInt, &i, NULL);
    }
    h_id=initHashOperation(has, coll);
    l_id=initListOperation(ins, cpy, del, comp, pri);
    grafo->correspondence=initCorrGraph(grafo, h_id, l_id);

    return grafo;
}
