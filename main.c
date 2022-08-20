#include <stdio.h>
#include <stdlib.h>
#include "copbuilder.h"
#include "registers.h"
#include "labels.h"





void printCopperlist(UWORD* copperlist) {
	int index = 0;
	
	while (1) {
        UWORD w1,w2;
        w1 = (UWORD)*(copperlist++);
        w2 = (UWORD)*(copperlist++);
        printf("%d: %#06x, %#06x\n",index, w1,w2);
        index+=2;
        if (w1 == 0xffff) break;
    }
}


int main () {
    
    allocLabels();
    UWORD* copperList = compileCopperlist("copperlist.pcl");


    //printCopperlist(copperList);
/* 
    char prova[20];

    snprintf(prova,20,"%s %d","miaLabel:",30);

    printf("%s\n",prova); */

    printCopperlist(copperList);
    
    printLabels();
    
    writeCopperlist("Outputcop.bin");

    freeLabels();
}
