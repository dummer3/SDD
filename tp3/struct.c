#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *toString(T cell) {
  char *retour = malloc(10);
  sprintf(retour, "%d\n", cell->value);
  return retour;
}
