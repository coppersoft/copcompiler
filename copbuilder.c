#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "copbuilder.h"






static UWORD* allocCopperlist() {
    UWORD* copPtr = (UWORD*) malloc(sizeof(UWORD) * COP_BUFFER_SIZE);

    if (copPtr == NULL) {
        printf("Unable to alloc copperlist\n");
        exit(-1);
    }
    return copPtr;
}

void freeCopperlist(UWORD* copperList) {
    free(copperList);
}

/**
 * @brief converts 4 nibble hexadecimal string to UWORD, input MUST be XXXX
 * 
 * @param hex 
 * @return UWORD* 
 */
UWORD hex2word(char* hex) {
    UWORD value = (UWORD)strtol(hex,NULL,16);

    return value;

}



UWORD* compileCopperlist(char* copFileName) {
    char    copLine[COP_MAX_LINE_SIZE];

    FILE* copFile = fopen(copFileName,"r");

    if (!copFile) {
        printf("Errore nella lettura del file\n");
        exit(-1);
    }

    while (fgets(copLine, COP_MAX_LINE_SIZE, copFile))
    {  
        printf("%s",copLine);
    }


    fclose(copFile);
}