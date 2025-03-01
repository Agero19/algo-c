//  Affiche sur la sortie standard la liste des différents mots lus sur
//    l'entrée standard, chaque mot étant précédé de son nombre d'occurrences.
//  Limites :
//  - les mots sont obtenus par lecture sur l'entrée des suites consécutives
//    de longueur maximale mais majorée WORD_LENGTH_MAX de caractères qui ne
//    sont pas de la catégorie isspace ;
//  - toute suite de tels caractères de longueur strictement supérieure à
//    WORD_LENGTH_MAX se retrouve ainsi découpée en plusieurs mots.
//  Attention ! Le point suivant est à retravailler. Le laisser en l'état est
//    contraire aux exigences prônées :
//  - l'avertissement qui figure aux lignes 50-51 est une nuisance si le mot lu
//    a exactement la longueur WORD_LENGTH_MAX.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "holdall.h"

#define nullptr NULL

//  str_hashfun : l'une des fonctions de pré-hachage conseillées par Kernighan
//    et Pike pour les chaines de caractères.
static size_t str_hashfun(const char *s);

//  scptr_display : affiche sur la sortie standard *cptr, le caractère
//    tabulation, la chaine de caractères pointée par s et la fin de ligne.
//    Renvoie zéro en cas de succès, une valeur non nulle en cas d'échec.
static int scptr_display(const char *s, const char *cptr);

//  rfree : libère la zone mémoire pointée par ptr et renvoie zéro.
static int rfree(void *ptr);

#define STR(s)  #s
#define XSTR(s) STR(s)

#define WORD_LENGTH_MAX 31
#define COUNTER_LENGTH_MAX 3

static char counter_array[COUNTER_LENGTH_MAX + 1];

int main() {
  int r = EXIT_SUCCESS;
  hashtable *ht = hashtable_empty((int (*)(const void *, const void *)) strcmp,
        (size_t (*)(const void *)) str_hashfun, 1.0);
  holdall *has = holdall_empty();
  if (ht == nullptr
      || has == nullptr) {
    goto error_capacity;
  }
  char w[WORD_LENGTH_MAX + 1];
  while (scanf("%" XSTR(WORD_LENGTH_MAX) "s", w) == 1) {
    if (strlen(w) == WORD_LENGTH_MAX) {
      fprintf(stderr, "*** Warning: Word '%s...' possibly sliced\n", w);
    }
    char *cptr = hashtable_search(ht, w);
    if (cptr != nullptr) {
      if (cptr - counter_array < COUNTER_LENGTH_MAX) {
        if (hashtable_add(ht, w, cptr + 1) == nullptr) {
          goto error_capacity;
        }
      }
    } else {
      char *s = malloc(strlen(w) + 1);
      if (s == nullptr) {
        goto error_capacity;
      }
      strcpy(s, w);
      if (holdall_put(has, s) != 0) {
        free(s);
        goto error_capacity;
      }
      cptr = malloc(sizeof *cptr);
      if (cptr == nullptr) {
        goto error_capacity;
      }

      // if (holdall_put(cptr, cptr) != 0) {
      //   free(cptr);
      //   goto error_capacity;
      // }

      cptr = &counter_array[holdall_count(has) % COUNTER_LENGTH_MAX];
      *cptr = 1;

      if (hashtable_add(ht, s, cptr + 1) == nullptr) {
        goto error_capacity;
      }
    }
  }
  if (!feof(stdin)) {
    goto error_read;
  }
  fprintf(stderr, "--- Info: Number of distinct words: %zu\n",
      holdall_count(has));
#if defined HOLDALL_EXT && defined WANT_HOLDALL_EXT
  holdall_sort(has, (int (*)(const void *, const void *)) strcmp);
#endif
  if (holdall_apply_context(has,
        ht, (void *(*)(void *, void *)) hashtable_search,
        (int (*)(void *, void *)) scptr_display) != 0) {
    goto error_write;
  }
#if defined HASHTABLE_EXT && defined WANT_HASHTABLE_EXT
  hashtable_fprint_stats(ht, stderr);
#endif
  goto dispose;
error_capacity:
  fprintf(stderr, "*** Error: Not enough memory\n");
  goto error;
error_read:
  fprintf(stderr, "*** Error: A read error occurs\n");
  goto error;
error_write:
  fprintf(stderr, "*** Error: A write error occurs\n");
  goto error;
error:
  r = EXIT_FAILURE;
  goto dispose;
dispose:
  hashtable_dispose(&ht);
  if (has != nullptr) {
    holdall_apply(has, rfree);
  }
  holdall_dispose(&has);
  return r;
}

size_t str_hashfun(const char *s) {
  size_t h = 0;
  for (const unsigned char *p = (const unsigned char *) s; *p != '\0'; ++p) {
    h = 37 * h + *p;
  }
  return h;
}

int scptr_display(const char *s,const char *cptr) {
  if (cptr - counter_array > COUNTER_LENGTH_MAX) {
    fprintf(stderr, "*** Warning: string exeed maximum capacity\n");
  }
  return printf("%td\t%s\n", (cptr - counter_array), s) < 0;
}

int rfree(void *ptr) {
  free(ptr);
  return 0;
}
