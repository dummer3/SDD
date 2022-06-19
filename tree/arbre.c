#include "arbre.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cellule_t *initCell(int value) {
  cellule_t *c = malloc(sizeof(cellule_t));
  c->value = value;
  c->filsG = NULL;
  c->filsD = NULL;
  return c;
}

void freeCellule(cellule_t *cell) { free(cell); }

void freeTree(cellule_t **tree) {
  int *code = malloc(sizeof(int));
  pile_t *p = initPile(MAXINT, code);
  cellule_t *temp;
  cellule_t *curr = *tree;
  while (curr) {
    empiler(p, curr, code);
    curr = curr->filsG;
    while (curr == NULL && !isEmptyPile(p)) {
      temp = depiler(p, code);
      curr = temp->filsD;
      freeCellule(temp);
    }
  }
  free(code);
  freePile(p);
}

void insertCell(cellule_t **pTree, cellule_t *cell) {
  if (*pTree == NULL) {
    *pTree = cell;
  } else {
    if ((*pTree)->value > cell->value)
      insertCell(&(*pTree)->filsG, cell);
    else
      insertCell(&(*pTree)->filsD, cell);
  }
}

void prettyPrintRecur(cellule_t *tree) {
  if (tree != NULL) {
    prettyPrint(tree->filsG);
    printf("%d\n", tree->value);
    prettyPrint(tree->filsD);
  }
}

void prettyPrint(cellule_t *tree) {
  int *code = malloc(sizeof(int));
  pile_t *p = initPile(MAXINT, code);
  cellule_t *curr = tree;
  while (curr) {
    empiler(p, curr, code);
    curr = curr->filsG;
    while (curr == NULL && !isEmptyPile(p)) {
      curr = depiler(p, code);
      printf("%d\n", curr->value);
      curr = curr->filsD;
    }
  }
  free(code);
  freePile(p);
}

cellule_t **SearchPrevious(cellule_t **pTree, int value,
                           cellule_t **subTreeReplace,
                           cellule_t **subTreeOtherSide) {
  cellule_t **prec = pTree;
  cellule_t *curr = *pTree;
  *subTreeReplace = curr->filsD;
  *subTreeOtherSide = curr->filsG;
  int val = curr->value;

  // Si vraiment aucune condition parcours avec pile, si empile alors N = filsG,
  // Si dépile alors N = filsD
  // Parcours en profondeur pour trouver le prec

  while ((curr->filsG != NULL || curr->filsD != NULL) && val != value) {
    if (curr->value > value) {

      prec = &(curr->filsG);
      *subTreeReplace = curr->filsG;
      *subTreeOtherSide = curr->filsD;
      curr = *prec;

    } else {
      prec = &(curr->filsD);
      *subTreeReplace = curr->filsD;
      *subTreeOtherSide = curr->filsG;
      curr = *prec;
    }
  }

  return prec;
}

cellule_t **findSmallest(cellule_t **tree) {
  cellule_t *curr = *tree;
  cellule_t **prec = tree;
  while (curr) {
    prec = &(curr->filsG);
    curr = curr->filsG;
  }
  return prec;
}

void suppr(cellule_t **pTree, int value) {
  cellule_t *subTreeOtherSide = NULL;
  cellule_t *subTreeReplace = NULL;
  cellule_t **prec =
      SearchPrevious(pTree, value, &subTreeReplace, &subTreeOtherSide);

  if ((*prec)->value != value) {
    fprintf(stderr, "ERROR : VALUE IS NOT INSIDE THE TREE\n");
  } else {
    cellule_t *suppr = *prec;

    *prec = subTreeReplace;
    cellule_t **temp = findSmallest(prec);
    *temp = subTreeOtherSide;
    freeCellule(suppr);
  }
}

int parcoursProfondeur(cellule_t *pTree) {
  int i = 0;
  int iMax = 0;
  cellule_t *cours = pTree;
  int *p = malloc(sizeof(int));
  pile_t *pile = initPile(MAXINT, p);
  int fin = 0;
  while (!fin) {
    while (cours != NULL) {
      empiler(pile, cours, p);
      i++;
      printf("\n\nétape : %d, %d\n\n", cours->value, i);
      cours = (cours->filsG);
    }
    if (i > iMax) {
      iMax = i;
    }
    if (!isEmptyPile(pile)) {
      cours = depiler(pile, p);
      i--;
      cours = (cours->filsD);
    } else {
      fin = 1;
    }
  }

  return iMax;
}
