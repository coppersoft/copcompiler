#include <stdio.h>
#include <stdlib.h>
#include "copbuilder.h"
#include "registers.h"





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
    

    UWORD* copperList = compileCopperlist("copperlist_fm.pcl");

    printf("Copperlist %#20x\n",copperList);

    //UWORD wReg = resolveRegister("BLTCMOD");
    //printf("Restituito %#08x\n",wReg);

    printCopperlist(copperList);
}
