#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fifo.h"
#include "list.h"



#define INFINITY INT_MAX


//static char *NOADJ="NONODEADJACENT";

typedef enum {WHITE, GRAY, BLACK} COLOR;
typedef enum {LIST, MATRIX} graphType;

typedef struct listLink{
    int to;
    int weight;
}listLink;

typedef struct graphNode{
    int node;
    int pred;
    void* info;
    COLOR color;
    list* adj;
}graphNode;

typedef struct graphMatrix{
    int** adjMatrix;
    int sizeOfMatrix;//grandezza effettiva della matrice
    graphNode* nodes;
}graphMatrix;

typedef struct graphList{
    graphNode* nodes;
    int sizeOfArray;
    int bound;
}graphList;

typedef struct graph{
    graphMatrix* GRAPHMATRIX;
    graphList* GRAPHLIST;
    graphType t;
    int numNodes;//numero nodi del grafo
}graph;



graph* makeGraph(graph*, graphType, int );

graph* makeMatrix(graph*);

graph* makeList(graph* );

graph* addVertMat(graph*, void*);

graph* addVertLis(graph*, void*);

graph* addLinkMat(graph*, int, int, int);

graph* removeVertMat(graph*, int);

graph* makeTrasp(graph* );

void BFDMatGraph(graph* , int );

void DFSVisitMat(graph*, int);

void DFSMatGraph(graph*);

void printWayAdjMat(graph* Ngraph, int from, int to);

int printWayMat(graph* Ngraph, int from, int to);
int checkCycleMat(graph* , int );
int haveACycleMatGraph(graph* );



graph* freeGraphMat(graph* );

graph* addLinkLis(graph*, int , int , int);

graph* removeVertLis(graph*, int);



void printInteger(void* toPrint){
    printf("%d", *(int*)(toPrint));
}

void printGraphNode(void* toPrint){
    printf("linked to: ");
    printf("%d", ((listLink*)(toPrint))->to);
    printf(" with weight ");
    printf("%d", ((listLink*)(toPrint))->weight);
    printf("\n");
}

int main(){
    graph* k;
    int i, j, n;
    listLink* p;
    k=makeGraph(k, LIST, 3);
    k=makeList(k);
    list* scroll=NULL;
    k=addVertLis(k, NULL);
    k=addLinkLis(k,0, 1, 0);
    k=addLinkLis(k,3, 1, 0);
    k=addLinkLis(k,3, 0, 0);
    k=addLinkLis(k,3, 2, 0);
    k=addLinkLis(k,0, 3, 0);
    for(i=0; i<k->numNodes; i++){
        printf("\n%d\n", k->GRAPHLIST->nodes[i].node);
        scroll=k->GRAPHLIST->nodes[i].adj;
        j=0;
        while(scroll!=NULL){
                j++;
            printGraphNode((scroll->elem));
            scroll=scroll->next;
            getchar();
        }
        printf(": %d", j);
    }
    k=removeVertLis(k, 2);

    printf("\n\n");
    for(i=0; i<k->numNodes; i++){
        printf("\n%d\n", k->GRAPHLIST->nodes[i].node);
        scroll=k->GRAPHLIST->nodes[i].adj;
        j=0;
        while(scroll!=NULL){
                j++;
            printGraphNode((scroll->elem));
            scroll=scroll->next;
            getchar();
        }
        printf(": %d", j);
    }
    return 0;
}


graph* makeGraph(graph* newGraph, graphType type, int numNodes){
    newGraph=NULL;
    newGraph=(graph*)malloc(sizeof(newGraph));
    newGraph->numNodes=numNodes;
    newGraph->t=type;
    newGraph->GRAPHLIST=NULL;
    newGraph->GRAPHMATRIX=NULL;
    return newGraph;
}

