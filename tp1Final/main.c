#include "semaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LC_LONG 1000

/*****************************************************************************
 *                                                                           *
 *     5 actions proposées par le menu :                                     *
 *      - ajouterAction : demande puis envoie les données à traiter          *
 *      - retirerAction : depuis puis encvoie les données à traiter          *
 *      - importerCalendrier : importe un calendrier depuis un               *
 *                             fichier existant                              *
 *      - exporterCalendrier : exporte le calendrier actuel                  *
 *      - rechercherMotif : crée une liste contiguë des actions              *
 *                          contenant un certain motif                       *
 *                                                                           *
 *****************************************************************************/

void ajouterAction(listWeek_t *listWeek) {
  char year[5], numWeek[3], day, hour[3], name[MAX_NAME];
  printf("Quel est le nom de votre action (moins de %d caractères) ?\n",
         MAX_NAME);
  scanf("%s", name);
  printf("En quelle année se passe votre action ?\n");
  scanf("%s", year);
  printf("Quel numéro de semaine ?\n");
  scanf("%s%*c", numWeek);
  printf("Quel jour a lieu votre action ? (1 à 7)\n");
  scanf("%c", &day);
  printf("Quel est l'heure de début de votre action ?\n");
  scanf("%s%*c", hour);
  printf("%s, %s, %s, %c, %s\n", year, numWeek, name, day, hour);
  insertActionInsideWeek(listWeek, year, numWeek, day, hour, name);
}

void retirerAction(listWeek_t *listWeek) {
  char year[5], numWeek[3], day, hour[3];
  int code;
  printf("En quelle année se passe l'action à supprimer ?\n");
  scanf("%s", year);
  printf("Quel est son numéro de semaine ?\n");
  scanf("%s%*c", numWeek);
  printf("Quel jour à lieu votre action ?\n");
  scanf("%c", &day);
  printf("Quel est l'heure de début de votre action ?\n");
  scanf("%s%*c", hour);
  code = supprActionInsideWeek(listWeek, year, numWeek, day, hour);
  if (code == -1)
    printf("NO ACTION WITH THIS DAY OR HOUR FOUND\n");
  else if (code == -2)
    printf("NO WEEK WITH THIS YEAR OR WEEK NUMBER FOUND\n");
}

int importerCalendrier(char *fichier, listWeek_t *listWeek) {
  int etat = 1; // vérifie si tout s'est bien passé
  FILE *f = fopen(fichier, "r");

  /*
  |   Si le fichier f a pu être ouvert sans erreur,
  |   on lit dans le fichier f la première ligne pour
  |   l'écrire dans un buffer.
  |   On lit dans le buffer les 4 premiers caractères
  |   pour mettre l'année dans le tableau "annee". On fait
  |   de même avec la semaine, le jour, l'heure et le nom
  |   de l'action, auquel on rajoute des espaces pour atteindre
  |   10 caractères si besoin.
  |   On transmet tous ces paramètres à insertActionInsideWeek
  |   avant de traîter la ligne suivante du tableau, le cas
  |   échéant.
  */

  if (f) {
    char annee[5], semaine[3], jour, heure[3], action[MAX_NAME], buffer[50];
    while (fgets(buffer, 50, f)) {

      if (buffer[strlen(buffer) - 1] == '\n' ||
          buffer[strlen(buffer) - 1] == '\0')
        buffer[strlen(buffer) - 1] = ' ';

      strncpy(annee, buffer, 4);
      strncpy(semaine, buffer + 4, 2);
      jour = buffer[6];
      strncpy(heure, buffer + 7, 2);
      char buffer_action[2*MAX_NAME];
      strncpy(buffer_action, buffer + 9, MAX_NAME);
      strncat(buffer_action, "           ", MAX_NAME);
      strncpy(action, buffer_action, MAX_NAME);

      annee[4] = '\0';
      semaine[2] = '\0';
      heure[2] = '\0';

      insertActionInsideWeek(listWeek, annee, semaine, jour, heure, action);
    }
    fclose(f);
  } else
    etat = 0;

  return etat;
}

int exporterCalendrier(char *fichier, listWeek_t listWeek) {
  int etat = 1; // vérifie si tout s'est bien passé

  FILE *f = fopen(fichier, "w");
  char buffer[255];

  week_t *currWeek = listWeek;
  action_t *currAct;

  /*
  |   Si le fichier f a pu être ouvert sans erreur,
  |   on parcourt les actions au sein des semaines.
  |   On concatène l'année, le numéro de la semaine,
  |   le jour de la semaine, l'heure et le nom de l'action
  |   dans un buffer.
  |   On écrit ce buffer dans le fichier ouvert f.
  */

  if (f) {
    while (currWeek) {
      currAct = currWeek->listAct;
      while (currAct) {

        strncpy(buffer, currWeek->year, 5);
        strncat(buffer, currWeek->numWeek, 3);
        buffer[6] = currAct->day;
        buffer[7] = 0;
        strncat(buffer, currAct->hour, 3);
        strncat(buffer, currAct->name, MAX_NAME);
        strncat(buffer, "           ", MAX_NAME);
        buffer[19] = 0;
        printf("%s\n", buffer);
        fwrite(buffer, 1, 19, f);
        fwrite("\n", 1, 1, f);
        buffer[0] = 0;
        currAct = currAct->suiv;
      }
      currWeek = currWeek->suiv;
    }
  } else
    etat = 0;

  fclose(f);

  return etat;
}

