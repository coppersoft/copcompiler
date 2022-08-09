#include <stdlib.h>
#include <stdbool.h>

typedef unsigned short  UWORD;

#define     COP_BUFFER_SIZE      1000


void freeCopperlist(UWORD* copList);

UWORD* compileCopperlist(char* copFileName);

UWORD hex2word(char* hex);
