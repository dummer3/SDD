#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEmptyPile(pile_t *pile) { return pile->sommet == -1; }
int isFullPile(pile_t *pile) { return pile->sommet + 1 == pile->taille; }

pile_t *initPile(int taille, int *code) {

  pile_t *nouv = NULL;
  *code = -1;

  if (taille > 0) {

    if ((nouv = malloc(sizeof(pile_t)))) {
      nouv->taille = taille;
      nouv->sommet = -1;
      nouv->tab = malloc(sizeof(T) * taille);
      *code = 0;
    }
  }
  return nouv;
}

void freePile(pile_t *pile) {
  free(pile->tab);
  free(pile);
}

void empiler(pile_t *pile, T nouv, int *code) {
  *code = -1;
  if (!isFullPile(pile)) {
    (pile->sommet)++;
    pile->tab[pile->sommet] = nouv;
    *code = 0;
  }
}

T depiler(pile_t *pile, int *code) {
  T val = sommetPile(pile, code);
  if (*code != -1) {
    *code = -1;
    if (!isEmptyPile(pile)) {
      *code = 0;
      pile->sommet--;
    }
  }
  return val;
}

T sommetPile(pile_t *pile, int *code) {
  *code = isEmptyPile(pile) ? -1 : 0;
  return pile->tab[pile->sommet];
}

void prettyPrintPile(pile_t *pile, char *(toString)(T)) {
  printf(""
         "\n=====================================\n"
         "                 PILE                \n"
         "=====================================\n\n"
         "");

  for (int i = 0; i <= pile->sommet; i++) {
    char *buffer = toString(pile->tab[i]);
    printf("| indice : %d | val : %s |\n", i, buffer);
    free(buffer);
  }

  printf(""
         "\n=====================================\n"
         "               FIN PILE              \n"
         "=====================================\n\n"
         "");
}
