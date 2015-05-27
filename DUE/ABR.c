#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _DATA_H_
    #define _DATA_H_

    #include "data.h"

#endif // _DATA_H_

#ifndef _ARB_H_
    #define _ARB_H_

    #include "ABR.h"

#endif // _ARB_H_


/*****FUNZIONI*****/
#ifndef _GEST_FUNCTDATA_
#define _GEST_FUNCTDATA_
FUNCTDATA *initFUNCTDATA(){
	FUNCTDATA *ret=(FUNCTDATA *)malloc(sizeof(FUNCTDATA));
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


void FUNCTDATAtype(FUNCTDATA* ret, int type){
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

FUNCTDATA* deleteFUNCTDATA(FUNCTDATA* toDel){
    free(toDel);
    return NULL;
}

#endif // _GEST_FUNCTDATA_

#ifndef _GEST_ARBNODE_
#define _GEST_ARBNODE_
/**CREAZIONE 1NUOVO NODO**/

ARB* newARBNode(void* toInsert, FUNCTDATA* funList){
    ARB* newNode=NULL;
    newNode=(ARB*)malloc(sizeof(ARB));//ALLOCAZIONENUOVO NODO
    newNode->element=funList->fcopy(newNode->element, toInsert);//ALLOCAZIONE MEMORIA PER LA STRINGA DA INSERIRE
    newNode->sx=NULL;
    newNode->dx=NULL;
    return newNode;
}

/***DEALLOCAZIONE NODO***/
ARB* freeARBNode(ARB* node, FUNCTDATA* funList){
    funList->funfree(node->element);
    free(node);
    return NULL;
}
#endif // _GEST_ARBNODE_

/***CANCELLAZIONE NODO***/

ARB* detachMin(ARB* son, ARB* dad){
    //SI CERCA IL NODO CONVALORE MINIMO NEL SOTTOALBEROCOI VALORI
    //MAGGIORI
    if(son!=NULL){
        if(son->sx!=NULL){
            return detachMin(son->sx, son);
        }else{
            if(son==dad->sx){
                dad->sx=son->dx;
            }else{
                dad->dx=son->dx;
            }
        }
    }
    return son;
}

ARB* adjustARB(ARB* ROOT, FUNCTDATA* funList){
    //SI CERCA IL NODO ADATTO DA SCMBIARE CON QUELLO CHE DEVE
    //ESSERE CANCELLATO, IN SEGUITO SI SOSTITUISCONO I DATI
    //TRA I DUE NODI E SI DEALLOCA IL CANDIDATO ALLA SOSTITUZIONE
    //IN QUESTO MODO SI CANCELLA QUELLO CHE SI E' CERCATO SENZA
    //MODIFICARE L'ALBERO
    ARB* temp=ROOT;
    void* etemp;
    if(ROOT->dx==NULL){
        ROOT=temp->sx;
    }else if(ROOT->sx==NULL){
            ROOT=temp->dx;
    }else{
        //SE IL NODO HA ENTRAMBI I FIGLI ALLORA CERCO IL MINORE
        //TRA I VALORE MAGGIORI E SCAMBIO GLI ELEMENTI
        //POI CANCELLO IL NODO CHE CONTENEVA L'ELEMENTO SOSTITUITO
        //QUINDI CANCELLO UNA FOGLIA
        temp=detachMin(ROOT->dx, ROOT);
        etemp=ROOT->element;
        ROOT->element=temp->element;
        temp->element=etemp;
    }
    freeARBNode(temp, funList);
    return ROOT;
}


int countARBNode(ARB* ROOT){
	if(ROOT!=NULL){
		return 1+countARBNode(ROOT->sx)+countARBNode(ROOT->dx);
	}else return 0;
}

/***FUNZIONALITA' RICHIESTE***/
/***
1. inserimento di una stringa data in un ARB dato;
***/
//NAVIGAZIONE RICORSIVA A DESTRA O A SINISTRA SECONDO UN ORDINE ALFANUMERICO ABITUALE
ARB* insertARBNode(ARB* ROOT, void* toInsert, FUNCTDATA* funList){
    if(ROOT!=NULL){
            //NAVIGAZIONE NELL'ALBERO
        if(funList->fcomp(ROOT->element, toInsert)>0){
            ROOT->sx=insertARBNode(ROOT->sx, toInsert, funList);
        }else if(funList->fcomp(ROOT->element, toInsert)<0){
                ROOT->dx=insertARBNode(ROOT->dx, toInsert, funList);
        }
    //QUESTA NAVIGAZIONE IMPEDISCE L'INSERIMENTO DI UNA STRINGA UGUALE AD UNA GIA' PRESENTE
    }else{
        //SPAZIO TROVATO ED INSERIMENTO
        ROOT=newARBNode(toInsert, funList);
        //free(toInsert);
        }
    return ROOT;
}


/***
2. stampa di tutte le stringhe presenti in un ARB dato;
***/
//STAMPA CON NAVIGAZIONE IN IN-ORDER

void printARB(ARB* ROOT, FUNCTDATA* funList){
    if(ROOT!=NULL){
        printf("\n");
        funList->fpri(ROOT->element);
        printARB(ROOT->sx, funList);
        printARB(ROOT->dx, funList);
    }
}


/***
3. cancellazione di tutti gli elementi di in un ARB dato;
***/

//LA CANCELLAZIONE SEGUE LA NAVIGAZIONE IN POST-ORDER
//OVVERO CANCELLA PRIMA TUTTI I FIGLI E POI IL NODO DI RIFERIMENTO
//DOVENDO CANCELLARE TUTTO ELIMINA PRIMA LE FOGLIE E RICORSIVAMENTE
//I NODI PADRE FINO A GIUNGERE ALLA RADICE
ARB* deleteAllKey(ARB* ROOT, FUNCTDATA* funList){
    if(ROOT!=NULL){
        ROOT->sx=deleteAllKey(ROOT->sx, funList);
        ROOT->dx=deleteAllKey(ROOT->dx, funList);
        ROOT=freeARBNode(ROOT, funList);
    }
    return ROOT;
}


/***
4. cancellazione da un ARB dato di una stringa data in ingresso;
***/
//PREVEDE UNA NAVIGAZIONE NELL'ALBERO PER LA RICERCA DELLA STRINGA
//NEL CASO LA STRINGA VENGA TROVATA VERRA' CANCELLATA

ARB* searchStringAndDelete(ARB* ROOT, void* toDelete, FUNCTDATA* funList){
    int r;
    if(ROOT!=NULL){
        r=funList->fcomp(ROOT->element, toDelete);
        switch(r){
            case -1:
                ROOT->dx=searchStringAndDelete(ROOT->dx, toDelete, funList);
                break;
            case 0:
                ROOT=adjustARB(ROOT, funList);
                break;
            case 1:
                ROOT->sx=searchStringAndDelete(ROOT->sx, toDelete, funList);
                break;
        }
    }
    return ROOT;
}

/***
5. cancellazione da un ABR dato di tutti gli elementi che contengono una stringa che soddisfa
la seguente proprietà:
    ha lunghezza pari o dispari, in dipendenza di un parametro dato in ingresso, e ha un
    valore compreso tra due stringhe a e b, anch’esse date in ingresso;
***/

//CONTROLLA SE LA STRINGA PRESA IN CONSIDERAZIONE SI TROVA TRA LA DUE DATE DALL'UTENTE
//MA PRIMA DI CANCELLARLA CONTROLLA SE ESISTONO NEI SOTTOALBERI DEL NODO PRESO IN CONSIDERAZIONE
//ALTRE STRINGHE DA DOVER CANCELLARE.
//QUANDO ARRIVA ALLA FINE COMINCIA LA CANCELLAZIONE
//INOLTRE PER EVITARE DI SCORRERE INUTILMENTE TUTTO L'ALBERO CONTROLLA SE E' IL CASO DI SCENDERE
//NEI SOTTOALBERI CONTROLLANDO SE LE STRINGHE DELLE RADICI DEI SOTTOALBERI SI TROVANO ALL'INTERNO DEL RANGE

ARB* searchConditionAndDeleteARB(ARB* ROOT, char* strMin, char* strMax, int odd, FUNCTDATA* funList){
    if(funList->fcomp(strMin, strMax)>0){
        return ROOT;
    }
    if(ROOT!=NULL){
        if(funList->fcomp(ROOT->element, strMin)>=0 && funList->fcomp(ROOT->element, strMax)<=0){
            if(funList->fcomp(ROOT->element, strMin)>0){
                ROOT->sx=searchConditionAndDeleteARB(ROOT->sx, strMin, strMax, odd, funList);
            }
            if(funList->fcomp(ROOT->element, strMax)<0){
                ROOT->dx=searchConditionAndDeleteARB(ROOT->dx, strMin, strMax, odd, funList);
            }
            if(funList->fodd(ROOT->element, odd)){
                ROOT=adjustARB(ROOT, funList);
            }
        }else{
            if(funList->fcomp(ROOT->element, strMin)>0){
                ROOT->sx=searchConditionAndDeleteARB(ROOT->sx, strMin, strMax, odd, funList);
            }
            if(funList->fcomp(ROOT->element, strMax)<0){
                ROOT->dx=searchConditionAndDeleteARB(ROOT->dx, strMin, strMax, odd, funList);
            }
        }
    }
    return ROOT;
}


/***
6. costruzione di un ABR contenente un numero n di stringhe casualmente generate, dove n
`e un parametro dato in ingresso;
***/
//GENERA CASUALMENTE UNA STRINGA E POI LA INSERISCE NEL SOTTOALBERO
//POI DECREMENTA IL CONTATORE DEI NODI
ARB* casualARB(ARB* ROOT, int numNodes, FUNCTDATA* funList){
    srand(time(NULL));
    void* toIns;
    while(numNodes>0){
        toIns=funList->frand();
        ROOT=insertARBNode(ROOT, toIns, funList);
        numNodes--;
    }
    return ROOT;
}

/***
7. duplicazione di un ABR dato;
***/
//SCORRE IN ORDER L'ALBERO ORIGINALE E INSERISCE NEL NUOVO ALBERO LE CHIAVI
//MAN MANO CHE INCONTRA QUELLE DELL'ALBERO ORIGINALE
//COSI' FACENDO INSERISCE NEL DUPLICATO LE CHIAVI NELLO STESSO ORDINE IN CUI SONO
//STATE INSERITE QUELLE DELL'ALBERO INIZIALE
ARB* duplicateARB(ARB* original, FUNCTDATA* funList){
    ARB* copy=NULL;
    if(original!=NULL){
        copy=(ARB*)malloc(sizeof(ARB));
        copy->element=funList->fcopy(copy->element, original->element);
        copy->sx=duplicateARB(original->sx, funList);
        copy->dx=duplicateARB(original->dx, funList);
    }
    return copy;
}

/***
8. verifica se due ABR dati sono identici (hanno le stesse chiavi e la stessa forma);
***/
//FA UNA LETTURA IN ORDER DEI DUE ALBERI
//SE LE CHIAVI DEL NODO PRESO IN CONSIDERAZIONE COINCIDONO, ALLORA SI PASSA AD ESAMINARE I SOTTOALBERI
//SE IL SOTTOALBERO SINISTRO(DESTRO) DEL PRIMO ALBERO ESISTE E IL SOTTOALBERO SINISTRO(DESTRO)DEL SECONDO
//NON ESISTE, ALLORA RESTITUISCE 0, ALTRIMENTI PRENDE IN CONSIDERAZIONE LE CHIAVI.
//E COSI0 VIA FINCHE' NON INCONTRA SOTTOALBERI DI FORMA DIVERSA O CHIAVI NON IDENTICHE.
//SE NON INCONTRA NESSUNA DELLA DUE, ALLORA L'ALGORITMO FINISCE E RESTITUISCE 1
int controlSameARB(ARB* one, ARB* two, FUNCTDATA* funList){
    if(one!=NULL && two!=NULL){
        if(funList->fcomp(one->element, two->element)==0){
            if(controlSameARB(one->sx, two->sx, funList)==1 && controlSameARB(one->dx, two->dx, funList)==1){
                return 1;
            }else return 0;
        }else return 0;
    }else{
        if(one==NULL && two==NULL){
            return 1;
        }else{
            return 0;
        }
    }
}

/***
9. riempimento di un array ordinato contenente tutti le stringhe di un ARB dato;
***/


//PASSANDO LA GRANDEZZA DELL'ARRAY, L'ALGORITMO RIEMPIE A PARTIRE DALL'ULTIMO POSTO E DECREMENTA IL CONTATORE
void** vectorizeFunction(ARB* ROOT, void** vec, int* k, FUNCTDATA* funList){
    if(ROOT!=NULL){
            //RICORRE FINO A RAGGIUNGERE UN NODO NULLO
		vec=vectorizeFunction(ROOT->dx, vec, k, funList);
    //SCENDE A DESTRA
		//vec[(*k)]=(char*)malloc(sizeof(char)*strlen(ROOT->stringElement));
		funList->fcopy(vec[(*k)],ROOT->element);
		(*k)=(*k)-1;
		//ALLOCA LO SPAZIO PER LA NUOVA STRINGA E COPIA QUELLA PRESENTE NELL'ALBERO
		//DECREMENTA IL CONTATORE PER LA POSIZIONE DEI NODI
		vec=vectorizeFunction(ROOT->sx, vec, k, funList);
		//SCENDE A SINISTRA
	}
	return vec;
}
//SI ALLOCA PRIMA UN ARRAY DELLA STESSA DIMENSIONE DELL'ALBERO, POI SI PARTE CON IL SUO RIEMPIMENTO ORDINATO
void** vectorizeARB(ARB* toVectorize, FUNCTDATA* funList){
    int size=countARBNode(toVectorize);
    void** result;
    result=(void**)malloc(sizeof(void*)*size);
    size--;
    result=vectorizeFunction(toVectorize, result, &size, funList);
    return result;
}

/***
10. costruzione di un ABR perfettamente bilanciato a partire da un ARB dato (NOTA: in
un ABR perfettamente bilanciato il numero di nodi dei due sottoalberi di ogni nodo differiscono
al massimo di 1. Si sfrutti opportunamente il punto 9 per realizzare la funzionalità).
***/

//PER BILANCIARE E' SUFFICIENTE RIEMPIRE LA RADICE DELL'ALBERO CON L'ELEMENTO MEDIANO DEL VETTORE ORDINATO
//POI SI PASSANO GLI ESTREMI DEI SOTTOARRAY DELIMITATI DALL'ELEMENTO MEDIANO
//SI PROCEDE IN QUESTO MODO FINCHE' NON SI INCROCIANO GLI ESTREMI PASSATI
//A QUEL PUNTO L'ALGORITMO TERMINA
ARB* balanceFunction(void** source, int i, int j, ARB* res, FUNCTDATA* funList){
    int k;
    if(i<=j){
        k=(i+j)/2;
        res=insertARBNode(res, source[k], funList);
        res=balanceFunction(source, i, k-1, res, funList);
        res=balanceFunction(source, k+1, j, res, funList);
    }
    return res;
}


//USIAMO IL VETTORE CREATO AL PUNTO 9.
ARB* balanceARB(ARB* toBalance, FUNCTDATA* funList){
    void** temp;
    ARB* result=NULL;
    int i;
    int size=countARBNode(toBalance);
    temp=vectorizeARB(toBalance, funList);
    result=balanceFunction(temp, 0, size-1, result, funList);
    for(i=0; i<size; i++){
        free(temp[i]);
    }
    free(temp);
    return result;
}
