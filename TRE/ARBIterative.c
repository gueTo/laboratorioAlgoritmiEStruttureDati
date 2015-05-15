#include <stdio.h>
#include <stdlib.h>
#include "ARBIterative.h"

/***/




FUNCT *initFUNCT(){
	FUNCT *ret=(FUNCT *)malloc(sizeof(FUNCT));
   	ret->fcomp=NULL;
   	ret->fcopy=NULL;
   	ret->fins=NULL;
   	ret->fodd=NULL;
    ret->frand=NULL;
    ret->funfree=NULL;
    ret->fpri=NULL;
    ret->ty=-1;
	return ret;
}

void FUNCTtype(FUNCT* ret, int type){
	if(type==1){
        ret->fcomp=&compareInteger;
        ret->fcopy=&copyInteger;
        ret->fins=&insertInteger;
        ret->fodd=&oddInteger;
        ret->frand=&casualInteger;
        ret->funfree=&deleteInteger;
        ret->fpri=&printInteger;
        ret->ty=1;
	}
	if(type==2){
        ret->fcomp=&compareFloat;
        ret->fcopy=&copyFloat;
        ret->fins=&insertFloat;
        ret->fodd=&oddFloat;
        ret->frand=&casualFloat;
        ret->funfree=&deleteFloat;
        ret->fpri=&printFloat;
        ret->ty=2;
	}
	if(type==3){
        ret->fcomp=&compareString;
        ret->fcopy=&copyString;
        ret->fins=&insertString;
        ret->fodd=&oddString;
        ret->frand=&casualString;
        ret->funfree=&deleteString;
        ret->fpri=&printString;
        ret->ty=3;
	}
}

FUNCT* deleteFUNCT(FUNCT* toDel){
    free(toDel);
    return NULL;
}

/***/
/**CREAZIONE 1NUOVO NODO**/
ARB* newARBNode(void* toInsert, FUNCT* funList){
    ARB* newNode=NULL;
    newNode=(ARB*)malloc(sizeof(ARB));//ALLOCAZIONENUOVO NODO
    newNode->element=funList->fcopy(newNode->element, toInsert);//ALLOCAZIONE MEMORIA PER LA STRINGA DA INSERIRE
    newNode->sx=NULL;
    newNode->dx=NULL;
    return newNode;
}

/***DEALLOCAZIONE NODO***/
ARB* freeARBNode(ARB* node, FUNCT* funList){
    funList->funfree(node->element);
    free(node);
    return NULL;
}


/*****************FUNZIONI RICHIESTE********************/
/**come richiesto, tutte le istruzioni di ricorsione sono state
"virtualizzate", dove necessario tramite la struttura dati chiamata STACK**/

ARB* insertARBNodeIterative(ARB* ROOT, void* toIns, FUNCT* funList){
    ARB* temp;
    ARB* dad=NULL;
    //serve per fermare il ciclo
    int stop;
    //serve per tenere memoria del risultato della comparazione
    int cmp;
    //controllo se l'albero ha già dei nodi
    if(ROOT!=NULL){
        temp=ROOT;
        //viene creato lo stack
        stop=0;
        cmp=0;
        //si scorre l'albero tramite stack
        while(stop!=1 && temp!=NULL){
            //compara l'elemento corrente con quello da inserire
            //per poter navigare nell'albero
            cmp=funList->fcomp(temp->element, toIns);
            //conservo il nodo corrente come padre
            dad=temp;
            //e vado a considerare il prossimo
            if(cmp<0){
                temp=temp->dx;
            }else if(cmp>0){
                temp=temp->sx;
            }else stop=1;//se l'elemento è lo stesso il ciclo termina
        }
        //se invece si arriva ad una foglia, si recupera il padre
        if(temp==NULL){
            //e a seconda del valore di cmp inserisco a destra o a sinistra
            if(cmp<0)
                dad->dx=newARBNode(toIns, funList);
            else
                dad->sx=newARBNode(toIns, funList);
        }
    }else{
        ROOT=newARBNode(toIns, funList);
    }
    return ROOT;
}

