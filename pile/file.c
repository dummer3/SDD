#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isEmptyFile(file_t *file) { return file->nbr_element == 0; }
int isFullFile(file_t *file) { return file->nbr_element == file->taille; }

file_t *initFile(int taille, int *code) {

  file_t *nouv = NULL;
  *code = -1;

  if (taille > 0) {

    if ((nouv = malloc(sizeof(file_t)))) {
      nouv->taille = taille;
      nouv->sommet = -1;
      nouv->debut = 0;
      nouv->tab = malloc(sizeof(int) * (taille + 1));
      nouv->nbr_element = 0;
      *code = 0;
    }
  }
  return nouv;
}

void freeFile(file_t *file) {
  free(file->tab);
  free(file);
}

void enfiler(file_t *file, int nouv, int *code) {
  *code = -1;
  if (!isFullFile(file)) {
    *code = 0;
    file->sommet = (file->sommet + 1) % file->taille;
    (file->nbr_element)++;
    file->tab[file->sommet] = nouv;
  }
}

int defiler(file_t *file, int *code) {
  int val = sommetFile(file, code);
  if (*code != -1) {
    *code = -1;
    if (!isEmptyFile(file)) {
      code = 0;
      file->debut = (file->debut + 1) % file->taille;
      file->nbr_element--;
    }
  }
  return val;
}

int sommetFile(file_t *file, int *code) {
  *code = isEmptyFile(file) ? -1 : 0;
  return *code == -1 ? -1 : file->tab[file->debut];
}

void prettyPrintFile(file_t *file) {
  printf(""
         "\n=====================================\n"
         "                 FILE                \n"
         "=====================================\n\n"
         "");

  for (int i = 0; i < file->nbr_element; i++) {
    printf("| indice : %d | valeur : %d |\n", i,
           file->tab[(file->debut + i) % file->taille]);
  }

  printf(""
         "\n=====================================\n"
         "               FIN FILE              \n"
         "=====================================\n\n"
         "");
}
