#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *toString(T i) {
  char *retour = malloc(10);
  sprintf(retour, "%d", i);
  return retour;
}