graph* makeMatrix(graph* newGraph){
    graphMatrix* NGM;
    int i, j;
    if(newGraph!=NULL){
        if(newGraph->numNodes>0){
            NGM=(graphMatrix*)malloc(sizeof(graphMatrix));
            NGM->nodes=(graphNode*)malloc(sizeof(graphNode)*(newGraph->numNodes));
            NGM->adjMatrix=(int**)malloc(sizeof(int*)*(newGraph->numNodes));
            NGM->sizeOfMatrix=newGraph->numNodes;
            for(i=0; i<newGraph->numNodes; i++){
                NGM->adjMatrix[i]=(int*)malloc(sizeof(int)*(newGraph->numNodes));
            }
            for(i=0; i<NGM->sizeOfMatrix;i++){
                for(j=0; j<NGM->sizeOfMatrix; j++){
                    NGM->adjMatrix[i][j]=i+j+2;
                }
            }
            for(i=0; i<NGM->sizeOfMatrix; i++){
                NGM->nodes[i].info=NULL;
                NGM->nodes[i].color=WHITE;
                NGM->nodes[i].node=i;
            }
            newGraph->GRAPHMATRIX=NGM;
        }
    }
    return newGraph;
}

graph* addVertMat(graph* GRAPH, void* toAdd){
    int i=0, j=0;
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
                printf("control %d %d\n", GRAPH->numNodes, GRAPH->GRAPHMATRIX->sizeOfMatrix);
            if(GRAPH->numNodes>=GRAPH->GRAPHMATRIX->sizeOfMatrix){
                printf("realloc\n");
                GRAPH->GRAPHMATRIX->sizeOfMatrix=GRAPH->GRAPHMATRIX->sizeOfMatrix+((GRAPH->GRAPHMATRIX->sizeOfMatrix)/2)+2;
                printf("newsize: %d\n", GRAPH->GRAPHMATRIX->sizeOfMatrix);
                GRAPH->GRAPHMATRIX->adjMatrix= (int**)realloc(GRAPH->GRAPHMATRIX->adjMatrix, GRAPH->GRAPHMATRIX->sizeOfMatrix*sizeof(int*));
                for(i = GRAPH->numNodes; i < GRAPH->GRAPHMATRIX->sizeOfMatrix; i++){
                    GRAPH->GRAPHMATRIX->adjMatrix[i] = NULL;
                }
                for (i = 0; i < GRAPH->GRAPHMATRIX->sizeOfMatrix; i++){
                    GRAPH->GRAPHMATRIX->adjMatrix[i] = (int*)realloc(GRAPH->GRAPHMATRIX->adjMatrix[i], (GRAPH->GRAPHMATRIX->sizeOfMatrix)*sizeof(int));
                }

                GRAPH->GRAPHMATRIX->nodes=(graphNode*)realloc(GRAPH->GRAPHMATRIX->nodes, sizeof(graphNode)*(GRAPH->GRAPHMATRIX->sizeOfMatrix));

            }
            for(i=GRAPH->numNodes; i<GRAPH->numNodes+1; i++){
                for(j=0; j<GRAPH->numNodes+1; j++){
                    GRAPH->GRAPHMATRIX->adjMatrix[i][j]=INFINITY;
                    GRAPH->GRAPHMATRIX->adjMatrix[j][i]=INFINITY;
                }
            }
        }else{
            GRAPH->numNodes=1;
            GRAPH=makeMatrix(GRAPH);
            printf("TTT: %d\n", GRAPH->numNodes);
            GRAPH->numNodes=0;
        }
        GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].color=WHITE;
        GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].info=toAdd;
        GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].node=GRAPH->numNodes;
        GRAPH->numNodes++;
    }
    printf("esc\n");
    return GRAPH;
}

graph* addLinkMat(graph* GRAPH, int from, int to, int weight){
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
                if(from<GRAPH->numNodes && to<GRAPH->numNodes && from>=0 && to>=0){
                    GRAPH->GRAPHMATRIX->adjMatrix[from][to]=weight;
                }
        }
    }
    return GRAPH;
}

graph* removeLinkMat(graph* GRAPH, int from, int to){
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
            if(from<GRAPH->numNodes && to<GRAPH->numNodes){
                GRAPH->GRAPHMATRIX->adjMatrix[from][to]=INFINITY;
            }
        }
    }
    return GRAPH;
}

