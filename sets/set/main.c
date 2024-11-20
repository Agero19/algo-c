//  Affiche :
//  - sur la sortie erreur, le nombre de mots lus sur l'entrée standard puis
//      le nombre de mots lus différents ;
//  - sur la sortie standard, la liste de ces mots,
//      sans ordre précisé.
//  Limites :
//  - les mots sont obtenus par lecture sur l'entrée des suites consécutives de
//      longueur maximale de caractères qui ne sont pas de la catégorie
//      isspace ;
//  - toute suite de tels caractères de longueur strictement supérieure à
//      WORD_LENGTH_MAX est découpée en plusieurs mots.
//  Attention ! Les points suivants sont à retravailler. Les laisser en l'état
//    est contraire aux exigences prônées :
//  - les dépassements de capacité qui peuvent survenir aux lignes 33 et 44 ne
//      sont pas traités ;
//  - l'avertissement qui figure lignes 39-40 est une nuisance si le mot lu a
//      exactement la longueur WORD_LENGTH_MAX ;
//  - l'allocation qui figure ligne 42 n'est pas testée ;
//  - les chaines allouées à la ligne 42 ne sont pas désallouées ;
//  - l'épuisement de l'entrée n'est pas testé.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define STR(s)  #s
#define XSTR(s) STR(s)

#define WORD_LENGTH_MAX 31

int main() {
  set *s = set_empty((int (*)(const void *, const void *)) strcmp);
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
    set_add(s, t);
  }
  fprintf(stderr,
      "--- Info: Number of words read: %ld\n", n);
  fprintf(stderr,
      "--- Info: Number of different words read: %zu\n", set_card(s));
  while (!set_is_empty(s)) {
    char *t = set_min(s);
    printf("%s\n", t);
    set_remove(s, t);
  }
  set_dispose(&s);
  return EXIT_SUCCESS;
}
