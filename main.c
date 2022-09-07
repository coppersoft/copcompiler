/*
    Planar framework - Copperlist compiler

    (C) 2022 - Lorenzo Di Gaetano
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "copbuilder.h"
#include "registers.h"
#include "labels.h"

#define FILENAMES_SIZE      100

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

static void printInstructions() {
    printf("Usage: \n\n");
    printf("copbuilder <copperlistfile> <outputfile> <labelsfile>\n");
}

int main (int argc, char** argv) {
    
    char  outputfilename[FILENAMES_SIZE];
    char  labelsfilename[FILENAMES_SIZE];
    
    if (argc < 2) {
        printInstructions();
        exit(0);
    }

    char* filename = argv[1];

    // outputfilename
    if (argc > 3) {
        strcpy(outputfilename,argv[2]);
    } else {
        int len = strlen (filename);
        strcpy(outputfilename,filename);
        strcpy(&outputfilename[len],".bin");
    }

    if (argc == 4) {
        strcpy(labelsfilename,argv[3]);
    } else {
        int len = strlen (filename);
        strcpy(labelsfilename,filename);
        strcpy(&labelsfilename[len],"_labels.txt");
    }

    allocLabels();
    UWORD* copperList = compileCopperlist(filename);

    printCopperlist(copperList);
    
    printLabels();
    
    writeCopperlist(outputfilename);
    writeLabels(labelsfilename);

    freeCopperlist();
    freeLabels();
}
