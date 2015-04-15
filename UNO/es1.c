#include "es1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*****FUNZIONI*****/

/**CREAZIONE NUOVO NODO**/
ARB* newARBNode(char* stringToInsert){
    ARB* newNode=NULL;
    newNode=(ARB*)malloc(sizeof(ARB));//ALLOCAZIONENUOVO NODO
    newNode->stringElement=(char*)malloc(sizeof(char)*strlen(stringToInsert));//ALLOCAZIONE MEMORIA PER LA STRINGA DA INSERIRE
    strcpy(newNode->stringElement, stringToInsert);//COPIA DELLA STRINGA
    newNode->sx=NULL;
    newNode->dx=NULL;
    return newNode;
}

/***DEALLOCAZIONE NODO***/
ARB* freeARBNode(ARB* node){
    free(node->stringElement);
    free(node);
    return NULL;
}

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

ARB* adjustARB(ARB* ROOT){
    //SI CERCA IL NODO ADATTO DA SCMBIARE CON QUELLO CHE DEVE
    //ESSERE CANCELLATO, IN SEGUITO SI SOSTITUISCONO I DATI
    //TRA I DUE NODI E SI DEALLOCA IL CANDIDATO ALLA SOSTITUZIONE
    //IN QUESTO MODO SI CANCELLA QUELLO CHE SI E' CERCATO SENZA
    //MODIFICARE L'ALBERO
    ARB* temp=ROOT;
    char* stemp;
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
        stemp=ROOT->stringElement;
        ROOT->stringElement=temp->stringElement;
        temp->stringElement=stemp;
    }
    freeARBNode(temp);
    return ROOT;
}

/***GENERAUNA STRINGA CASUALE***/

