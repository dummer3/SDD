#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  table_t *T = initTable();

  FILE *F = fopen("mat.txt", "r");
  int line, column, value;
  while (fscanf(F, "%d %d %d\n", &line, &column, &value) != EOF) {
    insertTable(T, line, column, value);
  }
  fclose(F);

  prettyPrintTable(T);

  printf("\n=====================================================\n\n");

  int *code = malloc(4);
  printf("valeur de (%d,%d) est %d\n", 1, 1, valueOf(T, 1, 1, code));
  printf("valeur de (%d,%d) est %d\n", 1, 0, valueOf(T, 1, 0, code));
  printf("valeur de (%d,%d) est %d\n", 0, 1, valueOf(T, 0, 1, code));
  printf("valeur de (%d,%d) est %d\n", 100, 100, valueOf(T, 100, 100, code));
  printf("valeur de (%d,%d) est %d\n", 30, 30, valueOf(T, 30, 30, code));
  printf("valeur de (%d,%d) est %d\n", 25, 30, valueOf(T, 25, 30, code));

  freeTable(T);
  free(code);

  return 0;
}
