#ifndef TABLE_H
#define TABLE_H

#define N 10000

typedef struct col {
  int col;
  int val;
  struct col *next;
} col_t;

typedef struct line {
  int line;
  col_t *next;
} line_t;

typedef struct table {
  int length;
  line_t tab[N];
} table_t;

line_t initLine(int val);
col_t *initCol(int col, int val);
table_t *initTable();

int insertTable(table_t *tab, int line, int col, int val);
int insertCol(col_t *new, col_t **root);

void prettyPrintLine(line_t l);
void prettyPrintTable(table_t *T);

int valueOf(table_t *T, int line, int col, int *code);

void freeTable(table_t *T);
void freeLine(line_t line);
void freeCol(col_t *col);

#endif
