#include "copbuilder.h"
#include <stdio.h>
#include <string.h>

int lblIndex = 0;

#define     LABEL_SIZE      80

char*   labels;

static void removeCr(char* label) {
    int sLen = strlen(label);
    for (int i=0 ; i < sLen; i++) {
        if (label[i] == '\n') {
            label[i] = 0;
            return;
        } 
    }
}

void putLabel(int index, char* label) {
    removeCr(label);
    char labelLine[LABEL_SIZE];
    int sLen = strlen(label);
    snprintf(labelLine,sLen+6,"%s %d\n",label,index);
    strcat(labels,labelLine);
}

void allocLabels() {
    labels = (char*) malloc(sizeof(char) * LABELS_BUFFER_SIZE);
}

void freeLabels() {
    free(labels);
}

void printLabels() {
    printf("%s\n",labels);
}

void writeLabels(char* fileName) {
    FILE* lfPtr;
    if ((lfPtr = fopen(fileName,"wb")) == NULL){
       printf("Error writing labels to file\n");
       exit(1);
    }
    
    int pos = 0;
    char actChar;
    while ((actChar = labels[pos++]) != 0) {
        fputc(actChar,lfPtr);
    }
    fclose(lfPtr);
}