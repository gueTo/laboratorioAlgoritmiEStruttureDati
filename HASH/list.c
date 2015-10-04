#include <stdlib.h>
#include <stdio.h>
#ifndef _LIST_H_
    #define _LIST_H_
    #include "list.h"
#endif // _LIST_H_

OPERAZIONI_LISTA InserisciFunzioni(void *(*AllocaDato)(void *, void *), void (*StampaDato)(FILE *, void *, void *),
                                  int (*ComparaDati)(void *, void *, void *),  void *(*GestisciCollisione)(void *, void *),
                                  void (*DeallocaDato)(void *, void *), void *(*LeggiDaInput)(void *, void *),
                                  unsigned long (*FunzioneHash)(void *, void *)){
    OPERAZIONI_LISTA fun;
    fun.allocaDato = AllocaDato;
    fun.stampaDato = StampaDato;
    fun.comparaDati = ComparaDati;
    fun.gestisciCollisione = GestisciCollisione;
    fun.deallocaDato = DeallocaDato;
    fun.leggiDaInput = LeggiDaInput;
    fun.funzioneHash = FunzioneHash;
    return fun;
}

NODO_LISTA* nuovoNodo(void* elem){
    NODO_LISTA* ret=(NODO_LISTA*)malloc(sizeof(NODO_LISTA));
    ret->elem=elem;
    return ret;
}

LIST inserisciNuovoNodo(LIST HEAD, OPERAZIONI_LISTA* op, NODO_LISTA* node, void* par){
    if(HEAD==NULL || op->comparaDati(HEAD->elem, node->elem, par)>0 ){
        node->next=HEAD;
        HEAD=node;
    }else if(op->comparaDati(HEAD->elem, node->elem, par)<0){
        HEAD->next=inserisciNuovoNodo(HEAD->next, op, node, par);
    }else if(op->comparaDati(HEAD->elem, node->elem, par)==0){
        node->elem=op->gestisciCollisione(node->elem, par);
        if(node->elem==NULL){
            op->deallocaDato(node, par);
        }else{
            node->next=HEAD;
            HEAD=node;
        }
    }
    return HEAD;
}

NODO_LISTA* cercaNodo(LIST HEAD, OPERAZIONI_LISTA* op, void* cerca, void* par){
    if(HEAD!=NULL){
        if(op->comparaDati(HEAD->elem, cerca, par)==0){
            return HEAD;
        }else if(op->comparaDati(HEAD->elem, cerca, par)<0){
            return cercaNodo(HEAD->next, op, cerca, par);
        }else return NULL;
    }else return NULL;
}


NODO_LISTA* deallocaNodo(NODO_LISTA* daDeallocare, OPERAZIONI_LISTA* op, void* par){
    op->deallocaDato(daDeallocare->elem, par);
    free(daDeallocare);
    return NULL;
}

LIST cancellaDallaLista(LIST HEAD, OPERAZIONI_LISTA* op, void* daCancellare, void* par){
    if(HEAD!=NULL){
        if(op->comparaDati(HEAD->elem, daCancellare, par)==0){
            NODO_LISTA* temp;
            temp=HEAD;
            HEAD=HEAD->next;
            deallocaNodo(temp, op, par);
        }else if(op->comparaDati(HEAD->elem, daCancellare, par)<0){
            HEAD->next=cancellaDallaLista(HEAD->next, op, daCancellare, par);
        }
    }
    return HEAD;
}



void stampaLista(FILE *fp, LIST HEAD, OPERAZIONI_LISTA* op, void *param){
  if(HEAD!=NULL){
    op->stampaDato(fp, HEAD->elem, param);
    fprintf(fp, " ");
    stampaLista(fp, HEAD->next, op, param);
  }
  else
    fprintf(fp, "\n");
}

LIST deallocaLista(LIST HEAD, OPERAZIONI_LISTA* op, void* par){
    if(HEAD!=NULL){
        HEAD->next=deallocaLista(HEAD->next, op, par);
        HEAD=deallocaNodo(HEAD, op, par);
    }
    return NULL;
}


LIST PushLista(LIST HEAD, void *id){
  NODO_LISTA *ret;
  ret = nuovoNodo(id);
  ret->next = HEAD;
  return ret;
}

LIST PopLista(LIST HEAD){
    NODO_LISTA* temp;
    temp=HEAD;
    HEAD=HEAD->next;
    free(temp);
    return HEAD;
}

void *TopLista(LIST HEAD){
    if(HEAD!=NULL){
        return HEAD->elem;
    }
    return NULL;
}
