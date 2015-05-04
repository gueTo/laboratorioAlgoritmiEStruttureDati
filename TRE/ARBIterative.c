#include <stdio.h>
#include <stdlib.h>
#include "ARBIterative.h"

/**CREAZIONE NUOVO NODO**/
ARB* newARBNode(void* toInsert, FUNCPY fcopy){
    ARB* newNode=NULL;
    newNode=(ARB*)malloc(sizeof(ARB));//ALLOCAZIONENUOVO NODO
    newNode->element=fcopy(newNode->element, toInsert);//ALLOCAZIONE MEMORIA PER LA STRINGA DA INSERIRE
    newNode->sx=NULL;
    newNode->dx=NULL;
    return newNode;
}

/***DEALLOCAZIONE NODO***/
ARB* freeARBNode(ARB* node, FUNDEL del){
    del(node->element);
    free(node);
    return NULL;
}

int countARBNode(ARB* ROOT){
	if(ROOT!=NULL){
		return 1+countARBNode(ROOT->sx)+countARBNode(ROOT->dx);
	}else return 0;
}
/*****************FUNZIONI RICHIESTE********************/

ARB* insertARBNodeIterative(ARB* ROOT, void* toIns, FUNCOM compare, FUNCPY fcopy){
    ARB* temp;
    lifo* stackTree;
    int stop;
    int cmp;
    if(ROOT!=NULL){
        temp=ROOT;
        stackTree=(lifo*)malloc(sizeof(lifo));
        stop=0;
        cmp=0;
        while(stop!=1 && temp!=NULL){
            cmp=compare(temp->element, toIns);
            stackTree=lifoPush(stackTree, temp);
            if(cmp<0){
                temp=temp->dx;
            }else if(cmp>0){
                temp=temp->sx;
            }else stop=1;
        }
        if(temp==NULL){
            temp=(ARB*)((lifoTop(stackTree))->element);
            if(cmp<0)
                temp->dx=newARBNode(toIns, fcopy);
            else
                temp->sx=newARBNode(toIns, fcopy);
        }
    }else{
        ROOT=newARBNode(toIns, fcopy);
    }
    return ROOT;
}

ARB* deleteARBIterative(ARB* ROOT, FUNDEL fdelete){
    lifo* stackTree=NULL;
    lifo* topStack=NULL;
    ARB* toControl=NULL;
    if(ROOT!=NULL){
        stackTree=lifoPush(stackTree, ROOT);
        while(!lifoIsEmpty(stackTree)){
            topStack=lifoTop(stackTree);
            toControl=(ARB*)(topStack->element);
            stackTree=lifoPop(stackTree);
            if(toControl->sx!=NULL){
                stackTree=lifoPush(stackTree, toControl->sx);
            }
            if(toControl->dx!=NULL){
                stackTree=lifoPush(stackTree, toControl->dx);
            }
            fdelete(toControl->element);
            free(toControl);
            toControl=NULL;
        }
        deleteLifo(stackTree);
    }
    return NULL;
}

void preOrderARBIter(ARB* toPrint, FUNPRINT print){
    if(toPrint!=NULL){
        lifo* temp=NULL;
        lifo* stackTree=NULL;
        ARB* toVisit=NULL;
        stackTree=lifoPush(stackTree, toPrint);
        while(!lifoIsEmpty(stackTree)){
            temp=lifoTop(stackTree);
            toVisit=(ARB*)(temp->element);
            stackTree=lifoPop(stackTree);
            if(toVisit->dx!=NULL){
                stackTree=lifoPush(stackTree, toVisit->dx);
            }
            if(toVisit->sx!=NULL){
                stackTree=lifoPush(stackTree, toVisit->sx);
            }
            print(toVisit->element);
            printf("\n");
        }
    }
}

void inOrderARBIter(ARB* toPrint, FUNPRINT print){
    lifo* stackT=NULL;
    lifo* temp;
    ARB* curr;
    if(toPrint!=NULL){
        curr=toPrint;
        while(stackT!=NULL || curr!=NULL){
            if(curr!=NULL){
                stackT=lifoPush(stackT, curr);
                curr=curr->sx;
            }else{
                temp=lifoTop(stackT);
                curr=(ARB*)(temp->element);
                stackT=lifoPop(stackT);
                printf("\n");
                print(curr->element);
                curr=curr->dx;
            }
        }
    }
}

void postOrder(ARB* toPrint, FUNPRINT print){
    lifo* stackT=NULL;
    lifo* temp;
    ARB* curr=toPrint;
    ARB* last=NULL;
    if(toPrint!=NULL){
        while(stackT!=NULL || curr!=NULL){
            if(curr!=NULL){
                stackT=lifoPush(stackT, curr);
                curr=curr->sx;
            }else{
                temp=lifoTop(stackT);
                curr=(ARB*)(temp->element);
                if(curr->dx==NULL || last==curr->dx){
                    last=curr;
                    printf("\n");
                    print(curr->element);
                    stackT=lifoPop(stackT);
                    curr=NULL;
                }else{
                    curr=curr->dx;
                }
            }
        }
    }
}

