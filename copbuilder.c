#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        //printf("%s",copLine);
        parseLine(copLine);
    }


    fclose(copFile);
}


void parseMove(char* move) {
    char regname[10] = {0};
    char regvalue[10] = {0};
    move+=5;
    char* startRegValue = strchr(move,'=');

    strncpy(regname,move,(startRegValue-move));
    printf("Nome del registro: %s\n",regname);

    startRegValue++;
    char* endRegValue = strchr(startRegValue,')');
    strncpy(regvalue,startRegValue,(endRegValue-startRegValue));

    printf("Valore del registro: %s\n",regvalue);

}

void parseLabel(char* label) {
    printf("E' una label: %s\n",label);
}

void parseSimpleValue(char* simpleValue) {
    printf("E' un valore semplice %s\n",simpleValue);
}


void parseToken(char* token) {
    printf("Parso il token '%s-\n",token);
    char* validToken = NULL;

    // Vedo se è una label
    validToken = strchr(token,':');
    if (validToken != NULL) {
        parseLabel(token);
        return;
    }

    // Vediamo se è un MOVE
    validToken = strstr(token,"MOVE");
    if (validToken != NULL) {
        printf("Trovato MOVE '%s'\n",validToken);
        parseMove(validToken);
        return;
    }

    // Vediamo se è un valore secco
    validToken = strstr(token,"0x");
    if (validToken != NULL) {
        parseSimpleValue(token);
    }
}

void parseLine(char* line) {
    char * token = strtok(line, ",");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        parseToken(token);
        token = strtok(NULL, ",");
    }
}