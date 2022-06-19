/**
 * \file action.h
 * \brief Header pour la structure SDD action
 * \author Marie Bornet et Cliquot Théo
 * \date 15 février 2022
 *
 * Header contenant toutes les fonctions de base pour la structure action
 * (Init, new, find, insert, suppr ...)
 *
 **/

#ifndef __ACTION__
#define __ACTION__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *                                                                           *
 *                                STRUCTURES                                 *
 *                                                                           *
 *****************************************************************************/

#define MAX_NAME 10

/**
 *\struct action_t action.h
 **/

typedef struct action {
  char day;            // Jour de la semaine (de 1 à 7)
  char hour[3];        // Heure (de 00 à 24)
  char name[MAX_NAME]; // nom de l'action
  struct action *suiv; // action suivante
} action_t;

/**
 * \def listAction_t
 *
 * Simplification, une liste d'actions est en réalité un pointeur vers l'action
 * qui correspond à la tête de liste
 **/
#define listAction_t action_t *

/*****************************************************************************
 *                                                                           *
 *                              SOUS PROCEDURES                              *
 *                                                                           *
 *****************************************************************************/

/**
 *
 * \fn checkDay(char jour)
 * \brief Vérifie si le jour est cohérent (entre 1 et 7 inclus)
 * \param jour : le jour à vérifier
 * \return 1 si cohérent, 0 sinon
 *
 **/

int checkDay(char jour);

/**
 *
 * \fn checkHour(char heure[2])
 * \brief Vérifie si l'heure est cohérente (entre 00 et 23 inclus)
 * \param jour : l'heure à vérifier
 * \return 1 si cohérent, 0 sinon
 *
 **/

int checkHour(char heure[2]);

/**
 *
 * \fn compareAction(action_t *a, char heure[2], char jour)
 * \brief retourne 1 si l'action est plus tard ou égale à l'heure et le jour
 *donnés en argument
 * \param act : action à comparer
 * \param heure : heure de référence
 * \param jour : jour de référence
 * \return 1 si act >=, 0 sinon
 *
 **/

int compareAction(action_t *act, char jour, char heure[2]);

/**
 *
 * \fn equalAction(action_t *a, char heure[2], char jour)
 * \brief retourne 1 si l'action est égale à l'heure et le jour donné en
 *argument
 * \param act : action à comparer
 * \param heure : heure de référence
 * \param jour : jour de référence
 * \return 1 si act =, 0 sinon
 *
 **/

int equalAction(action_t *act, char jour, char heure[2]);

/*****************************************************************************
 *                                                                           *
 *                                PROCEDURES                                 *
 *                                                                           *
 *****************************************************************************/

/**
 * \fn listAction_t initListAction()
 * \brief Fonction créant une nouvelle instance d'une liste d'action
 * \param None
 * \return void (liste d'action vide)
 *
 **/

listAction_t initListAction();

/**
 *
 * \fn action_t *newAction(char jour, char heure[2],char nom[MAX_NAME])
 * \brief Alloue une action contenant les valeurs données en argument
 * \param jour : jour de l'action que l'on veut allouer (0 à 7)
 * \param heure : heure de l'action que l'on veut allouer (00 à 24)
 * \param nom : nom de l'action que l'on veut allouer (max MAX_NAME char)
 * \return L'action remplie avec les arguments donnés s'ils sont corrects,
 * NULL sinon
 *
 **/

action_t *newAction(char jour, char heure[2], char nom[MAX_NAME]);

/**
 *
 * \fn void freeAction(action_t *a);
 * \brief libère l'action (simple free)
 * \param act : action à libérer
 * \return void
 *
 **/

void freeAction(action_t *act);

/**
 *
 * \fn void freeListAction(listAction_t listAct)
 * \brief libère la liste fournie en paramètre
 * \param listAct : la liste a libérer
 * \return void
 *
 **/

void freeListAction(listAction_t listAct);

/**
 *
 * \fn action_t ** findAction(listAction_t * listAct, char heure[2], char jour)
 * \brief recherche l'adresse de l'action avec l'heure et le jour donnés en
 arguments
 * \param heure : l'heure (00 à 24),
 * \param jour : le jour (1 à 7),
 * \param listAct : la liste où il faut chercher
 * \return un pointeur de pointeur vers la cellule recherchée ou
 * la première plus grande, NUll si heure et jour ne sont pas corrects
 *
 **/

action_t **findAction(listAction_t *listAct, char heure[2], char jour);

/**
 *
 * \fn insertAction(listAction_t *listAct, action_t *nouvAction)
 * \brief insert l'action nouvAction dans la liste listAct en respectant l'ordre
 * \param nouvAction : l'action à insérer
 * \param listAct : la liste où il faut insérer
 * \return un pointeur de pointeur vers la cellule insérer (ou celle occupant
 * déjà la place)
 *
 * Si l'action existe déjà, on libère nouvAction car on n'as pas besoin de
 * l'ajouter.
 *
 **/

action_t **insertAction(listAction_t *listAct, action_t *nouvAction);

/**
 *
 * \fn suprAction(listAction_t *la, char heure[2],char jour)
 * \brief supprime l'action du jour et heure indiqués dans la liste listAct
 * \param jour : le jour de l'action à supprimer (0 à 7)
 * \param heure : l'heure de l'action à supprimer (0 à 24)
 * \param listAct : la liste d'action de laquelle il faut supprimer
 * \return void
 *
 * Si l'action n'est pas contenu dans la liste, la fonction ne fera rien dans ce
 *cas
 *
 **/

void supprAction(listAction_t *listAct, char heure[2], char jour);

/**
 *
 * \fn prettyPrintListAction(listAction_t listAct)
 * \brief Affichage de la liste d'action de façon plus lisible
 * \param listAct : la liste à afficher
 * \return void
 *
 * EFFET DE BORD ::: Print la liste
 *
 **/

void prettyPrintListAction(listAction_t listAct);
#endif
