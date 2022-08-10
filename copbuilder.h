#include <stdlib.h>
#include <stdbool.h>

typedef unsigned short  UWORD;

#define     COP_BUFFER_SIZE      10000
#define     LABELS_BUFFER_SIZE    10000
#define     COP_MAX_LINE_SIZE    100



UWORD* compileCopperlist(char* copFileName);

UWORD hex2word(char* hex);

void parseLine(char* line);

void freeCopperlist();
void freeLabels();
