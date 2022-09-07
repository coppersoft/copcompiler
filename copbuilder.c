#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "copbuilder.h"
#include "registers.h"
#include "labels.h"

UWORD* copperList;
int     copIndex = 0;

/*
    Cannot use GNU libc's "endian.h" because is absent in Amiga's NDK, and I want this tool to be multiplatform.

    I use this simple technique to check if I'm running in a big-endian system (Amiga m68k) or a little endian system (Intel x86/64).
    
    Taken from:

    https://www.geeksforgeeks.org/little-and-big-endian-mystery/
*/
bool    isLittleEndian = true;
static void checkEndianess() {
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c)   
        isLittleEndian = true;
    else
        isLittleEndian = false;
}

/*
    Memory management stuff
*/
static void allocCopperlist() {
    copperList = (UWORD*) malloc(sizeof(UWORD) * COP_BUFFER_SIZE);

    if (copperList == NULL) {
        printf("Unable to alloc copperlist\n");
        exit(-1);
    }
}

void freeCopperlist() {
    free(copperList);
}

void writeCopperlist(char* fileName) {
    FILE* cfPtr;
    if ((cfPtr = fopen(fileName,"wb")) == NULL){
       printf("Error writing copperlist to file\n");
       exit(1);
    }
    
    fwrite(copperList,sizeof(UWORD),copIndex,cfPtr);

    fclose(cfPtr);
}

static UWORD swapBytes(UWORD word) {
    return (word>>8) | (word<<8);
}


/**
 * @brief converts 4 nibble hexadecimal string to UWORD, input MUST be XXXX
 * 
 * @param hex 
 * @return UWORD* 
 */
UWORD hex2word(char* hex) {
    UWORD value = (UWORD)strtol(hex,NULL,16);

    if (isLittleEndian) {
        value = swapBytes(value);
    }

    return value;
}

UWORD* compileCopperlist(char* copFileName) {

    checkEndianess();

    printf("Little endian?: %d\n",isLittleEndian);


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

    copperList[copIndex++] = hReg;
    copperList[copIndex++] = hVal;

}

void parseWait(char* wait) {
    char waitValue[10] = {0};
    wait+=5;
    char* endWaitValue = strchr(wait,')');

    strncpy(waitValue,wait,(endWaitValue-wait));

    printf("Valore wait: %s\n",waitValue);

    UWORD wVal = hex2word(waitValue);
    copperList[copIndex++] = wVal;
    if (isLittleEndian) {
        copperList[copIndex++] = 0xfeff;
    } else {
        copperList[copIndex++] = 0xfffe;
    }

}

void parseLabel(char* label) {
    putLabel(copIndex,label);
}

void parseSimpleValue(char* simpleValue) {
    
    UWORD wVal = hex2word(simpleValue);
    copperList[copIndex++] = wVal;
}

void addWaitEnd() {
    printf("Dentro addWaitEnd\n");
    if (isLittleEndian) {
        copperList[copIndex++] = 0xffff;
        copperList[copIndex++] = 0xfeff;
    } else {
        copperList[copIndex++] = 0xffff;
        copperList[copIndex++] = 0xfffe;
    }
    
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

    // Vediamo se è la fine della copperlist
    validToken = strstr(token,"WAIT_END");
    if (validToken != NULL) {
        addWaitEnd();
        return;
    }    

    // Vediamo se è una wait
    validToken = strstr(token,"WAIT");
    if (validToken != NULL) {
        parseWait(validToken);
        return;
    }

    

    // Vediamo se è un valore secco
    validToken = strstr(token,"0x");
    if (validToken != NULL) {
        parseSimpleValue(token);
        return;
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