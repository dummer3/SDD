#ifndef PILE_H
#define PILE_H

#include "struct.h"

typedef struct pile {
  int taille;
  int sommet;
  T *tab;
} pile_t;

pile_t *initPile(int taille, int *code);
void freePile(pile_t *pile);

void empiler(pile_t *pile, T nouv, int *code);
int depiler(pile_t *pile, int *code);
T sommetPile(pile_t *pile, int *code);

int isEmptyPile(pile_t *pile);
int isFullPile(pile_t *pile);

void prettyPrintPile(pile_t *pile, char *(toString)(T));

#endif
