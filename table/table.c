#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

table_t *initTable() {
  table_t *T = malloc(sizeof(table_t));
  T->length = 0;
  return T;
}

line_t initLine(int val) {
  line_t L;
  L.line = val;
  L.next = NULL;
  return L;
}

col_t *initCol(int col, int val) {
  col_t *C = malloc(sizeof(col_t));
  C->col = col;
  C->val = val;
  C->next = NULL;
  return C;
}

int shiftRight(line_t *tab, int rank, int end) {
  for (int i = end; i > rank; i--) {
    tab[i] = tab[i - 1];
  }
  return 0;
}

int insertCol(col_t *new, col_t **root) {
  col_t **curr = root;
  while (*curr != NULL && (*curr)->col < new->col) {
    curr = &(*curr)->next;
  }
  new->next = *curr;
  *curr = new;
  return 0;
}

int insertTable(table_t *T, int line, int col, int val) {
  int end = T->length;
  int start = 0;
  int mid = (end + start) / 2;
  while (end != 0 && end != start) {
    if (T->tab[mid].line >= line) {
      end = mid;

    } else {
      start = mid + 1;
    }
    mid = (end + start) / 2;
  }
  if (T->length == 0 || T->tab[start].line != line) {
    shiftRight(T->tab, mid, T->length);
    T->tab[start] = initLine(line);
    T->length++;
  }

  col_t *c = initCol(col, val);
  insertCol(c, &(T->tab[start].next));
  return 0;
}

void prettyPrintLine(line_t l) {
  col_t *curr = l.next;
  while (curr != NULL) {
    printf("    col: %d => val: %d\n", curr->col, curr->val);
    curr = curr->next;
  }
}

void prettyPrintTable(table_t *T) {
  if (T != NULL) {
    for (int i = 0; i < T->length; i++) {
      printf("\n==========================\n"
             "                Line %d    \n"
             "==========================\n",
             T->tab[i].line);
      prettyPrintLine(T->tab[i]);
    }
  }
}

int valueOf(table_t *T, int line, int col, int *code) {
  int i = 0;
  int val = -1;
  *code = 0;
  while (i < T->length && T->tab[i].line < line)
    i++;

  if (i == T->length || T->tab[i].line != line) {
    printf("No line %d exist in this matrix\n", line);
  } else {
    col_t *curr = T->tab[i].next;
    while (curr != NULL && curr->col < col)
      curr = curr->next;

    if (curr == NULL || curr->col != col) {
      printf("The line %d doesn't contain a value in the %d column\n", line,
             col);
    } else {
      *code = 1;
      val = curr->val;
    }
  }
  return val;
}

void freeTable(table_t *T) {
  for (int i = 0; i < T->length; i++)
    freeLine(T->tab[i]);
  free(T);
}

void freeLine(line_t line) {
  col_t *curr = line.next;
  col_t *supr;
  while (curr != NULL) {
    supr = curr;
    curr = curr->next;
    freeCol(supr);
  }
}

void freeCol(col_t *col) { free(col); }
