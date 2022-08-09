#include <stdlib.h>
#include <stdbool.h>

typedef unsigned short  UWORD;

#define     COP_BUFFER_SIZE      1000
#define     COP_MAX_LINE_SIZE    100


void freeCopperlist(UWORD* copList);

UWORD* compileCopperlist(char* copFileName);

UWORD hex2word(char* hex);

void parseLine(char* line);
