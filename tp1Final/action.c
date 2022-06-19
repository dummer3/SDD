/**
 * \file action.c
 * \brief Source pour la structure SDD action
 * \author Marie Bornet et Cliquot Théo
 * \date 15 février 2022
 *
 * Fichier contenant la source de toutes les fonction nécessaire pour la
 * structure action
 *
 * Les blocs de commentaires expliquant les fonctions sont dans le header pour
 * ne pas surcharger le fichier source
 **/

/**
 *
 * Lexique général :
 * day, hour, name: information que va contenir l'action.
 * act : L'action à créer/ supprimer / modifier ...
 * listAct : La liste d'action à créer/ supprimer/ modifier ...
 * nouv : Une nouvelle variable allouée
 * prec : pointeur de pointeur de l'action voulue si elle existe
 *
 **/

#include "action.h"

/*****************************************************************************
 *                                                                           *
 *                              SOUS PROCEDURES                              *
 *                                                                           *
 *****************************************************************************/

int checkDay(char day) { return (day > '0' && day < '7'); }

int checkHour(char hour[2]) {
  return strcmp(hour, "00") >= 0 && strcmp(hour, "24") <= 0;
}

int compareAction(action_t *act, char day, char hour[2]) {
  return act->day < day || (act->day == day && strcmp(act->hour, hour) < 0);
}

int equalAction(action_t *act, char day, char hour[2]) {
  return act->day == day && strcmp(act->hour, hour) == 0;
}

/*****************************************************************************
 *                                                                           *
 *                                PROCEDURES                                 *
 *                                                                           *
 *****************************************************************************/

listAction_t initListAction() { return NULL; }

action_t *newAction(char day, char hour[2], char name[MAX_NAME]) {

  action_t *nouv = NULL;

  // Si tout est correcte, on alloue l'espace mémoire nécessaire
  // Sinon on renvoie NULL;
  if (checkHour(hour) && checkDay(day)) {
    if ((nouv = (action_t *)malloc(sizeof(action_t)))) {
      nouv->day = day;
      strcpy(nouv->hour, hour);
      strncpy(nouv->name, name, MAX_NAME);
      nouv->suiv = NULL;
    } else {
      printf("ERROR ALLOC DOESN'T WORK");
      exit(-1);
    }
  } else {
    printf("INVALID HOUR OR DAY\n");
  }
  return nouv;
}

void freeAction(action_t *act) { free(act); }

void freeListAction(listAction_t listAct) {
  action_t *curr = listAct; // Un pointeur vers notre action actuelle
  action_t *tmp;            // Action temporaire (celle qu'on va supprimer)

  // On supprime la tête de liste et on avance jusqu'à arriver à la fin
  while (curr) {
    tmp = curr;
    curr = curr->suiv;
    freeAction(tmp);
  }
}

action_t **findAction(listAction_t *listAct, char hour[2], char day) {
  action_t **prec =
      NULL; // Pointeur d'un pointeur contenant l'action précédente
  if (checkHour(hour) && checkDay(day)) {
    prec = listAct;
    action_t *curr = *listAct; // Un pointeur vers notre action actuelle

    // Tant qu'on n'as pas trouvé l'action voulue et qu'on est avant
    // chronologiquement
    while (curr && compareAction(curr, day, hour)) {
      prec = &(curr->suiv);
      curr = curr->suiv;
    }
  }
  return prec;
}

action_t **insertAction(listAction_t *listAct, action_t *nouvAction) {

  action_t **prec;
  // Si notre nouvAction n'est pas correcte, pas besoin de l'ajouter
  if (nouvAction != NULL) {

    // Pointeur de pointeur d'action qui pointe vers l'action précédent celle
    // voulue si elle existe sinon voir fonction findAction
    prec = findAction(listAct, nouvAction->hour, nouvAction->day);

    // Si une action existe déjà avec ce jour et heure
    // On ne l'ajoute pas, et on le libère de la mémoire
    if ((*prec) != NULL &&
        equalAction(*prec, nouvAction->day, nouvAction->hour)) {
      printf("WE ALREADY HAVE AN ACTION AT THIS HOUR AND DAY OF THE WEEK\n");
      freeAction(nouvAction);

    }
    // Sinon on l'ajoute dans notre liste
    else {
      nouvAction->suiv = (*prec);
      *prec = nouvAction;
    }
  }
  return prec;
}

void supprAction(listAction_t *listAct, char hour[2], char day) {

  if (checkHour(hour) && checkDay(day)) {
    action_t **pprec =
        findAction(listAct, hour, day); // Comme dans insertAction

    // Si on a bien cette action dans note liste
    if (pprec != NULL && *pprec != NULL && equalAction(*pprec, day, hour)) {

      action_t *tmp = *pprec; // Action temporaire
      (*pprec) = (*pprec)->suiv;
      freeAction(tmp);
    }
  }
}

void prettyPrintListAction(listAction_t listAct) {

  action_t *curr = listAct; // Pointeur vers l'action courante
  int i = 0;                // Un simple compteur
  char act[MAX_NAME];       // Une chaîne de caractères pour stocker le nom

  printf("==========================================================\n");
  while (curr) {
    strncpy(act, curr->name, MAX_NAME);
    act[MAX_NAME] = '\0';
    printf(" ===> | %2d | day %c | hour %s | name %10s |\n", i, curr->day,
           curr->hour, act);
    i++;
    curr = curr->suiv;
  }
  printf("==========================================================\n\n");
}
