#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "es2.h"
#include "data.h"


int main(){
    void*k=NULL;
    k=insertInteger();
    printf("\n%d\n", oddInteger(k, 1));
    return 0;
}