void afficherTab(char *tabMotif[]) {

  /* Pointeur de tête : &tabMotif[0]
     Pointeur de fin  : &(tabModif[last]+6)  */

  int i, j = 0;
  int last = 0;
  for (i = 0; i < LC_LONG; i++) {
    if (tabMotif[i][0] == '2') {
      for (j = 0; j < 7; j++) {
        printf("%c", tabMotif[i][j]);
      }
      last++;
      printf("\n");
    }
  }
  printf("\nTaille du tableau : %d charactères et "
         "n° dernier élément : %d (pointeur de fin)\n",
         last * 7, last);
  printf(""
         "Adresse de début de premier élément : %p, adresse de début du dernier"
         "élément : %p, adresse de fin du dernier élément %p\n\n"
         "",
         &tabMotif[0], &tabMotif[last], (tabMotif[last] + 6));
}

void rechercherMotif(listWeek_t listWeek, char * motif, int affichage) {
  char buffer[16];

  int i = 0;
  char ** tabMotif = malloc(LC_LONG*sizeof(char*));
  for (i=0; i<LC_LONG; i++){
    tabMotif[i] = malloc(7*sizeof(char**));
  }
  
  i = 0;
  char * comp;
  week_t *currWeek = listWeek;
  action_t *currAct;

  /*
  |   On concatène l'année, le numéro de la semaine,
  |   le jour de la semaine, l'heure et le nom de l'action
  |   dans un buffer.
  |   comp permet, avec strstr, de chercher une occurrence
  |   dans un string. On cherche "motif" dans le buffer créé.
  |   Si le motif a été créé, on écrit le buffer dans la ième
  |   case du tableau et on incrémente i.
  */

  while (currWeek) {
    currAct = currWeek->listAct;
    while (currAct) {
      strncpy(buffer, currWeek->year, 5);
      strncat(buffer, currWeek->numWeek, 3);
      buffer[6] = currAct->day;
      comp = strstr(currAct->name, motif);
      if (comp)
      {
        strncpy(tabMotif[i], buffer, 7);
        i++;
      }
      currAct = currAct->suiv;
    }
    currWeek = currWeek->suiv;
  }

  if (affichage) afficherTab(tabMotif);

  for (i = 0; i < LC_LONG; i++)
  {
    free(tabMotif[i]);
  }
  free(tabMotif);
}


/*****************************************************************************
 *                                                                           *
 *                                   MAIN                                    *
 *                                                                           *
 *****************************************************************************/


int main(int argc, char *argv[]) {
  char choix = '1';
  char progMarche = '1';
  int etat = 0;
  char fichier[100];
  int fichierOk = 0;
  char nomSauvegarde[255];
  listWeek_t listWeek = initListWeek();

  if (argc > 1) {                                   // vérification si un fichier à importer a été
    strcpy(fichier, argv[1]);                       // ajouté ou non
    fichierOk = 1;
  }

  while (progMarche - '1' + 1) {                    // affichage du menu tant qu'on ne quitte pas
    printf(""                                       // le programme
           "[ Bienvenue ]\n\n"
           "Veuillez choisir une action :\n  "
           "1) Ajouter action\n  "
           "2) Retirer action\n  "
           "3) Importer calendrier\n  "
           "4) Exporter calendrier\n  "
           "5) Afficher calendrier\n  "
           "6) Rechercher motif\n  "
           "0) Quitter\n\n=> ");

    scanf("%c%*c", &choix);

    switch (choix - '1' + 1) {                      // switch en fonction du choix de l'utilisateur
    case 1:
      printf("      [ Ajouter une action ]\n\n");
      ajouterAction(&listWeek);
      printf("Action insérée avec succès.\n\n");
      break;
    case 2:
      printf("      [ Retirer une action ]\n\n");
      retirerAction(&listWeek);
      printf("Action supprimée avec succès.\n\n");
      break;
    case 3:
      printf("      [ Importer un calendrier ]\n\n");
      if (fichierOk) {
        etat = importerCalendrier(fichier, &listWeek); // vérifier argv et argc
        if (etat)
          printf("Calendrier importé avec succès.\n\n");
        else
          printf("Erreur au cours de l'importation.\n\n");
      } else {
        printf("Relancez le programme en ajoutant un fichier.\n\n");
      }
      break;
    case 4:
      printf(""
             "      [ Exporter un calendrier ]\n\n"
             "Entrer le nom du fichier :\n"
             "");
      scanf("%s", nomSauvegarde);
      etat = exporterCalendrier(nomSauvegarde, listWeek);
      if (etat)
        printf("Calendrier exporté avec succès.\n\n");
      else
        printf("Erreur au cours de l'exportation.\n\n");
      break;
    case 5:
      printf("      [ Afficher calendrier ]\n\n");
      prettyPrintListWeek(listWeek);
      printf("Calendrier affiché avec succès.\n\n");
      break;
    case 6:
      printf("      [ Rechercher motif ]\n\n");
      char motif[20];
      int resultat = 0;

      printf("Quel motif faut-il chercher ? (min 1, max 19 caractères)\n");
      scanf("%19s%*c", motif);

      do {
        printf("Afficher le résultat ? (0 : non, 1 : oui)\n");
        scanf("%d%*c", &resultat);
      } while (resultat != 0 && resultat != 1);

      rechercherMotif(listWeek, motif, resultat);

      printf("Calendrier selon le motif affiché avec succès.\n\n");
      break;
    default:
      progMarche = '0';
      break;
    }
    choix = '1';
  }
  freeListWeek(listWeek);
  return 0;
}