ARB* searchAndDeleteIterative(ARB* ROOT, void* key, FUNCOM compare, FUNDEL fdel){
    ARB* dad=NULL;
    ARB* current=ROOT;
    ARB* find=NULL;
    void* temp;
    while(current!=NULL && compare(current->element, key)!=0){
        dad=current;
        if(compare(current->element, key)==1){
            current=current->sx;
        }else{
            current=current->dx;
        }
    }
    if(current==NULL){//non trovato
        return ROOT;
    }else{
        find=current;//trovato
    }
    if(find->sx==NULL && find->dx==NULL){//foglia
        if(find==ROOT){
            ROOT=NULL;
            fdel(find->element);
            free(find);
            return NULL;
        }else{
            if(find==dad->dx){
                dad->dx=NULL;
            }else {
                dad->sx=NULL;
            }
            fdel(find->element);
            free(find);
            return ROOT;
        }
    }
    //find ancora uguale a curr
    if(find->dx!=NULL){
        dad=current;
        current=current->dx;
        if(current->sx==NULL){
           temp=find->element;
           find->element=current->element;
           current->element=temp;
          // dad->dx=NULL;
            dad->dx=current->dx;

           fdel(current->element);
           free(current);
        }else{
            while(current->sx!=NULL){
                dad=current;
                current=current->sx;
            }
            dad->sx=current->dx;
            temp=find->element;
            find->element=current->element;
            current->element=temp;
            fdel(current->element);
            free(current);
        }
        return ROOT;
    }else{
        dad->sx=find->sx;
        fdel(find->element);
        free(find);
        return ROOT;
    }
}

ARB* deleteNodeIter(ARB* ROOT, FUNDEL fdel){
    ARB* current=ROOT;
    ARB* dad;
    void* temp;
    if(ROOT!=NULL){
        if(current->dx==NULL && current->sx==NULL){
            fdel(ROOT->element);
            free(ROOT);
            return NULL;
        }else if(current->dx!=NULL){
            current=current->dx;
            while(current->sx!=NULL){
                dad=current;
                current=current->sx;
            }
            if(current==ROOT->dx){
                current->sx=ROOT->sx;
                ROOT=current;
            }else{
                temp=ROOT->element;
                ROOT->element=current->element;
                current->element=ROOT->element;
                dad->sx=current->dx;
                fdel(current->element);
                free(current);
            }
        }else{
            current=ROOT;
            ROOT=ROOT->sx;
            fdel(current->element);
            free(current);
        }
    }
    return ROOT;
}


ARB* searchConditionAndDeleteIterative(ARB* ROOT, char* strMin, char* strMax, int odd, FUNCOM compare, FUNODD fodd, FUNDEL fdel){
    ARB* dad=NULL;
    ARB* current=ROOT;
    lifo* stack=NULL;
    lifo* popped;
    stack=lifoPush(stack, NULL);//dad
    stack=lifoPush(stack, ROOT);//current
    while(stack!=NULL){
        popped=lifoTop(stack);
        current=(ARB*)(popped->element);
        stack=lifoPop(stack);
        popped=lifoTop(stack);
        dad=(ARB*)(popped->element);
        stack=lifoPop(stack);
        if(current!=NULL){
            if(compare(current->element, strMin)>=0 && compare(current->element, strMax)<=0){
                if(fodd(current->element, odd)){
                    if(dad==NULL){
                        ROOT=deleteNodeIter(ROOT, fdel);
                        current=ROOT;
                        dad=NULL;/****cancello in testa, quindi ripristino***/
                    }else{
                        if(dad->sx==current){
                            current=deleteNodeIter(current, fdel);
                            dad->sx=current;
                        }else if(dad->dx==current){
                                current=deleteNodeIter(current, fdel);
                                dad->dx=current;
                        }
                    }
                    stack=lifoPush(stack, dad);
                    stack=lifoPush(stack, current);
                }else{
                    if(compare(current->element, strMin)>0){
                        stack=lifoPush(stack, current);
                        stack=lifoPush(stack, current->sx);
                    }
                    if(compare(current->element, strMax)<0){
                        stack=lifoPush(stack, current);
                        stack=lifoPush(stack, current->dx);
                    }
                }
            }else{
                if(compare(current->element, strMin)>0){
                        if(current->sx!=NULL){
                            stack=lifoPush(stack, current);
                            stack=lifoPush(stack, current->sx);
                        }
                }
                if(compare(current->element, strMax)<0){
                        if(current->dx!=NULL){
                            stack=lifoPush(stack, current);
                            stack=lifoPush(stack, current->dx);
                        }
                }
            }
        }
    }
    deleteLifo(stack);
    return ROOT;
}

