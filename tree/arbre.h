#ifndef ARBRE_H
#define ARBRE_H

#include "pile.h"
#include "struct.h"

cellule_t *initCell(int value);

void freeCellule(cellule_t *cell);

void freeTree(cellule_t **tree);

void insertCell(cellule_t **root, cellule_t *cell);

void prettyPrint(cellule_t *root);

void prettyPrintRecur(cellule_t *tree);

void suppr(cellule_t **pTree, int value);

int parcoursProfondeur(cellule_t *pTree);

#endif
