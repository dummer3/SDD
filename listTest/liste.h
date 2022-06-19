#ifndef LISTE_CHAINEE
#define LISTE_CHAINEE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct action {
  char jour;           // Jour de la semaine (de 1 à 7)
  char heure[2];       // Heure (de 00 à 24)
  char nom[10];        // nom de l'action
  struct action *suiv; // action suivante
} action_t;

typedef struct semaine {
  char annee[4];         // Annee de la semaine
  char numSemaine[2];    // Jour de la semaine (01 à 53)
  struct semaine *suiv;  // Semaine suivante
  action_t *listeAction; // Actions de la semaine
} semaine_t;

typedef struct listSemaine {
  semaine_t *tete;
} listSemaine_t;

typedef struct listAction {
  action_t *tete;
} listAction_t;

listSemaine_t* initListSemaine();
listAction_t* initListAction();
action_t* newAction(char jour, char heure[2], char nom[10]);
semaine_t * newSemaine(char annee[4],char numSemaine[2]);
void freeListSemaine(semaine_t** s);
void freeListAction(action_t** a);

#endif