/**questa cancellazione fa uso dello stack per tenere traccia
dei figli del nodo che si andaranno a cancellare**/
ARB* deleteARBIterative(ARB* ROOT, FUNCT* funList){
    //vengono usate due variabili puntatori a lifo
    //una per lo stack vero e proprio
    //l'altra, topStack, per una più comoda lettura del codice
    //visto che serve solo per vedere il corrente top dello stack
    lifo* stackTree=NULL;
    lifo* topStack=NULL;
    // toControl serve anch'esso per una migliore lettura del codice
    //e tiene traccia solo del nodo dell'albero che stiamo considerando un quel momento
    ARB* toControl=NULL;
    if(ROOT!=NULL){
        //se l'albero non è vuoto allora metto nello stack la radice
        stackTree=lifoPush(stackTree, ROOT);
        //si cicla finché lo stack non è vuoto
        //ovvero dopo che ho visitato tutto l'albero
        while(!lifoIsEmpty(stackTree)){
            //prendo l'elemento in cima
            topStack=lifoTop(stackTree);
            //ne estraggo l'elemento, in questo caso il nodo dell'albero
            toControl=(ARB*)(topStack->element);
            //ed estraggo il primo elemento dello stack
            stackTree=lifoPop(stackTree);
            //dato che deve essere cancellato tutto l'albero
            //vengono inseriti nello stack entrambi i figli
            //del nodo corrente, se presenti
            if(toControl->sx!=NULL){
                stackTree=lifoPush(stackTree, toControl->sx);
            }
            if(toControl->dx!=NULL){
                stackTree=lifoPush(stackTree, toControl->dx);
            }
            //dopodiché si dealloca l'elemento presente nel nodo
            funList->funfree(toControl->element);
            //e poi il nodo stesso
            free(toControl);
            toControl=NULL;
        }
        //non ce n'è bisogno, ma viene deallocato tutto lo stack
        deleteLifo(stackTree);
    }
    return NULL;
}


//pure qua viene utilizzato lo stack per la visita in pre order dell'albero
void preOrderARBIter(ARB* toPrint, FUNCT* funList){
    //è identico all'algoritmo precedente(cancellazione completa dell'albero)
    //ma invece di cancellare il nodo dopo aver messo nello stack i figli
    //esso viene visitato, in questo caso letto e stampao a video
    lifo* temp=NULL;
    lifo* stackTree=NULL;
    ARB* toVisit=NULL;
    if(toPrint!=NULL){
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
            funList->fpri(toVisit->element);
            printf("\n");
        }
    }
}

void inOrderARBIter(ARB* toPrint, FUNCT* funList){
    lifo* stackTree=NULL;
    lifo* temp=NULL;
    ARB* current=NULL;
    if(toPrint!=NULL){
        current=toPrint;
        //per la visita in order verrà scorso tutto l'albero nel ramo sinistro
        //dopodichè, risalendo nello stesso si visiterà il nodo corrente e si
        //inserirà nello stack il figlio destro del nodo
        //a quel punto di quel sottoalbero verranno presi in considerazione
        //prima i figli sinistri, poi le radici di eventuali sottoalberi
        //e poi quelli destri
        while(!lifoIsEmpty(stackTree)|| current!=NULL){
            if(current!=NULL){
                //praticamente va a sinistra fintanto c'è un figlio
                stackTree=lifoPush(stackTree, current);
                current=current->sx;
            }else{
                //se non c'è prende l'elemento in cima allo stack
                temp=lifoTop(stackTree);
                current=(ARB*)(temp->element);
                stackTree=lifoPop(stackTree);
                //lo visita
                funList->fpri(current->element);
                printf("\n");
                //e comincia ad andare a destra
                current=current->dx;
                //a quel punto se a destra è null, continua a risalire
                //nell'albero principale, se invece è radice di un altro
                //sottoalbero, viene messo nello stack e comincia a scorrere verso sinistra
            }
        }
    }
}

void postOrder(ARB* toPrint, FUNCT* funList){
    lifo* stackTree=NULL;
    lifo* temp=NULL;
    ARB* current=NULL;
    ARB* last=NULL;
    if(toPrint!=NULL){
        current=toPrint;
        while(stackTree!=NULL || current!=NULL){
            if(current!=NULL){
                stackTree=lifoPush(stackTree, current);
                current=current->sx;
                //come per la visita inOrder, anche qui si scorre
                //prima tutto il ramo sinistro del nodo corrente
            }else{
                //se non esistono più figli sinsitri si estrae la
                //testa dello stack
                temp=lifoTop(stackTree);
                current=(ARB*)(temp->element);
                //a questo punto se ci troviamo in una foglia
                //o abbiamo già visitato il sottoalbero destro
                //visitiamo il nodo corrente
                if(current->dx==NULL || last==current->dx){
                    funList->fpri(current->element);
                    printf("\n");
                    //con last ricordiamo di essere già passati
                    //in questo sottoalbero destro
                    last=current;
                    stackTree=lifoPop(stackTree);
                    current=NULL;
                }else{
                    //nel caso non sia ne' una foglia, ne' un nodo già visitato
                    //scorriamo a destra
                    current=current->dx;
                }
            }
        }
    }
}

