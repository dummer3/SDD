#include "liste.h"

semaine_t *initListSemaine() {
  semaine_t *s = (listSemaine_t *)malloc(sizeof(listSemaine_t));
  if (!s) {
    printf("ERROR INIT WEEK\n");
    exit(1);
  }
  s->tete = NULL;
  return s;
}

semaine_t *newSemaine(char annee[4], char numSemaine[2]) {
  semaine_t *a = (semaine_t *)malloc(sizeof(semaine_t));
  semaine_t *s = initSemaine();
  strcpy(s->annee, annee);
  strcpy(s->numSemaine, numSemaine);
  s->suiv = NULL;
  s->listeAction = initListAction();
  return s;
}

action_t *initListAction() {
  listAction_t *a = (listAction_t *)malloc(sizeof(listAction_t));
  a->tete = NULL;
  return a;
}

action_t *newAction(char jour, char heure[2], char nom[10]) {
  action_t *a = (action_t *)malloc(sizeof(action_t));
  a->jour = jour;
  strcpy(a->heure, heure);
  strcpy(a->nom, nom);
  a->suiv = NULL;
  return a;
}

void freeSemaine(listSemaine_t s)
{
  semaine_t* curr = s->tete;
  semaine_t* tmp;
  while(curr)
    {
      freeListAction(curr->listeAction);
      tmp = curr;
      curr = curr->suiv;
      free(tmp);
    }
}

void freeListAction(listAction_t* a)
{
  semaine_t* curr = a->tete;
  semaine_t* tmp;
  while(curr)
    {
      tmp = curr;
      curr = curr->suiv;
      free(tmp);
    }
}

void insertAction(action_t* nouvAction, listeAction_t ** la)
{
  if((*la)->tete && compareAction(la,nouvAction))
    {
      action_t* curr = (*la)->tete;
      action_t* tmp;
    while(!curr->suiv && compareAction(la,nouvAction))
      {
       curr = curr->suiv;
      }
    tmp = curr->suiv;
    curr->suiv = nouvAction;
    nouvAction->suiv = tmp;
    }
  else
    {
      nouvAction->suiv = (*la)->tete;
      (*la)->tete = nouvAction;
    }
}

void insertAction(action_t* nouvAction, listeAction_t ** la)
{
  if((*la)->tete && compareAction(la,nouvAction))
    {
      action_t* curr = (*la)->tete;
      action_t* tmp;
    while(!curr->suiv && compareAction(la,nouvAction))
      {
       curr = curr->suiv;
      }
    tmp = curr->suiv;
    curr->suiv = nouvAction;
    nouvAction->suiv = tmp;
    }
  else
    {
      nouvAction->suiv = (*la)->tete;
      (*la)->tete = nouvAction;
    }
}

  int compareAction(action_t* a,action_t* b)
  {
   return a->jour > b->jour || (a->jour == b->jour && strcmp(a->heure,b->heure) > 0)    
  }
