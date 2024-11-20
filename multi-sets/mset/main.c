//  Affiche :
//  - sur la sortie erreur, le nombre de mots lus sur l'entrée standard, puis
//      ce même nombre mais en tant que cardinal du multi-ensemble constitué à
//      partir de ces mots ;
//  - sur la sortie standard, la liste des mots dans le multi-ensemble,
//      sans ordre précisé,
//      chaque mot étant précédé de son nombre d'occurrences.
//  Limites :
//  - les mots sont obtenus par lecture sur l'entrée des suites consécutives de
//      longueur maximale de caractères qui ne sont pas de la catégorie
//      isspace ;
//  - toute suite de tels caractères de longueur strictement supérieure à
//      WORD_LENGTH_MAX est découpée en plusieurs mots.
//  Attention ! Les points suivants sont à retravailler. Les laisser en l'état
//    est contraire aux exigences prônées :
//  - les dépassements de capacité qui peuvent survenir aux lignes 35 et 46 ne
//      sont pas traités ;
//  - l'avertissement qui figure lignes 41-42 est une nuisance si le mot lu a
//      exactement la longueur WORD_LENGTH_MAX ;
//  - l'allocation qui figure ligne 44 n'est pas testée ;
//  - les chaines allouées à la ligne 44 ne sont pas désallouées ;
//  - l'épuisement de l'entrée n'est pas testé.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mset.h"

#define nullptr NULL

#define STR(s)  #s
#define XSTR(s) STR(s)

#define WORD_LENGTH_MAX 31

int main() {
  mset *ms = mset_empty((int (*)(const void *, const void *)) strcmp);
  long int n = 0;
  char w[WORD_LENGTH_MAX + 1];
  while (scanf("%" XSTR(WORD_LENGTH_MAX) "s", w) == 1) {
    ++n;
    if (strlen(w) == WORD_LENGTH_MAX) {
      fprintf(stderr,
          "*** Warning: Word '%s...' possibly sliced\n", w);
    }
    char *t = malloc(strlen(w) + 1);
    strcpy(t, w);
    mset_add(ms, t);
  }
  fprintf(stderr,
      "--- Info: Number of words read: %ld\n", n);
  fprintf(stderr,
      "--- Info: Cardinality : %zu\n", mset_card(ms));
  while (!mset_is_empty(ms)) {
    char *t = mset_min(ms);
    printf("%zu\t%s\n", mset_count(ms, t), t);
    //while (mset_remove(ms, t) != nullptr) {
    //}

    #if 1
    while (mset_remove(ms, t) != nullptr) { }
    #else
    mset_remove_all(ms, t);
    #endif

  }
  mset_dispose(&ms);
  return EXIT_SUCCESS;
}
