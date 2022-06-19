#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

void read(char nom[], cellule_t **pTree) {
  FILE *f = fopen(nom, "r");
  if (f) {
    int num;
    while (fscanf(f, "%d\n", &num) == 1) {
      cellule_t *c = initCell(num);
      insertCell(pTree, c);
    }
    free(f);
  }
}

int main(int argc, char *argv[]) {
  cellule_t *tree = NULL;
  if (argc == 2) {
    read(argv[1], &tree);
  }
  prettyPrint(tree);
  printf("\n============================================\n\n");
  prettyPrintRecur(tree);
  printf("\n============================================\n\n");
  printf("%d\n", parcoursProfondeur(tree));
  printf("\n============================================\n\n");
  suppr(&tree, 2);
  prettyPrint(tree);
  printf("\n============================================\n\n");
  suppr(&tree, 6);
  prettyPrint(tree);
  printf("\n============================================\n\n");
  suppr(&tree, 8);
  prettyPrint(tree);
  printf("\n============================================\n\n");
  suppr(&tree, 4);
  prettyPrint(tree);
  printf("\n============================================\n\n");
  suppr(&tree, -1);
  prettyPrint(tree);

  freeTree(&tree);
  return 0;
}