ARB* duplicateARBIterative(ARB* copy, ARB* original, FUNCOM compare, FUNCPY fcopy){
    lifo* stackD=NULL;
    lifo* temp;
    ARB* current=original;
    if(current!=NULL){
        stackD=lifoPush(stackD, current);
        while(stackD!=NULL){
            temp=lifoTop(stackD);
            current=(ARB*)(temp->element);
            stackD=lifoPop(stackD);
            copy=insertARBNodeIterative(copy, current->element, compare, fcopy);
            if(current->dx!=NULL){
                stackD=lifoPush(stackD, current->dx);
            }
            if(current->sx!=NULL){
                stackD=lifoPush(stackD, current->sx);
            }
        }
    }
    return copy;
}

int controlSameARBIterative(ARB* one, ARB* two, FUNCOM compare){
    int ret=1;
//    int i=0;
    lifo* stackC=NULL;
    lifo* temp;
    ARB* tOne, *tTwo;
    if(one!=NULL && two!=NULL){
        stackC=lifoPush(stackC, one);
        stackC=lifoPush(stackC, two);
        while(stackC!=NULL && ret==1){
            temp=lifoTop(stackC);
            tTwo=(ARB*)(temp->element);
            stackC=lifoPop(stackC);

            temp=lifoTop(stackC);
            tOne=(ARB*)(temp->element);
            stackC=lifoPop(stackC);
            if(compare(tOne->element, tTwo->element)==0){
                if(tOne->dx!=NULL && tTwo->dx!=NULL){
                    stackC=lifoPush(stackC, tOne->dx);
                    stackC=lifoPush(stackC, tTwo->dx);
                }else if((tOne->dx!=NULL && tTwo->dx==NULL)|| (tOne->dx==NULL && tTwo->dx!=NULL)){
                    ret=0;
                }
                if(tOne->sx!=NULL && tTwo->sx!=NULL){
                    stackC=lifoPush(stackC, tOne->sx);
                    stackC=lifoPush(stackC, tTwo->sx);
                }else if((tOne->sx!=NULL && tTwo->sx==NULL)|| (tOne->sx==NULL && tTwo->sx!=NULL)){
                    ret=0;
                }
            }else ret=0;
        }
    }
    stackC=deleteLifo(stackC);
    return ret;
}


int countARBNodeIterative(ARB* ROOT){
    lifo* stack=NULL;
    lifo* temp;
    ARB* curr;
    int n=0;
    if(ROOT!=NULL){
        stack=lifoPush(stack, ROOT);
        while(stack!=NULL){
            temp=lifoTop(stack);
            curr=(ARB*)(temp->element);
            stack=lifoPop(stack);
            if(curr->dx!=NULL){
                stack=lifoPush(stack, curr->dx);
            }
            if(curr->sx!=NULL){
                stack=lifoPush(stack, curr->sx);
            }
            n++;
        }
    }
    return n;
}


void** vectorizeARBIterative(ARB* toVectorize, FUNCPY fcopy){
    int size=countARBNodeIterative(toVectorize);
    void** result;
    int n=0;
    lifo* stackT=NULL;
    lifo* temp;
    ARB* curr;
    result=(void**)malloc(sizeof(void*)*size);

    if(toVectorize!=NULL){
        curr=toVectorize;
        while(stackT!=NULL || curr!=NULL){
            if(curr!=NULL){
                stackT=lifoPush(stackT, curr);
                curr=curr->sx;
            }else{
                temp=lifoTop(stackT);
                curr=(ARB*)(temp->element);
                stackT=lifoPop(stackT);
                result[n]=fcopy(result[n], curr->element);
                n++;
                curr=curr->dx;
            }
        }
    }


    return result;
}


ARB* balanceARBIterative(ARB* toBalance, FUNCOM compare, FUNCPY fcopy){
    int n=countARBNodeIterative(toBalance);
    int i, j, k;
    lifo* stackB=NULL;
    ARB* balanced=NULL;
    i=0;
    j=n-1;
    int ti, tj;
    lifo* t;
    printf("\n%d\n\n\n", j);
    stackB=lifoPush(stackB,i);
    stackB=lifoPush(stackB,j);
    void**vect=vectorizeARBIterative(toBalance, fcopy);
    int o=0;
    for(o=0; o<n; o++){
        printString(vect[o]);
        printf("\n");
    }
    while(stackB!=NULL){
        t=lifoTop(stackB);
        j=(int*)(t->element);
        stackB=lifoPop(stackB);
        t=lifoTop(stackB);
        i=(int*)(t->element);
        stackB=lifoPop(stackB);
        printf("\ni:%d j:%d\n", i, j);
        if(i<=j){
            k=(i+j)/2;
            printString(vect[k]);
            printf("\n");
            balanced=insertARBNodeIterative(balanced, vect[k], compare, fcopy);
            k=k-1;
            stackB=lifoPush(stackB,i);
            stackB=lifoPush(stackB,k);
            k=k+2;
            stackB=lifoPush(stackB, k);
            stackB=lifoPush(stackB, j);
        }
    }
    preOrderARBIter(balanced, printString);
    return 0;
}