graph* removeVertMat(graph* GRAPH, int toDel){
    graphNode* nodeToDel;
//    void* l;
    int i;
    int j;
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
            if(toDel<GRAPH->numNodes){
                /***GRAPHMATRIX=NULL SE numNodes <=1 **/

                if(GRAPH->numNodes<=1){
                    GRAPH=freeGraphMat(GRAPH);
                    GRAPH->GRAPHMATRIX=NULL;
                }else{

                    nodeToDel=(GRAPH->GRAPHMATRIX->nodes)+toDel;
                    for(i=toDel; i<GRAPH->numNodes-1; i++){
                        GRAPH->GRAPHMATRIX->nodes[i]=GRAPH->GRAPHMATRIX->nodes[i+1];
                        GRAPH->GRAPHMATRIX->nodes[i].node--;
                    }
                    for(i=toDel; i<(GRAPH->numNodes)-1; i++){
                        for(j=0; j<toDel; j++){
                            GRAPH->GRAPHMATRIX->adjMatrix[i][j]=GRAPH->GRAPHMATRIX->adjMatrix[i+1][j];
                        }
                    }
                    for(i=0; i<toDel; i++){
                        for(j=toDel; j<(GRAPH->numNodes)-1; j++){
                            GRAPH->GRAPHMATRIX->adjMatrix[i][j]=GRAPH->GRAPHMATRIX->adjMatrix[i][j+1];
                        }
                    }
                    for(i=toDel; i<(GRAPH->numNodes)-1; i++){
                        for(j=toDel; j<(GRAPH->numNodes)-1; j++){
                            GRAPH->GRAPHMATRIX->adjMatrix[i][j]=GRAPH->GRAPHMATRIX->adjMatrix[i+1][j+1];
                        }
                    }
                    GRAPH->numNodes--;
                    free(nodeToDel->info);
                    free(nodeToDel);
                }
           }
        }
    }
    return GRAPH;
}
/***********************************CALCOLO TRASPOSTO************************/

graph* makeTrasp(graph* original){
    graph* transp=NULL;
    int i, j;
    if(original!=NULL){
        transp=makeGraph(transp, original->t, original->numNodes);
        transp=makeMatrix(transp);
        for(i=0; i<original->numNodes; i++){
            transp->GRAPHMATRIX->nodes[i].node=original->GRAPHMATRIX->nodes[i].node;
/**copia**/            transp->GRAPHMATRIX->nodes[i].info=original->GRAPHMATRIX->nodes[i].info;
        }
        for(i=0; i<original->numNodes; i++){
            for(j=0; j<original->numNodes; j++){
                transp->GRAPHMATRIX->adjMatrix[i][j]=original->GRAPHMATRIX->adjMatrix[j][i];
            }
        }

        transp->GRAPHMATRIX->sizeOfMatrix=transp->numNodes;
    }
    return transp;
}

/****************************************************************************/
void BFDMatGraph(graph* toVisit, int toStart){
    printf("BFD\n");
    graphMatrix* Ngraph=toVisit->GRAPHMATRIX;
    int i=0, visiting=0;
    fifo* tail=NULL;
    fifo* now=NULL;
    for(i=0; i<toVisit->numNodes; i++){
        Ngraph->nodes[i].color=WHITE;
        Ngraph->nodes[i].pred=INFINITY;
    }
    Ngraph->nodes[toStart].color=GRAY;
    tail=enqueue(tail, (void*)toStart);
    while(tail!=NULL){
        now=readFifo(tail);
        visiting=(int)(now->el);
        printf("N%d \n",visiting);
        for(i=0; i<toVisit->numNodes; i++){
            if(Ngraph->adjMatrix[visiting][i]!=INFINITY){
                printf("in i:%d\n", i);
                if(Ngraph->nodes[i].color==WHITE){
                    printf("and this is white\n");
                    tail=enqueue(tail, (void*)i);
                    Ngraph->nodes[i].pred=visiting;
                    Ngraph->nodes[i].color=GRAY;
                }
            }
        }
        if(tail==NULL){
            printf("wat\n");
        }else{
            printf("end %d \n", visiting);
            printf("\n%d\n", (int*)(tail->el));
            Ngraph->nodes[visiting].color=BLACK;
            tail=tail->next;
        }
    }
}

void DFSVisitMat(graph* visiting, int vert){
    visiting->GRAPHMATRIX->nodes[vert].color=GRAY;
    printf("%d ", vert);
    int j;
    for(j=0; j<visiting->numNodes; j++){
        if(visiting->GRAPHMATRIX->adjMatrix[vert][j]!=INFINITY){
            if(visiting->GRAPHMATRIX->nodes[j].color==WHITE){
                visiting->GRAPHMATRIX->nodes[j].pred=vert;
                DFSVisitMat(visiting, j);
            }
        }
    }
    visiting->GRAPHMATRIX->nodes[vert].color=BLACK;
}