//cancellazione di un elemento richiesto
ARB* searchAndDeleteIterative(ARB* ROOT, void* key, FUNCT* funList){
    ARB* dad=NULL;
    ARB* current=ROOT;
    ARB* find=NULL;
    void* temp;
    //fintanto che l'albero non è finito o è stato trovato l'elemento
    //si continua a navigare un ramo dell'albero
    while(current!=NULL && funList->fcomp(current->element, key)!=0){
        dad=current;
        if(funList->fcomp(current->element, key)==1){
            current=current->sx;
        }else{
            current=current->dx;
        }
    }
    //finito il ciclo

    //se l'elemento non è stato trovato, si ritorna
    if(current==NULL){//non trovato
        return ROOT;
    }else{
        //altrimenti si setta la variabile find col nodo trovato
        find=current;//trovato
    }
    //adesso, si controlla se il nodo trovato è una foglia
    if(find->sx==NULL && find->dx==NULL){//foglia
        //potrebbe essere la radice di un albero con un solo nodo
        if(find==ROOT){
            //lo si cancella e si ritorna NULL
            ROOT=NULL;
            funList->funfree(find->element);
            free(find);
            return NULL;
        }else{
            //altrimenti controlliamo se è figlio destro o sinistro del padre
            if(find==dad->dx){
                dad->dx=NULL;
            }else {
                dad->sx=NULL;
            }
            //a quel punto cancelliamo il collegamento tra il padre e il figlio
            //e deallochiamo quest'ultimo
            funList->funfree(find->element);
            free(find);
            return ROOT;
        }
    }
    //ma se non è una foglia?
    //allora cercom il minimo nel sottoalbero destro
    if(find->dx!=NULL){
        /**perché ho deciso di salvarmi il padre?**/
        dad=current;
        current=current->dx;
        //se il sottoalbero preso in considerazione
        //non ha un ramo sinistro, si sostituisce
        //questo nodo, col suo figlio destro
        if(current->sx==NULL){
            temp=find->element;
            find->element=current->element;
            current->element=temp;
            dad->dx=current->dx;
            funList->funfree(current->element);
            free(current);
        }else{
            //se invece un sottoalbero sinistro
            //scorro il ramo sinistro
            while(current->sx!=NULL){
                dad=current;
                current=current->sx;
            }
            dad->sx=current->dx;
            temp=find->element;
            find->element=current->element;
            current->element=temp;
            funList->funfree(current->element);
            free(current);
        }
        //in entrambi i casi alla fine sostituisco il nodo trovato
        //con il minimo, e sostituisco il primo
        return ROOT;
    }else{
        dad->sx=find->sx;
        funList->funfree(find->element);
        free(find);
        return ROOT;
    }
}

/**Cancellazione come sopra**/
ARB* deleteNodeIter(ARB* ROOT, FUNCT* funList){
    ARB* current=ROOT;
    ARB* dad=NULL;
    void* temp;
    temp=NULL;
    if(ROOT!=NULL){
        if(current->dx==NULL && current->sx==NULL){
            funList->funfree(ROOT->element);
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
                funList->funfree(current->element);
                free(current);
            }
        }else{
            current=ROOT;
            ROOT=ROOT->sx;
            funList->funfree(current->element);
            free(current);
        }
    }
    return ROOT;
}


ARB* searchConditionAndDeleteIterative(ARB* ROOT, char* strMin, char* strMax, int odd, FUNCT* funList){
    ARB* dad=NULL;
    ARB* current=ROOT;
    lifo* stack=NULL;
    lifo* popped;
    stack=lifoPush(stack, NULL);//dad
    stack=lifoPush(stack, ROOT);//current
    /**dato che serve sapere il padre di ogni nodo
    che considero in quel momento, faccio ogni volta
    un doppio push con un doppio pop quando mi serve**/
    while(stack!=NULL){
        /**doppio pop: nodo considerato e suo padre**/
        popped=lifoTop(stack);
        current=(ARB*)(popped->element);
        stack=lifoPop(stack);
        popped=lifoTop(stack);
        dad=(ARB*)(popped->element);
        stack=lifoPop(stack);
        if(current!=NULL){
            /**controllo se si trova tra i due estremi**/
            if(funList->fcomp(current->element, strMin)>=0 && funList->fcomp(current->element, strMax)<=0){
                /**se lo è controllo se è pari**/
                if(funList->fodd(current->element, odd)){
                    /**poi cancello**/
                    /**faccio i controlli e chiamo la funzione preparata prima**/
                    if(dad==NULL){
                        ROOT=deleteNodeIter(ROOT, funList);
                        current=ROOT;
                        dad=NULL;/****cancello in testa, quindi ripristino***/
                    }else{
                        if(dad->sx==current){
                            current=deleteNodeIter(current, funList);
                            dad->sx=current;
                        }else if(dad->dx==current){
                                current=deleteNodeIter(current, funList);
                                dad->dx=current;
                        }
                    }
                    /**doppio push di nodo padre e corrente**/
                    stack=lifoPush(stack, dad);
                    stack=lifoPush(stack, current);
                }else{
                    /**altrimenti coi controlli scendo a destra o a sinistra**/
                    if(funList->fcomp(current->element, strMin)>0){
                        stack=lifoPush(stack, current);
                        stack=lifoPush(stack, current->sx);
                    }
                    if(funList->fcomp(current->element, strMax)<0){
                        stack=lifoPush(stack, current);
                        stack=lifoPush(stack, current->dx);
                    }
                }
            }else{
                /**qua invece entro se il nodo corrente
                non è compreso fre i due estremi**/
                /**e faccio i controlli su dove scendere**/
                if(funList->fcomp(current->element, strMin)>0){
                        if(current->sx!=NULL){
                            stack=lifoPush(stack, current);
                            stack=lifoPush(stack, current->sx);
                        }
                }
                if(funList->fcomp(current->element, strMax)<0){
                        if(current->dx!=NULL){
                            stack=lifoPush(stack, current);
                            stack=lifoPush(stack, current->dx);
                        }
                }
            }
        }
    }
    //alla fine pulisco lo stack
    deleteLifo(stack);
    return ROOT;
}

