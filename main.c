/*
    Planar framework - Copperlist compiler

    (C) 2022 - Lorenzo Di Gaetano
*/

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

    printCopperlist(copperList);
    
    printLabels();
    
    writeCopperlist("Outputcop.bin");
    writeLabels("Labels.txt");

    freeCopperlist();
    freeLabels();
}