void DFSMatGraph(graph* Ngraph){
    int i=0;
    for(i=0; i<Ngraph->numNodes; i++){
        Ngraph->GRAPHMATRIX->nodes[i].color=WHITE;
        Ngraph->GRAPHMATRIX->nodes[i].pred=INFINITY;
    }
    for(i=0; i<Ngraph->numNodes; i++){
        if(Ngraph->GRAPHMATRIX->nodes[i].color==WHITE){
            DFSVisitMat(Ngraph, i);
        }
    }
}



void printWayAdjMat(graph* Ngraph, int from, int to){
    int i=0;
    for(i=0; i<Ngraph->numNodes; i++){
        Ngraph->GRAPHMATRIX->nodes[i].color=WHITE;
    }
    printWayMat(Ngraph, from, to);
    printf("\n");
}

int printWayMat(graph* Ngraph, int from, int to){
    int i=0;
    int res=0;
    if(from==to){
            printf("\neven %d %d\n", from, to);
        res=1;
    }
    if(res!=1){
        Ngraph->GRAPHMATRIX->nodes[to].color=GRAY;
        for(i=0; i<Ngraph->numNodes; i++){
            if(Ngraph->GRAPHMATRIX->adjMatrix[i][to]==1){
                if(Ngraph->GRAPHMATRIX->nodes[i].color==WHITE){
                    res=printWayMat(Ngraph, from, i);
                }
            }
            if(res==1){
                break;
            }
        }
    }
    if(res==1){
        printf("%d ", to);
    }
    return res;
}


int haveACycleMatGraph(graph* Ngraph){
    /*sse ha un arco di ritorno,
    ovvero la dfs incontra un nodo grigio*/
    int i=0;
    int ret=0;
    for(i=0; i<Ngraph->numNodes; i++){
        Ngraph->GRAPHMATRIX->nodes[i].color=WHITE;
    }
    for(i=0; i<Ngraph->numNodes; i++){
        if(Ngraph->GRAPHMATRIX->nodes[i].color==WHITE){
            ret=checkCycleMat(Ngraph, i);
        }
        if(ret==1){
            return ret;
        }
    }
    return ret;
}

int checkCycleMat(graph* Ngraph, int vert){
    /**
    0: ha ciclo
    1: ha ciclo
    **/
    /*DFS modificata per cercare il ciclo*/
    Ngraph->GRAPHMATRIX->nodes[vert].color=GRAY;
    int j;
    int ret=0;
    for(j=0; j<Ngraph->numNodes; j++){
        if(Ngraph->GRAPHMATRIX->adjMatrix[vert][j]!=INFINITY){
            if(Ngraph->GRAPHMATRIX->nodes[j].color==WHITE){
                Ngraph->GRAPHMATRIX->nodes[j].pred=vert;
                ret=checkCycleMat(Ngraph, j);
            }else if(Ngraph->GRAPHMATRIX->nodes[j].color==GRAY){
                ret=1;
                return ret;
            }
        }
    }
    Ngraph->GRAPHMATRIX->nodes[vert].color=BLACK;
    return ret;
}

graph* freeGraphMat(graph* toDel){
    int i;
    graphMatrix* temp;
    if(toDel!=NULL){
        if(toDel->GRAPHMATRIX!=NULL){
            for(i=0; i<toDel->GRAPHMATRIX->sizeOfMatrix; i++){
                free(toDel->GRAPHMATRIX->adjMatrix[i]);
            }
            free(toDel->GRAPHMATRIX->adjMatrix);
            for(i=0; i<toDel->GRAPHMATRIX->sizeOfMatrix; i++){
                free(((toDel->GRAPHMATRIX->nodes)+i)->info);
            }
            free(toDel->GRAPHMATRIX->nodes);
            toDel->GRAPHMATRIX->nodes=NULL;
            toDel->GRAPHMATRIX->adjMatrix=NULL;
            temp=toDel->GRAPHMATRIX;
        }
        toDel->GRAPHMATRIX=NULL;

    }
    return toDel;
}




/**********************************/



