#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "copbuilder.h"
#include "registers.h"



UWORD* copperList;
char*   labels;
int     copIndex = 0;
int     lblIndex = 0;



static void allocCopperlist() {
    copperList = (UWORD*) malloc(sizeof(UWORD) * COP_BUFFER_SIZE);

    if (copperList == NULL) {
        printf("Unable to alloc copperlist\n");
        exit(-1);
    }
}

static void allocLabels() {
    labels = (char*) malloc(sizeof(char) * LABELS_BUFFER_SIZE);
}

void freeCopperlist() {
    free(copperList);
}

void freeLabels() {
    free(labels);
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

    allocCopperlist();
    allocLabels();

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

    return copperList;
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

    

    UWORD hReg = resolveRegister(regname);
    UWORD hVal = hex2word(regvalue);

    

    printf("Valori reg %d , val %d\n\n",hReg,hVal);

    //*(copperList) = hReg;
    copperList[copIndex++] = hReg;
    copperList[copIndex++] = hVal;

}

void parseLabel(char* label) {
    printf("E' una label: %s\n",label);
}

void parseSimpleValue(char* simpleValue) {
    printf("E' un valore semplice %s\n",simpleValue);
}

void addWaitEnd() {
    copperList[copIndex++] = 0xffff;
    copperList[copIndex++] = 0xfffe;
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

    // Vediamo se è la fine della copperlist
    validToken = strstr(token,"WAIT_END");
    if (validToken != NULL) {
        addWaitEnd();
    }

    printf("\n\n\n");
}

void parseLine(char* line) {
    char * token = strtok(line, ",");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        parseToken(token);
        token = strtok(NULL, ",");
    }
}