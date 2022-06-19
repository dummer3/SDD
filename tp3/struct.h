#ifndef STRUCT_H
#define STRUCT_H

typedef struct cellule {
  int value;
  struct cellule *filsG;
  struct cellule *filsD;
} cellule_t;

typedef cellule_t *T;

char *toString(T);

#endif
