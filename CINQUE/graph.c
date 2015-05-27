#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY INT_MAX


typedef enum {WHITE, GRAY, BLACK} COLOR;
typedef enum {LIST, MATRIX} graphType;

typedef struct graphNode{
    int node;
    int pred;
    void* info;
    COLOR color;
    //list adj;
}graphNode;

typedef struct graphMatrix{
    int** adjMatrix;
    int sizeOfMatrix;//grandezza effettiva della matrice
    graphNode* nodes;
}graphMatrix;

typedef struct graphList{
    graphNode* adjList;
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

graph* addVertMat(graph*, void*);

graph* addLinkMat(graph*, int, int, int);

graph* removeVertMat(graph*, int);

int main(){
    graph* k;
    k=makeGraph(k, MATRIX, 5);
    k=makeMatrix(k);
    int i, j;
    for(i=0; i<k->GRAPHMATRIX->sizeOfMatrix; i++){
        for(j=0; j<k->GRAPHMATRIX->sizeOfMatrix; j++){
            printf("%d ", k->GRAPHMATRIX->adjMatrix[i][j]);
        }
        printf("\n");
    }

//    k=addLinkMat(k, 5, 6, 3);
//    k=addLinkMat(k, 4, 4, 0);
    printf("\n");
    for(i=0; i<k->numNodes; i++){
        for(j=0; j<k->numNodes; j++){
            printf("%d ", k->GRAPHMATRIX->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i=0; i<k->numNodes;i++){
        printf("%d ", k->GRAPHMATRIX->nodes[i].node);
    }
    printf("\n%d, %d", k->numNodes, k->GRAPHMATRIX->sizeOfMatrix);

    k=removeVertMat(k, 4);

    printf("\n\\****************************************\\\n");
    for(i=0; i<k->numNodes; i++){
        for(j=0; j<k->numNodes; j++){
            printf("%d ", k->GRAPHMATRIX->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i=0; i<k->numNodes;i++){
        printf("%d ", k->GRAPHMATRIX->nodes[i].node);
    }
    printf("\n%d, %d", k->numNodes, k->GRAPHMATRIX->sizeOfMatrix);

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
    graphMatrix* NGM=(graphMatrix*)malloc(sizeof(graphMatrix));
    NGM->nodes=(graphNode*)malloc(sizeof(graphNode)*(newGraph->numNodes));
    int i, j;
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
    return newGraph;
}

graph* addVertMat(graph* GRAPH, void* toAdd){
    int i=0, j=0;
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
            if(GRAPH->numNodes<=GRAPH->GRAPHMATRIX->sizeOfMatrix){
                GRAPH->GRAPHMATRIX->sizeOfMatrix=GRAPH->GRAPHMATRIX->sizeOfMatrix+((GRAPH->GRAPHMATRIX->sizeOfMatrix)/2);
                GRAPH->GRAPHMATRIX->adjMatrix= (int**)realloc(GRAPH->GRAPHMATRIX->adjMatrix, GRAPH->GRAPHMATRIX->sizeOfMatrix*sizeof(int*));
                for(i = GRAPH->numNodes; i < GRAPH->GRAPHMATRIX->sizeOfMatrix; i++){
                    GRAPH->GRAPHMATRIX->adjMatrix[i] = NULL;
                }
                for (i = 0; i < GRAPH->GRAPHMATRIX->sizeOfMatrix; i++){
                    GRAPH->GRAPHMATRIX->adjMatrix[i] = (int*)realloc(GRAPH->GRAPHMATRIX->adjMatrix[i], (GRAPH->GRAPHMATRIX->sizeOfMatrix)*sizeof(int));
                }
                for(i=GRAPH->numNodes; i<GRAPH->GRAPHMATRIX->sizeOfMatrix; i++){
                    GRAPH->GRAPHMATRIX->nodes[i].info=NULL;
                    for(j=0; j<=GRAPH->numNodes; j++){
                        GRAPH->GRAPHMATRIX->adjMatrix[i][j]=INFINITY;
                        GRAPH->GRAPHMATRIX->adjMatrix[j][i]=INFINITY;
                    }
                }
                GRAPH->GRAPHMATRIX->nodes=(graphNode*)realloc(GRAPH->GRAPHMATRIX->nodes, sizeof(graphNode)*(GRAPH->GRAPHMATRIX->sizeOfMatrix));
            }
            GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].color=WHITE;
            GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].info=toAdd;
            GRAPH->GRAPHMATRIX->nodes[GRAPH->numNodes].node=GRAPH->numNodes;
            GRAPH->numNodes++;
        }
    }
    return GRAPH;
}

graph* addLinkMat(graph* GRAPH, int from, int to, int weight){
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
                if(from<GRAPH->numNodes && to<GRAPH->numNodes){
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
}

graph* removeVertMat(graph* GRAPH, int toDel){
    graphNode* nodeToDel;
    void* l;
    int i;
    int j;
    if(GRAPH!=NULL){
        if(GRAPH->GRAPHMATRIX!=NULL){
            if(toDel<GRAPH->numNodes){
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
    return GRAPH;
}
/***********************************CALCOLO TRASPOSTO************************/


//void BFDMatGraph(adjMatGraph* Ngraph, int toStart){
/*
void BFDMatGraph(graph* toVisit, int toStart){
    graphMatrix* Ngraph=toVisit->GRAPHMATRIX;
    int i=0, visiting=0;
    fifoNode* tail=NULL;
    fifoNode* now=NULL;
    for(i=0; i<Ngraph->numNodes; i++){
        Ngraph->nodes[i].color=WHITE;
        Ngraph->nodes[i].pred=INFINITY;
    }
    Ngraph->nodes[toStart].color=GRAY;
    tail=enqueue(tail, (void*)toStart);
    while(tail!=NULL){
        now=readFifo(tail);
        visiting=(int)(now->el);
        printf("N%d \n",visiting);
        for(i=0; i<Ngraph->numNodes; i++){
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
            printf("\n%d\n", *(int*)(tail->el));
            Ngraph->nodes[visiting].color=BLACK;
            tail=tail->next;
        }
    }
}
*/
