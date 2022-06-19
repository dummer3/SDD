#include "semaine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ajouterAction(listWeek_t *listWeek) {
  char year[5], numWeek[3], day, hour[3], name[MAX_NAME];
  printf("Quel est le nom de votre action (moins de %d caractères)\n",
         MAX_NAME);
  scanf("%s", name);
  printf("En quelle année ce passe votre action\n");
  scanf("%s", year);
  printf("Quel numéro de semaine\n");
  scanf("%s%*c", numWeek);
  printf("Quel jour à lieu votre action\n");
  scanf("%c", &day);
  printf("Quel est l'heure de début de votre action)\n");
  scanf("%s%*c", hour);
  printf("%s, %s, %s, %c, %s\n", year, numWeek, name, day, hour);
  insertActionInsideWeek(listWeek, year, numWeek, day, hour, name);
}

void retirerAction(listWeek_t *listWeek) {
  char year[5], numWeek[3], day, hour[3];
  int code;
  printf("En quelle année ce passe l'action à supprimer\n");
  scanf("%s", year);
  printf("Quel est son numéro de semaine\n");
  scanf("%s%*c", numWeek);
  printf("Quel jour à lieu votre action\n");
  scanf("%c", &day);
  printf("Quel est l'heure de début de votre action)\n");
  scanf("%s%*c", hour);
  code = supprActionInsideWeek(listWeek, year, numWeek, day, hour);
  if (code == -1)
    printf("NO ACTION WITH THIS DAY OR HOUR FOUND\n");
  else if (code == -2)
    printf("NO WEEK WITH THIS YEAR OR WEEK NUMBER FOUND\n");
};

int importerCalendrier(char *fichier, listWeek_t *listWeek) {
  int etat = 1; // vérifie si tout s'est bien passé
  FILE *f = fopen(fichier, "r");

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
      strncpy(action, buffer + 9, MAX_NAME);

      annee[4] = '\0';
      semaine[2] = '\0';
      heure[2] = '\0';

      insertActionInsideWeek(listWeek, annee, semaine, jour, heure, action);
    }
    fclose(f);
  } else
    etat = 0;

  return etat;
};

int exporterCalendrier(char *fichier, listWeek_t listWeek) {
  int etat = 1; // vérifie si tout s'est bien passé

  FILE *f = fopen(fichier, "w");
  char buffer[255];

  week_t *currWeek = listWeek;
  action_t *currAct;
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
};

int main(int argc, char *argv[]) {
  char choix = '1';
  char progMarche = '1';
  int etat = 0;
  char fichier[100];
  int fichierOk = 0;
  char nomSauvegarde[255];
  listWeek_t listWeek = initListWeek();

  if (argc > 1) {
    strcpy(fichier, argv[1]);
    fichierOk = 1;
  }

  while (progMarche - '1' + 1) {
    printf(""
           "[ Bienvenue ]\n\n"
           "Veuillez choisir une action :\n  "
           "1) Ajouter action\n  "
           "2) Retirer action\n  "
           "3) Importer calendrier\n  "
           "4) Exporter calendrier\n  "
           "5) Afficher calendrier\n  "
           "0) Quitter\n\n=> ");

    scanf("%c%*c", &choix);

    switch (choix - '1' + 1) {
    case 1:
      printf("      [ Ajouter une action ]\n\n");
      ajouterAction(&listWeek);
      printf("Action insérer avec succès.\n\n");
      break;
    case 2:
      printf("      [ Retirer une action ]\n\n");
      retirerAction(&listWeek);
      printf("Action supprimer avec succès.\n\n");
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
      printf("Calendrier afficher avec succès.\n\n");
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
