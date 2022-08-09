#include <stdio.h>
#include <stdlib.h>
#include "copbuilder.h"
#include "registers.h"

UWORD copperlist[] = {
	1,2,
	3,4,
	5,6,
	0xffff,0xfffe
};




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
    

    compileCopperlist("copperlist.pcl");

    

    //UWORD wReg = resolveRegister("BLTCMOD");
    //printf("Restituito %#08x\n",wReg);


}
