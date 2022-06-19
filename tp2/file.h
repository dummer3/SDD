/**
 * \file file.h
 * \brief Header pour la structure file.h.
 * \author Marie Bornet et Cliquot Théo
 * \date 18 mars 2022
 *
 * Header contenant toutes les fonctions de base pour la structure file
 * (init, new, isEmpty, isFull sommet, emfiler, defiler et free)
 *
 **/

#ifndef FILE_H
#define FILE_H

/**
 * \struct file_t file.h
 **/

typedef struct file {
  int taille;      // Taille du tableau contenant nos valeurs
  int sommet;      // La fin de queue de notre file
  int debut;       // Le début de queue de notre file
  int nbr_element; // Le nombre d'éléments contenus dans notre liste
  int *tab;        // Le tableau contentant les données;
} file_t;

/**
 *
 * \fn file_t *initFile(int taille, int* code);
 * \brief initialise une file et la renvoie si crée
 * \param int taille : taille de la liste
 * \param int *code : code de retour (0 si OK -1 sinon)
 * \return Null
 *
 * Initialise la file ainsi que c'est variables
 *
 **/

file_t *initFile(int taille, int *code);

/**
 *
 * \fn void freeFile(file_t *file)
 * \brief libère une file
 * \param file_t * file : la file à libérer
 * \return NULL
 *
 * libère d'abord la variable tab de file, puis la file
 *
 **/

void freeFile(file_t *file);

/**
 *
 * \fn void enfiler(file_t *file, int nouv, int *code);
 * \brief ajoute une variable à notre file
 * \param file_t *file : Un pointeur vers la file à modifier
 * \param int nouv : La nouvelle valeur à ajouter.
 * \param int *code : Le code de retour (0 OK, 1 sinon)
 * \return Null
 *
 * La fonction vérifie que la file n'est pas pleine.
 *
 **/

void enfiler(file_t *file, int nouv, int *code);

/**
 *
 * \fn int defiler(file_t *file, int *code);
 * \brief enlève une valeur dans la file (et la renvoie)
 * \param file_t *file : Un pointeur vers la file à modifier
 * \param int *code : Le code de retour (0 OK, 1 sinon)
 * \return int : la valeur que l'on a défilée
 *
 * La fonction vérifie que la file n'est pas vide.
 *
 **/

int defiler(file_t *file, int *code);

/**
 *
 * \fn int sommetFile(file_t *file, int *code);
 * \brief retourne la valeur en début de file
 * \param file_t *file : Un pointeur vers la file à modifier
 * \param int *code : Le code de retour (0 OK, 1 sinon)
 * \return int : la valeur en tête de file
 *
 * La fonction vérifie que la file n'est pas vide.
 *
 **/

int sommetFile(file_t *file, int *code);

/**
 *
 * \fn int isEmptyFile(file_t *file);
 * \brief Renvoie si la file est vide ou non.
 * \param file_t *file : Un pointeur vers la file à vérifier
 * \return Null
 *
 *
 *
 **/

int isEmptyFile(file_t *file);
int isFullFile(file_t *file);

void prettyPrintFile(file_t *file);

#endif
