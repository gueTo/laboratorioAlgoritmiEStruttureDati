/****************************************
	Antonio Guerriero
	N86/000900

INSERIRE DESCRIZIONE CODICE

****************************************/
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "correspondence.h"
int main(){

    CORRESPONDENCE *in, *out;
    HASH_OPERATION* h_id, *h_index;
    LIST_OPERATION* l_id, *l_index;
    CORRESPONDENCE_TABLE* table;
    h_id=initHashOperation(hashCorrespondenceID, collisionString);
    h_index=initHashOperation(hashCorrespondenceIndex, collisionInteger);
    l_id=initListOperation(insertString, copyString, deleteString, compareString, printString);
    l_index=initListOperation(insertInteger, copyInteger, deleteInteger, compareInteger, printInteger);
    table=initCorresponcendeTable(6, l_id, l_index, h_id, h_index);
    in=newCorrespondence("ooo", 4, table->correspondenceID->l_operation->cpy, NULL);
    table=insertIntoCorrespondenceTable(table, in, NULL);

    in=newCorrespondence("aaa", 2, table->correspondenceID->l_operation->cpy, NULL);
    table=insertIntoCorrespondenceTable(table, in, NULL);

    in=newCorrespondence("sfgvdbxcv", 9, table->correspondenceID->l_operation->cpy, NULL);
    table=insertIntoCorrespondenceTable(table, in, NULL);

    in=newCorrespondence("esfzvc", 0, table->correspondenceID->l_operation->cpy, NULL);
    table=insertIntoCorrespondenceTable(table, in, NULL);

    //table=removeFromCorrespondenceTableByIndex(table, 4, NULL);
    printCorrespondenceTable(stdout, table, NULL);
    //freeCorrespondenceTable(table, NULL);


    return 0;
}
