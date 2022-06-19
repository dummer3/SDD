#include "file.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverser(pile_t *pile, int *code) {
  file_t *file = initFile(5, code);
  while (!isEmptyPile(pile)) {
    enfiler(file, sommetPile(pile));
    depiler(pile, code);
  }
  while (!isEmptyFile(file)) {
    empiler(pile, sommetFile(file, code));
    defiler(file, code);
  }
  freeFile(file);
}

int main() {
  printf(""
         "\n==========================================================\n"
         "                           PILE                             \n"
         "==========================================================\n\n"
         "");
  int code;
  pile_t *pile = initPile(5, &code);
  if (code == 0) {
    printf("\nisEmpty ? %d\n", isEmptyPile(pile));
    printf("isFull ? %d\n", isFullPile(pile));
    printf("\n==========================================================\n\n");
    empiler(pile, 0);
    printf("isEmpty ? %d\n", isEmptyPile(pile));
    printf("isFull ? %d\n", isFullPile(pile));
    printf("\n==========================================================\n\n");
    empiler(pile, 1);
    empiler(pile, 2);
    empiler(pile, 3);
    empiler(pile, 4);
    printf("isEmpty ? %d\n", isEmptyPile(pile));
    printf("isFull ? %d\n", isFullPile(pile));
    printf("\n==========================================================\n\n");

    printf("Avant inversion :\n");
    prettyPrintPile(pile, toString);

    inverser(pile, &code);

    printf("Après inversion :\n");
    prettyPrintPile(pile, toString);
  }

  freePile(pile);

  printf(""
         "\n==========================================================\n"
         "                           FILE                             \n"
         "==========================================================\n\n"
         "");

  file_t *file = initFile(5, &code);
  if (code == 0) {
    printf("\nisEmpty ? %d\n", isEmptyFile(file));
    printf("isFull ? %d\n", isFullFile(file));
    printf("\n==========================================================\n\n");
    enfiler(file, 0);
    printf("isEmpty ? %d\n", isEmptyFile(file));
    printf("isFull ? %d\n", isFullFile(file));
    printf("\n==========================================================\n\n");
    enfiler(file, 1);
    enfiler(file, 2);
    enfiler(file, 3);
    enfiler(file, 4);
    printf("isEmpty ? %d\n", isEmptyFile(file));
    printf("isFull ? %d\n", isFullFile(file));
    printf("\n==========================================================\n\n");
    prettyPrintFile(file);

    defiler(file, &code);
    defiler(file, &code);
    prettyPrintFile(file);
    printf("isEmpty ? %d\n", isEmptyFile(file));
    printf("isFull ? %d\n", isFullFile(file));
    enfiler(file, 10);
    enfiler(file, 42);
    printf("isEmpty ? %d\n", isEmptyFile(file));
    printf("isFull ? %d\n", isFullFile(file));
    prettyPrintFile(file);
    sommetFile(file, &code);
  }

  freeFile(file);

  printf(""
         "\n==========================================================\n"
         "                      PILE LE RETOUR                        \n"
         "==========================================================\n\n"
         "");

  pile_t *pile2 = initPile(5, &code);
  if (code == 0) {
    printf("\nisEmpty ? %d\n", isEmptyPile(pile2));
    printf("isFull ? %d\n", isFullPile(pile2));
    printf("\n==========================================================\n\n");
    empiler(pile2, 0);
    printf("isEmpty ? %d\n", isEmptyPile(pile2));
    printf("isFull ? %d\n", isFullPile(pile2));
    printf("\n==========================================================\n\n");
    empiler(pile2, 1);
    empiler(pile2, 2);
    empiler(pile2, 3);
    empiler(pile2, 4);
    printf("isEmpty ? %d\n", isEmptyPile(pile2));
    printf("isFull ? %d\n", isFullPile(pile2));
    printf("\n==========================================================\n\n");
    prettyPrintPile(pile2, toString);

    depiler(pile2, &code);
    depiler(pile2, &code);
    prettyPrintPile(pile2, toString);
    printf("isEmpty ? %d\n", isEmptyPile(pile2));
    printf("isFull ? %d\n", isFullPile(pile2));
    empiler(pile2, 10);
    empiler(pile2, 42);
    printf("isEmpty ? %d\n", isEmptyPile(pile2));
    printf("isFull ? %d\n", isFullPile(pile2));
    prettyPrintPile(pile2, toString);
    sommetPile(pile2);
  }

  freePile(pile2);

  return 0;
}
