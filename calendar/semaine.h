/**
 * \file semaine.h
 * \brief Header pour la structure SDD semaine
 * \author Marie Bornet et Cliquot Théo
 * \date 15 février 2022
 *
 * Header contenant toute les fonctions de bases pour la structure semaine
 * (Init, new, find semaine / action, insert semaine / action, suppr semaine /
 *action)
 *
 **/

#ifndef __SEMAINE__
#define __SEMAINE__

#include "action.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *                                                                           *
 *                                STRUCTURES                                 *
 *                                                                           *
 *****************************************************************************/

/**
 *\struct week_t week.h
 **/

typedef struct week {
  char year[5];         // Annee de la semaine
  char numWeek[3];      // Jour de la semaine (01 à 53)
  struct week *suiv;    // Semaine suivante
  listAction_t listAct; // Actions de la semaine
} week_t;

/**
 * \def listWeek_t
 *
 * Simplification, une liste de Semaine est en réalité un pointeur vers la
 *semaine qui correspond à la tête de liste
 **/

#define listWeek_t week_t *

/*****************************************************************************
 *                                                                           *
 *                              SOUS PROCEDURES                              *
 *                                                                           *
 *****************************************************************************/

/**
 *
 * int checkYear(char year[4]);
 * \brief Vérifie si l'année est cohérent
 * \param year : l'année à vérifié
 * \return 1 si cohérent, 0 sinon
 *
 **/
int checkYear(char year[4]);

/**
 *
 * int checkNumWeek(char numWeek[2]);
 * \brief Vérifie si le numéro de semaine est cohérent
 * \param numWeek : le numéro de semaine à vérifié
 * \return 1 si cohérent, 0 sinon
 *
 **/
int checkNumWeek(char numWeek[2]);

/**
 *
 * \fn int compareWeek(week_t *week, char year[4], char numWeek[2]);
 * \brief retourne 1 si la semaine suit ou est égale à l'année et le numéro de
 *semaine donné en argument
 * \param week : semaine à comparer
 * \param  year: année de référence
 * \param numWeek : numéro de semaine de référence
 * \return 1 si week >=, 0 sinon
 *
 **/

// 1 si a <<, 0 sinon 0
int compareWeek(week_t *week, char year[4], char numWeek[2]);

/**
 *
 * \fn int equalWeek(week_t *week, char year[4], char numWeek[2]);
 * \brief retourne 1 si la semaine est égale à l'année et le numéro de semaine
 *donné en argument
 * \param week : semaine à comparer
 * \param  year: année de référence
 * \param numWeek : numéro de semaine de référence
 *\return 1 si week =, 0 sinon
 *
 **/
// 1 si a ==, 0 sinon 0
int equalWeek(week_t *week, char year[4], char numWeek[2]);

/*****************************************************************************
 *                                                                           *
 *                                PROCEDURES                                 *
 *                                                                           *
 *****************************************************************************/

/**
 * \fn listWeek_t initListWeek()
 * \brief Fonction créant une nouvelle instance d'une liste de semaine
 * \param None
 * \return void (liste de semaine vide)
 *
 **/
listWeek_t initListWeek();

/**
 *
 * \fn week_tweek_t *newWeek(char year[4], char numWeek[2])
 * \brief Alloue une semaine contenant les valeurs données en argument
 * \param year : année de la semaine que l'on veut allouer. (0000 à 9999)
 * \param numSemain : numéro de semaine de la semaine que l'on veut allouer (00
 * à 52)
 * \return La semaine remplie avec les arguments données si ils sont correctes,
 * NULL sinon
 *
 **/

week_t *newWeek(char year[4], char numWeek[2]);

/**
 *
 * \fn void freeWeek(week_t *week);
 * \brief libère la semaine
 * \param week : semaine à libérer
 * \return void
 *
 **/
// Libère l'espace alloué pour une semaine / action
void freeWeek(week_t *week);

/**
 *
 * \fn void freeListWeek(listWeek_t listWeek)
 * \brief libère la liste fournit en paramètre
 * \param listWeek : la liste à libérer
 * \return void
 *
 **/
