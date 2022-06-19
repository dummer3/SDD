/**
 * \file semaine.c
 * \brief Source pour la structure SDD semaine
 * \author Marie Bornet et Cliquot Théo
 * \date 15 février 2022
 *
 * Fichier contenant la source de toutes les fonction nécessaire pour la
 * structure semaine
 *
 * Bloc de commentaires expliquant les fonctions sont dans le header pour ne pas
 * surcharger le fichier source
 **/

#include "semaine.h"

/*****************************************************************************
 *                                                                           *
 *                              SOUS PROCEDURES                              *
 *                                                                           *
 *****************************************************************************/

int checkYear(char year[4]) {
  return strcmp(year, "0000") >= 0 && strcmp(year, "9999") <= 0;
}

int checkNumWeek(char numWeek[2]) {
  return strcmp(numWeek, "00") >= 0 && strcmp(numWeek, "52") <= 0;
}

int compareWeek(week_t *week, char year[4], char numWeek[2]) {
  return strcmp(week->year, year) < 0 || (strcmp(week->year, year) == 0 &&
                                          (strcmp(week->numWeek, numWeek) < 0));
}

int equalWeek(week_t *week, char year[4], char numWeek[2]) {
  return strcmp(week->year, year) == 0 && strcmp(week->numWeek, numWeek) == 0;
}

/*****************************************************************************
 *                                                                           *
 *                                PROCEDURES                                 *
 *                                                                           *
 *****************************************************************************/

listWeek_t initListWeek() { return NULL; }

week_t *newWeek(char year[4], char numWeek[2]) {
  week_t *nouv = NULL; // La nouvelle semaine alloué (null si incorrect)

  // Si nos arguments sont cohérents
  if (checkYear(year) && checkNumWeek(numWeek)) {

    // Si l'allocation c'est bien passé
    if ((nouv = (week_t *)malloc(sizeof(week_t)))) {
      strcpy(nouv->year, year);
      strcpy(nouv->numWeek, numWeek);
      nouv->suiv = NULL;
      nouv->listAct = initListAction();
    } else {
      printf("ERROR ALLOC DOESN'T WORK");
      exit(-1);
    }
  } else {
    printf("INVALID YEAR OR WEEK\n");
  }

  return nouv;
}

void freeWeek(week_t *week) {
  freeListAction(week->listAct); // On libère en premier la liste d'action
  free(week);                    // Puis la semaine en elle même
}

void freeListWeek(listWeek_t week) {
  week_t *curr = week; // Un pointeur vers la semaine actuelle
  week_t *tmp;         // Un pointeur de semaine temporaire
  while (curr) {
    tmp = curr;
    curr = curr->suiv;
    freeWeek(tmp);
  }
}

week_t **findWeek(listWeek_t *listWeek, char year[4], char numWeek[2]) {
  week_t **prec = NULL; // Un pointeur de pointeur de semaine pointant vers la
                        // semaine précédent celle recherche si elle existe
                        // (sinon : voir bloc de commentaires dans le header)

  // Si nos argument sont correctes
  if (checkYear(year) && checkNumWeek(numWeek)) {
    week_t *curr = *listWeek; // pointeur vers la semaine actuelle
    prec = listWeek;

    // Tant qu'on à pas trouvé la bonne semaine ou une plus grande.
    while (curr && compareWeek(curr, year, numWeek)) {
      prec = &(curr->suiv);
      curr = curr->suiv;
    }
  }
  return prec;
}

week_t **insertWeek(listWeek_t *listWeek, week_t *nouvWeek) {
  week_t **prec; // Comme dans findWeek

  if (nouvWeek != NULL) {
    prec = findWeek(listWeek, nouvWeek->year, nouvWeek->numWeek);

    // Si il existe déjà une liste dans ce créneau.
    if ((*prec) != NULL &&
        equalWeek((*prec), nouvWeek->year, nouvWeek->numWeek)) {

      printf("THIS WEEK ALREADY EXIST, NO NEED TO ADD IT\n");

      // On libère celle en trop.
      freeWeek(nouvWeek);

    }

    // Sinon on l'ajoute
    else {
      nouvWeek->suiv = (*prec);
      *prec = nouvWeek;
    }
  }
  return prec;
}

void supprWeek(listWeek_t *listWeek, char year[4], char week[2]) {
  week_t **pprec = findWeek(listWeek, year, week); // Comme dans findWeek

  // Si la semaine correspond bien à celle voulue
  if (pprec != NULL && *pprec != NULL && equalWeek(*pprec, year, week)) {
    // On la supprime
    week_t *tmp = *pprec; // pointeur de semaine temporaire
    (*pprec) = (*pprec)->suiv;
    freeWeek(tmp);
  }
}

int supprActionInsideWeek(listWeek_t *listWeek, char year[4], char week[2],
                          char day, char hour[2]) {
  // On cherche la semaine de l'action à supprimer
  int code = 1;
  week_t **precWeek = findWeek(listWeek, year, week);

  // Si elle existe
  if (*precWeek != NULL && equalWeek(*precWeek, year, week)) {

    // On cherche l'action dans cette semaine
    action_t **curr =
        findAction((&(*findWeek(listWeek, year, week))->listAct), hour, day);

    // Si elle existe on la supprime
    if (curr != NULL && equalAction(*curr, day, hour)) {
      supprAction(curr, hour, day);
      if ((*precWeek)->listAct == NULL) {
        supprWeek(precWeek, year, week);
      }
    } else
      code = -1;
  } else
    code = -2;

  return code;
}

void insertActionInsideWeek(listWeek_t *listWeek, char year[4], char numWeek[2],
                            char day, char hour[2], char name[10]) {
  // Si notre semaine et action sont cohérentes
  if (checkNumWeek(numWeek) && checkYear(year) && checkDay(day) &&
      checkHour(hour)) {
    // On cherche/insère si besoin la semaine
    // Pas besoin de vérifier si week NULL, en effet on l'a déjà vérifié avec la
    // condition au dessus
    week_t **week = insertWeek(listWeek, newWeek(year, numWeek));
    // On insère l'action
    insertAction(&(*week)->listAct, newAction(day, hour, name));
  }
}

void prettyPrintListWeek(listWeek_t listWeek) {
  week_t *curr = listWeek; // Pointeur sur la semaine courante
  int i = 0;               // Simple compteur

  printf("==========================================================\n");
  while (curr) {
    printf("| %d | week %s | year %s |\n", i, curr->numWeek, curr->year);
    if (curr->listAct) {
      printf("Action :::\n");
      prettyPrintListAction(curr->listAct);
      printf("\n\n");
    }
    i++;
    curr = curr->suiv;
  }
  printf("==========================================================\n\n");
}