/**funziona come la visita preorder, ma copio il nodo corrente
in un nuovo nodo che inserisco nel nuovo albero**/
ARB* duplicateARBIterative(ARB* copy, ARB* original, FUNCT* funList){
    lifo* stackD=NULL;
    lifo* temp;
    ARB* current=original;
    if(current!=NULL){
        stackD=lifoPush(stackD, current);
        while(stackD!=NULL){
            temp=lifoTop(stackD);
            current=(ARB*)(temp->element);
            stackD=lifoPop(stackD);
            copy=insertARBNodeIterative(copy, current->element, funList);
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

/**controllo scendendo nell'albero se i nodi sono uguali pushando
contemporaneamente i candidati uguali, se sono diversi o come forma o come dato, esco dal ciclo*/
int controlSameARBIterative(ARB* one, ARB* two, FUNCT* funList){
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
            if(funList->fcomp(tOne->element, tTwo->element)==0){
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
    /**se esce senza problemi dal ciclo allo ret=1 altrimenti se incontra problemi ret=0**/

    /**dealloco lo stack eventualmente non vuoto**/
    stackC=deleteLifo(stackC);
    //ritorno ret
    return ret;
}


int countARBNodeIterative(ARB* ROOT){
    lifo* stack=NULL;
    lifo* temp;
    ARB* curr;
    int n=0;
    if(ROOT!=NULL){
        //visito in pre order e ogni pop aumento il contatore di 1
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

/**visita in order con copia nel vettore dell'albero**/

void** vectorizeARBIterative(ARB* toVectorize, FUNCT* funList){
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
                result[n]=funList->fcopy(result[n], curr->element);
                n++;
                curr=curr->dx;
            }
        }
    }
    return result;
}

/**sarebbe meglio creare una struttura per gli estremi**/
ARB* balanceARBIterative(ARB* toBalance, FUNCT* funList){
    /**costruisce prima l'array contenente i nodi dell'albero da bilanciare**/
    int n=countARBNodeIterative(toBalance);
    int i, j, k;
    lifo* stackB=NULL;
    ARB* balanced=NULL;
    boundArray* bpop;
    boundArray* bpush;
    //uso gli indici i e j come estremi delle posizioni dell'array da considerare
    i=0;
    j=n-1;
    lifo* t;
    //e sonogli indici che vengono inseriti di volta in volta nello stack
    bpush=(boundArray*)malloc(sizeof(boundArray));
    bpush->i=i;
    bpush->j=j;
    stackB=lifoPush(stackB, bpush);
    void**vect=vectorizeARBIterative(toBalance, funList);
    while(stackB!=NULL){
        //in ogni iterazione del ciclo vengono estratti due indici inseriti
        t=lifoTop(stackB);
        bpop=(boundArray*)(t->element);
        i=bpop->i;
        j=bpop->j;
        free(bpop);
        stackB=lifoPop(stackB);
        if(i<=j){
            k=(i+j)/2;
            //grazie a loro viene calcolato il valore della posizione
            //alla quale accedere per prendere il nodo da inserire
            //nell'albero bilanciato
            balanced=insertARBNodeIterative(balanced, vect[k], funList);
            k=k-1;
            bpush=(boundArray*)malloc(sizeof(boundArray));
            bpush->i=i;
            bpush->j=k;
            stackB=lifoPush(stackB, bpush);
            k=k+2;
            bpush=(boundArray*)malloc(sizeof(boundArray));
            bpush->i=k;
            bpush->j=j;
            stackB=lifoPush(stackB, bpush);
            //vengono ricalcolati gli indici e inseriti come estremi nello stack
        }
    }
    return 0;
}
