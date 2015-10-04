
/*

CORRESPONDENCE_TABLE* initCorrespondenceTable(int dim, LIST_OPERATION* lId, HASH_OPERATION* hId, LIST_OPERATION* lIndex, HASH_OPERATION* hIndex){
    CORRESPONDENCE_TABLE* ret=(CORRESPONDENCE_TABLE*)malloc(sizeof(CORRESPONDENCE_TABLE));
    ret->correspondenceID=initHashTable(hId, lId, dim);
    ret->correspondenceIndex=initHashTable(hIndex, lIndex, dim);
    return ret;
}

CORRESPONDENCE_TABLE* insertIntoCorrespondenceTable(CORRESPONDENCE_TABLE* table, CORRESPONDENCE *toInsert){

    printf("printf: \n");
    printString(stdout, toInsert->ID);
    printf("\nk\n");
    copyInfoNode temp=table->correspondenceID->operationList->copy;
    table->correspondenceID->operationList->copy=&copyCorrespondance;


    table->correspondenceID=insertIntoHashTable(table->correspondenceID, toInsert);

    table->correspondenceID->operationList->copy=temp;

    temp=table->correspondenceIndex->operationList->copy;
    table->correspondenceIndex->operationList->copy=&copyCorrespondance;


    table->correspondenceIndex=insertIntoHashTable(table->correspondenceIndex, toInsert);

    table->correspondenceIndex->operationList->copy=temp;


//    table->correspondenceID=insertIntoHashTable(table->correspondenceID, toInsert->ID);
  //  table->correspondenceIndex=insertIntoHashTable(table->correspondenceIndex, (void*)(&(toInsert->index)));
    return table;
}

CORRESPONDENCE_TABLE* deleteFromCorrespondeceTable(CORRESPONDENCE_TABLE* table, CORRESPONDENCE* toDel){
    table->correspondenceID=deleteFromHashTable(table->correspondenceID, toDel->ID);
    table->correspondenceIndex=deleteFromHashTable(table->correspondenceIndex, (void*)(&(toDel->index)));
    return table;
}

CORRESPONDENCE* searchCorrespondenceByID(CORRESPONDENCE_TABLE* table, void* id){
    CORRESPONDENCE temp;
    temp.ID=id;
    temp.index=0;
    return (CORRESPONDENCE*)searchInfoIntoHash(table->correspondenceID, id);
}

CORRESPONDENCE* searchCorrespondenceByIndex(CORRESPONDENCE_TABLE* table, unsigned int index){
    CORRESPONDENCE temp;
    temp.ID=NULL;
    temp.index=index;
    return (CORRESPONDENCE*)searchInfoIntoHash(table->correspondenceIndex, &temp);
}

void printCorrespondenceTable(FILE* fp, CORRESPONDENCE_TABLE* table){
    printHashTable(fp, table->correspondenceID);
    fprintf(fp, "\n");
    printHashTable(fp, table->correspondenceIndex);
}

void changeIndex(CORRESPONDENCE_TABLE* table, unsigned int oldIndex, unsigned int newIndex){
    void* temp;
    CORRESPONDENCE toSearch, *searched;
    searched=searchCorrespondenceByIndex(table, oldIndex);
    searched->index=newIndex;
}



void* copyCorrespondance(void* toAlloc, void* funTo){
//    CORRESPONDENCE* ret=(CORRESPONDENCE*)malloc(sizeof(CORRESPONDENCE));
//    ((LIST_OPERATION*)(funTo))->copy(ret->ID, toAlloc);
//    ret->index=((CORRESPONDENCE*)toAlloc)->index;
//    return ret;
    return toAlloc;
}

void* deallocCorrespondence(void* toDealloc, void* funTo){
    ((LIST_OPERATION*)(funTo))->dealloc(toDealloc);
    free((CORRESPONDENCE*)toDealloc);
    toDealloc=NULL;
    return NULL;
}


int compareCorrespondenceID(void* a, void* b, void* funTo){
    return ((LIST_OPERATION*)funTo)->compare(((CORRESPONDENCE*)a)->ID, ((CORRESPONDENCE*)b)->ID);
}

int compareCorrespondanceIndex(void* a, void* b, void* funTo){
    int r=0;
    if(((CORRESPONDENCE*)a)->index>((CORRESPONDENCE*)b)->index)
        r=1;
    else if(((CORRESPONDENCE*)a)->index<((CORRESPONDENCE*)b)->index)
        r=-1;
    return r;
}

void printCorrespondence(FILE* fp, void* toPrint, void* funTo){
    fprintf(fp, "ID -> ");
   //printString(fp, ((CORRESPONDENCE*)(toPrint))->ID);
    ((LIST_OPERATION*)funTo)->print(fp, ((CORRESPONDENCE*)toPrint)->ID);
    fprintf(fp, " | index -> %d", ((CORRESPONDENCE*)toPrint)->index);
}


unsigned int correspondenceHashId(void* corr, void* funTo){
    return ((HASH_OPERATION*)funTo)->hashing(((CORRESPONDENCE*)corr)->ID);
}

unsigned int correspondenceHashIndex(void* corr, void* funTo){
    return ((CORRESPONDENCE*)corr)->index;
}

void* collisionCorrespondance(void* corr, void* funTo){
    return corr;
}

*/