graph* makeList(graph* newGraph){
    int i;
    graphList* NGL;
    if(newGraph!=NULL){
        if(newGraph->numNodes>0){
            NGL=(graphList*)malloc(sizeof(graphList));
            /***/
            NGL->sizeOfArray=newGraph->numNodes;
            /***/
            NGL->nodes=(graphNode*)malloc(sizeof(graphNode)*(NGL->sizeOfArray));
            for(i=0; i<NGL->sizeOfArray; i++){
                NGL->nodes[i].adj=NULL;
                NGL->nodes[i].node=i;
            }
            newGraph->GRAPHLIST=NGL;
        }
    }
    newGraph->t=LIST;
    return newGraph;
}

graph* addVertLis(graph* Ngraph, void* inf){
    if(Ngraph!=NULL){
        if(Ngraph->GRAPHLIST!=NULL){
            if(Ngraph->numNodes>=Ngraph->GRAPHLIST->sizeOfArray){
                Ngraph->GRAPHLIST->sizeOfArray=Ngraph->GRAPHLIST->sizeOfArray+((Ngraph->GRAPHLIST->sizeOfArray)/2);
                Ngraph->GRAPHLIST->nodes=(graphNode*)realloc(Ngraph->GRAPHLIST->nodes, sizeof(graphNode)*Ngraph->GRAPHLIST->sizeOfArray);
            }
            Ngraph->GRAPHLIST->nodes[Ngraph->numNodes].info=inf;
            Ngraph->GRAPHLIST->nodes[Ngraph->numNodes].node=Ngraph->numNodes;
            Ngraph->GRAPHLIST->nodes[Ngraph->numNodes].adj=NULL;
            (Ngraph->numNodes)++;
        }
    }
    return Ngraph;
}

void* copyListLink(void* original, void* ret){
    ret=(listLink*)malloc(sizeof(listLink));
    ((listLink*)ret)->to=((listLink*)original)->to;;
    ((listLink*)ret)->weight=((listLink*)original)->weight;
    return ret;
}

int compareListLink(void* a, void* b){
    int toa;
    int tob;
    toa=((listLink*)a)->to;
    tob=((listLink*)b)->to;
    printf("\n%d %d", toa, tob);
    if(toa>tob)
        return 1;
    if(toa<tob)
        return -1;
    return 0;
}

void deleteListLink(void* toDel){
    free(((listLink*)toDel));
}

graph* addLinkLis(graph* Ngraph, int from, int to, int wei){
    listLink *ins;
    if(Ngraph!=NULL){
        if(Ngraph->GRAPHLIST!=NULL){
            if(from<Ngraph->numNodes && to<Ngraph->numNodes && from>=0 && to>=0){
                ins=(listLink*)malloc(sizeof(listLink));
                ins->to=to;
                ins->weight=wei;
                Ngraph->GRAPHLIST->nodes[from].adj=insertNodeList(Ngraph->GRAPHLIST->nodes[from].adj, ins, copyListLink);
            }
        }
    }
    return Ngraph;
}



graph* removeVertLis(graph* Ngraph, int toDel){
    int i;
    list* scroll;
    list* dec;
    void* info;
    int* t=toDel;
    if(Ngraph!=NULL){
        if(Ngraph->GRAPHLIST!=NULL){
            if(toDel<Ngraph->numNodes){
                scroll=Ngraph->GRAPHLIST->nodes[toDel].adj;
                info=Ngraph->GRAPHLIST->nodes[toDel].info;
                for(i=toDel;i<Ngraph->numNodes-1; i++){
                    Ngraph->GRAPHLIST->nodes[i].adj=Ngraph->GRAPHLIST->nodes[i+1].adj;
                    Ngraph->GRAPHLIST->nodes[i].info=Ngraph->GRAPHLIST->nodes[i+1].info;
                }
                Ngraph->numNodes--;
                for(i=0; i<Ngraph->numNodes; i++){
                    dec=Ngraph->GRAPHLIST->nodes[i].adj;
                    if(dec!=NULL){
                        dec=deleteNodeFromList(dec, Ngraph->GRAPHLIST->nodes[toDel].adj->elem, compareListLink, deleteListLink);
                    }
                    while(dec!=NULL){
                        if(((listLink*)(dec->elem))->to>toDel){
                            ((listLink*)(dec->elem))->to--;
                        }
                        dec=dec->next;
                    }
                }
                freeList(scroll, deleteListLink);
                free(info);
            }
        }
    }
    return Ngraph;
}