// Libère l'espace alloué pour une listeSemaine / listAction
void freeListWeek(listWeek_t s);

// Insère une action ou une semaine dans une listAction / listSemaine sans
// perturber l'ordre

/**
 *
 * \fn week_t **findWeek(char year[4], char numWeek[2], listWeek_t *listWeek);
 * \brief recherche la semaine contenant les informations fournit en argument
 * dans listW
 * \param listWeek : La liste à regarder
 * \param year : L'année de la semaine à supprimer
 * \param numWeek : Le numéro de semaine à supprimer
 * \return Null si l'année ou le numéro de semaine n'est pas correct,
 * un pointeur vers le pointeur pointant sur notre
 * élement si il existe, sinon celui qui le suit juste après dans l'ordre de la
 * liste.
 *
 **/
week_t **findWeek(listWeek_t *listWeek, char year[4], char numWeek[2]);

/**
 *
 * \fn insertWeek(listWeek_t *listWeek, week_t *nouvWeek)
 * \brief Insère une semaine dans une liste Semaine en respectant l'ordre
 * \param nouvWeek : La nouvelle semaine à insérer
 * \param listWeek : La liste à modifier
 * \return un pointeur de pointeur vers la cellule insérer (ou celle occupant
 * déjà la place)
 *
 * Si la semaine existe déjà, on libère nouvWeek car on n'as pas besoin de
 * l'ajouter.
 *
 **/
week_t **insertWeek(listWeek_t *listWeek, week_t *nouvWeek);

/**
 *
 * \fn supprWeek(listWeek_t *listWeek, char year[4], char numWeek[2]);
 * \brief supprime la semaine ayant comme information ceux fournit en argument
 * dans la liste listWeek
 * \param listWeek : La liste à modifier
 * \param year : L'année de la semaine à supprimer
 * \param numWeek : Le numéro de semaine à supprimer
 * \return Null
 *
 * Si la semaine n'existe pas, notre fonction ne fait rien
 *
 **/

// Supprime une action / semaine dans une listeAction / Semaine
void supprWeek(listWeek_t *listWeek, char year[4], char numWeek[2]);

/**
 *
 * \fn void supprActionInsideWeek(listWeek_t *listWeek, char year[4], char
 week[2], char jour, char heure[2]);
 * \brief supprime l'action ayant les informations données en argument dans
                          listW si il existe, sinon ne fait rien.
 * \param listWeek : La liste à regarder
 * \param year : L'année de la semaine contenant l'action à supprimer
 * \param numWeek : Le numéro de semaine contenant l'action à supprimer
 * \param jour : Le jour de l'action à supprimer
 * \param heure : l'heure de l'action à supprimer

 * \return Void
 *
 * La fonction envoie un message si la semaine ou l'action n'existe pas
 *
 **/

int supprActionInsideWeek(listWeek_t *listWeek, char year[4], char week[2],
                          char jour, char heure[2]);

/**
 *
 * \fn void insertActionInsideWeek(listWeek_t *listWeek, char year[4], char
 week[2], char jour, char heure[2]);
 * \brief ajoute l'action ayant les informations données en argument dans
                          listW si la place est libre, sinon ne fait rien.
 * \param listWeek : La liste à regarder
 * \param year : L'année de la semaine contenant l'action à ajouter
 * \param numWeek : Le numéro de semaine contenant l'action à ajouter
 * \param jour : Le jour de l'action à ajouter
 * \param heure : l'heure de l'action à ajouter

 * \return code : -1 => NO ACTION FOUND, -2 => NO WEEK FOUND, 1 => OK
 *
 * La fonction envoie un message si la semaine ou l'action n'existe pas
 *
 **/
void insertActionInsideWeek(listWeek_t *listWeek, char year[4], char week[2],
                            char jour, char heure[2], char nom[10]);

/**
 *
 * \fn prettyPrintListWeek(listWeek_t listWeek)
 * \brief Affichage de la liste de semaine de façon plus lisible
 * \param listWeek : la liste à afficher
 * \return void
 *
 * EFFET DE BORD ::: Print la liste
 *
 **/

// Affichage plus propre des listes
void prettyPrintListWeek(listWeek_t listWeek);

#endif