char* casualString(){
    int lenght;
    int cicle=0;
    int ins;
    char* strRes=NULL;
    lenght=(rand()%LENGHT_WORD)+2;
    strRes=(char*)malloc(sizeof(char)*lenght);
    while(cicle<(lenght-1)){// && cicle<MAXSTRING){
        ins='a'+(rand()%25);
        strRes[cicle]=ins;
        printf("%c ", ins);
        cicle++;
    }
    strRes[cicle]='\0';
    printf("%s\n\n", strRes);
    return strRes;
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
ARB* insertARBNode(ARB* ROOT, char* stringToInsert){
    if(ROOT!=NULL){
            //NAVIGAZIONE NELL'ALBERO
        if(strcmp(ROOT->stringElement, stringToInsert)>0){
            ROOT->sx=insertARBNode(ROOT->sx, stringToInsert);
        }else if(strcmp(ROOT->stringElement, stringToInsert)<0){
                ROOT->dx=insertARBNode(ROOT->dx, stringToInsert);
        }
    //QUESTA NAVIGAZIONE IMPEDISCE L'INSERIMENTO DI UNA STRINGA UGUALE AD UNA GIA' PRESENTE
    }else{
        //SPAZIO TROVATO ED INSERIMENTO
        ROOT=newARBNode(stringToInsert);
    }
    return ROOT;
}


/***
2. stampa di tutte le stringhe presenti in un ARB dato;
***/
//STAMPA CON NAVIGAZIONE IN IN-ORDER

void printARB(ARB* ROOT){
    if(ROOT!=NULL){
        printf("%s\n", ROOT->stringElement);
        printARB(ROOT->sx);
        printARB(ROOT->dx);
    }
}


/***
3. cancellazione di tutti gli elementi di in un ARB dato;
***/

//LA CANCELLAZIONE SEGUE LA NAVIGAZIONE IN POST-ORDER
//OVVERO CANCELLA PRIMA TUTTI I FIGLI E POI IL NODO DI RIFERIMENTO
//DOVENDO CANCELLARE TUTTO ELIMINA PRIMA LE FOGLIE E RICORSIVAMENTE
//I NODI PADRE FINO A GIUNGERE ALLA RADICE
ARB* deleteAllKey(ARB* ROOT){
    if(ROOT!=NULL){
        ROOT->sx=deleteAllKey(ROOT->sx);
        ROOT->dx=deleteAllKey(ROOT->dx);
        ROOT=freeARBNode(ROOT);
    }
    return ROOT;
}


/***
4. cancellazione da un ARB dato di una stringa data in ingresso;
***/
//PREVEDE UNA NAVIGAZIONE NELL'ALBERO PER LA RICERCA DELLA STRINGA
//NEL CASO LA STRINGA VENGA TROVATA VERRA' CANCELLATA

ARB* searchStringAndDelete(ARB* ROOT, char* stringToDelete){
    int r;
    if(ROOT!=NULL){
        r=strcmp(ROOT->stringElement, stringToDelete);
        switch(r){
            case -1:
                ROOT->dx=searchStringAndDelete(ROOT->dx, stringToDelete);
                break;
            case 0:
                ROOT=adjustARB(ROOT);
                break;
            case 1:
                ROOT->sx=searchStringAndDelete(ROOT->sx, stringToDelete);
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

ARB* searchConditionAndDeleteARB(ARB* ROOT, char* strMin, char* strMax, int odd){
    if(strcmp(strMin, strMax)>0){
        return ROOT;
    }
    if(ROOT!=NULL){
        if(strcmp(ROOT->stringElement, strMin)>=0 && strcmp(ROOT->stringElement, strMax)<=0){
            if(strcmp(ROOT->stringElement, strMin)>0){
                ROOT->sx=searchConditionAndDeleteARB(ROOT->sx, strMin, strMax,odd);
            }
            if(strcmp(ROOT->stringElement, strMax)<0){
                ROOT->dx=searchConditionAndDeleteARB(ROOT->dx, strMin, strMax, odd);
            }
            if(strlen(ROOT->stringElement)%2==odd){
                ROOT=adjustARB(ROOT);
            }
        }else{
            if(strcmp(ROOT->stringElement, strMin)>0){
                ROOT->sx=searchConditionAndDeleteARB(ROOT->sx, strMin, strMax, odd);
            }
            if(strcmp(ROOT->stringElement, strMax)<0){
                ROOT->dx=searchConditionAndDeleteARB(ROOT->dx, strMin, strMax, odd);
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
ARB* casualARB(ARB* ROOT, int numNodes){
    srand(time(NULL));
    char* toIns;
    int lenght, cicle, ch;
    while(numNodes>0){
        lenght=(rand()%LENGHT_WORD);
        cicle=0;
        toIns=(char*)malloc(lenght*(sizeof(char)));
        while(cicle<lenght){
            ch=(rand()%26)+97;
            toIns[cicle]=ch;
            cicle++;
        }
        toIns[cicle]='\0';
        ROOT=insertARBNode(ROOT, toIns);
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
ARB* duplicateARB(ARB* original){
    ARB* copy=NULL;
    if(original!=NULL){
        copy=(ARB*)malloc(sizeof(ARB));
        copy->stringElement=(char*)malloc(sizeof(char)*strlen(original->stringElement));
        strcpy(copy->stringElement, original->stringElement);
        copy->sx=duplicateARB(original->sx);
        copy->dx=duplicateARB(original->dx);
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
int controlSameARB(ARB* one, ARB* two){
    if(one!=NULL && two!=NULL){
        if(strcmp(one->stringElement, two->stringElement)==0){
            if(controlSameARB(one->sx, two->sx)==1 && controlSameARB(one->dx, two->dx)==1){
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
//SI ALLOCA PRIMA UN ARRAY DELLA STESSA DIMENSIONE DELL'ALBERO, POI SI PARTE CON IL SUO RIEMPIMENTO ORDINATO
char** vectorizeARB(ARB* toVectorize){
    int size=countARBNode(toVectorize);
    char** result;
    result=(char**)malloc(sizeof(char*)*size);
    size--;
    result=vectorizeFunction(toVectorize, result, &size);
    return result;
}

//PASSANDO LA GRANDEZZA DELL'ARRAY, L'ALGORITMO RIEMPIE A PARTIRE DALL'ULTIMO POSTO E DECREMENTA IL CONTATORE
char** vectorizeFunction(ARB* ROOT, char** vector, int* k){
    if(ROOT!=NULL){
            //RICORRE FINO A RAGGIUNGERE UN NODO NULLO
		vector=vectorizeFunction(ROOT->dx, vector, k);
    //SCENDE A DESTRA
		vector[(*k)]=(char*)malloc(sizeof(char)*strlen(ROOT->stringElement));
		strcpy(vector[(*k)],ROOT->stringElement);
		(*k)=(*k)-1;
		//ALLOCA LO SPAZIO PER LA NUOVA STRINGA E COPIA QUELLA PRESENTE NELL'ALBERO
		//DECREMENTA IL CONTATORE PER LA POSIZIONE DEI NODI
		vector=vectorizeFunction(ROOT->sx, vector, k);
		//SCENDE A SINISTRA
	}
	return vector;
}


/***
10. costruzione di un ABR perfettamente bilanciato a partire da un ARB dato (NOTA: in
un ABR perfettamente bilanciato il numero di nodi dei due sottoalberi di ogni nodo differiscono
al massimo di 1. Si sfrutti opportunamente il punto 9 per realizzare la funzionalità).
***/
//USIAMO IL VETTORE CREATO AL PUNTO 9.
ARB* balanceARB(ARB* toBalance){
    char** temp;
    ARB* result=NULL;
    int i;
    int size=countARBNode(toBalance);
    temp=vectorizeARB(toBalance);
    result=balanceFunction(temp, 0, size-1, result);
    for(i=0; i<size; i++){
        free(temp[i]);
    }
    free(temp);
    return result;
}

//PER BILANCIARE E' SUFFICIENTE RIEMPIRE LA RADICE DELL'ALBERO CON L'ELEMENTO MEDIANO DEL VETTORE ORDINATO
//POI SI PASSANO GLI ESTREMI DEI SOTTOARRAY DELIMITATI DALL'ELEMENTO MEDIANO
//SI PROCEDE IN QUESTO MODO FINCHE' NON SI INCROCIANO GLI ESTREMI PASSATI
//A QUEL PUNTO L'ALGORITMO TERMINA
ARB* balanceFunction(char** source, int i, int j, ARB* res){
    int k;
    if(i<=j){
        k=(i+j)/2;
        res=insertARBNode(res, source[k]);
        res=balanceFunction(source, i, k-1, res);
        res=balanceFunction(source, k+1, j, res);
    }
    return res;
}
