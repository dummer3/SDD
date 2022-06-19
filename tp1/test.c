#include "semaine.h"
#include <stdio.h>
#include <stdlib.h>

#define PRINTF(TEST)                                                           \
  do {                                                                         \
    printf("| Test ::: %s |\n", #TEST);                                        \
    TEST;                                                                      \
    printf("| Test Passé |\n\n");                                              \
  } while (0);

#define TITLE(TEXT)                                                            \
  printf(""                                                                    \
         "\n--------------------------------------------------------------\n"  \
         "%60s\n"                                                              \
         "--------------------------------------------------------------\n\n"  \
         "",                                                                   \
         TEXT)

int main() {
  action_t *jeuAction[8];
  week_t *jeuWeek[8];
  listAction_t listAct;
  listWeek_t listWeek;

  // Test si l'initialisation des listes fonctionnent
  // (Nécessaire pour les autres tests)
  TITLE("INIT");

  PRINTF(listAct = initListAction());
  PRINTF(listWeek = initListWeek());

  // Test si la création des actions fonctionnent
  // (Nécessaire pour les autres tests)
  TITLE("INIT ACTION");

  // Actions correctes utilisées pour ce qui suit
  PRINTF(jeuAction[0] = newAction('1', "08", "SDD"));
  PRINTF(jeuAction[1] = newAction('3', "14", "CSN"));
  PRINTF(jeuAction[2] = newAction('1', "07", "AUTOMATE"));
  PRINTF(jeuAction[3] = newAction('3', "07", "TDS"));
  PRINTF(jeuAction[4] = newAction('5', "14", "TDD"));
  PRINTF(jeuAction[5] = newAction('1', "08", "SDD ERROR"));

  // Actions incohérentes (= NULL)
  PRINTF(jeuAction[6] = newAction('1', "25", "OUTSIDE TIME"));
  PRINTF(jeuAction[7] = newAction('9', "10", "OUTSIDE DAY"));

  // Test si la création des semaines fonctionnent
  // (Nécessaire pour les autres tests)
  TITLE("INIT WEEK");

  // Semaines correctes utilisées pour ce qui suit
  PRINTF(jeuWeek[0] = newWeek("2019", "05"));
  PRINTF(jeuWeek[1] = newWeek("2020", "05"));
  PRINTF(jeuWeek[2] = newWeek("0666", "10"));
  PRINTF(jeuWeek[3] = newWeek("0666", "47"));
  PRINTF(jeuWeek[4] = newWeek("1999", "47"));
  PRINTF(jeuWeek[5] = newWeek("2019", "05"));

  // Semaines incohérentes (= NULL)
  PRINTF(jeuWeek[6] = newWeek("1000", "99"));
  PRINTF(jeuWeek[7] = newWeek("-999", "25"));

  // Test les comparaisons d'actions
  TITLE("TEST COMPARE ACTION");
  PRINTF(
      printf("%d\n", compareAction(jeuAction[0], '1', "08"))); // Même actions
  PRINTF(printf("%d\n",
                compareAction(jeuAction[0], '5', "18"))); // L'action précède
  PRINTF(printf("%d\n",
                compareAction(jeuAction[0], '1', "06"))); // L'action succède

  // Test les comparaisons d'actions
  TITLE("TEST EQUAL ACTION");
  PRINTF(printf("%d\n", equalAction(jeuAction[0], '1', "08"))); // Même action
  PRINTF(
      printf("%d\n", equalAction(jeuAction[0], '5', "18"))); // L'action précède
  PRINTF(
      printf("%d\n", equalAction(jeuAction[0], '1', "06"))); // L'action succède

  // Test les comparaisons de semaines
  TITLE("TEST COMPARE WEEK");
  PRINTF(printf("%d\n", compareWeek(jeuWeek[0], "2020", "05"))); // Même semaine
  PRINTF(printf("%d\n",
                compareWeek(jeuWeek[0], "2020", "10"))); // la semaine précède
  PRINTF(printf("%d\n",
                compareWeek(jeuWeek[0], "2019", "05"))); // la semaine succède

  // Test les comparaisons de semaines
  TITLE("TEST EQUAL WEEK");
  PRINTF(printf("%d\n", equalWeek(jeuWeek[0], "2020", "05"))); // Même semaine
  PRINTF(printf("%d\n",
                equalWeek(jeuWeek[0], "2020", "10"))); // la semaine précède
  PRINTF(printf("%d\n",
                equalWeek(jeuWeek[0], "2019", "05"))); // la semaine succède

  // Test l'insertion d'action
  TITLE("TEST INSERT + PRINT ACTION");
  PRINTF(insertAction(&listAct, jeuAction[0])); // Insertion dans une liste vide
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct,
                      jeuAction[1])); // Insertion dans une liste à un élément
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct, jeuAction[2])); // Insertion tête
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct, jeuAction[3])); // Insertion même jour
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct, jeuAction[4])); // Insertion même heure
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct,
                      jeuAction[5])); // Insertion déjà existante (ici tête)
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(insertAction(&listAct, jeuAction[6])); // Insertion action invalide
  PRINTF(prettyPrintListAction(listAct));

  TITLE("TEST INSERT + PRINT WEEK");
  PRINTF(insertWeek(&listWeek, jeuWeek[0])); // Insertion dans une liste vide
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(insertWeek(&listWeek,
                    jeuWeek[1])); // Insertion dans une liste à un élément
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(insertWeek(&listWeek, jeuWeek[2])); // Insertion tête
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(insertWeek(&listWeek, jeuWeek[3])); // Insertion même année
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(insertWeek(&listWeek, jeuWeek[4])); // Insertion même semaine
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(
      insertWeek(&listWeek, jeuWeek[5])); // Insertion déjà existante (ici tête)
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(insertWeek(&listWeek, jeuWeek[6])); // Insertion semaine invalide
  PRINTF(prettyPrintListWeek(listWeek));

  // Test suppression
  TITLE("TEST SUPPRESSION ACTION ET SEMAINE");

  // Suppression action existante
  PRINTF(supprAction(&listAct, "08", '1'));
  PRINTF(prettyPrintListAction(listAct));

  // Suppression action tête
  PRINTF(supprAction(&listAct, "07", '1'));
  PRINTF(prettyPrintListAction(listAct));

  // Suppression action inexistante
  PRINTF(supprAction(&listAct, "09", '1'));
  PRINTF(prettyPrintListAction(listAct));

  // Suppression action invalide
  PRINTF(supprAction(&listAct, "13", '9'));
  PRINTF(prettyPrintListAction(listAct));

  PRINTF(supprAction(&listAct, "25", '5'));
  PRINTF(prettyPrintListAction(listAct));

  // Suppression semaine existante
  PRINTF(supprWeek(&listWeek, "1999", "47"));
  PRINTF(prettyPrintListWeek(listWeek));

  // Suppression tête
  PRINTF(supprWeek(&listWeek, "0666", "10"));
  PRINTF(prettyPrintListWeek(listWeek));

  // Suppression semaine inexistante
  PRINTF(supprWeek(&listWeek, "0666", "11"));
  PRINTF(prettyPrintListWeek(listWeek));

  // Suppression semaine invalide
  PRINTF(supprWeek(&listWeek, "-005", "05"));
  PRINTF(prettyPrintListWeek(listWeek));

  PRINTF(supprWeek(&listWeek, "2000", "66"));
  PRINTF(prettyPrintListWeek(listWeek));

  TITLE("TEST SUPPRESSION ET AJOUT D'ACTION DANS DES SEMAINES");

  // Test libération de mémoire
  TITLE("FREE");
  PRINTF(freeListAction(listAct));
  PRINTF(freeListWeek(listWeek));
  return 0;
}
