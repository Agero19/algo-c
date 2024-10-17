#include <stdio.h>
#include <stdlib.h>
#include "lslower.h"
#include "lslower_ext.h"

//  stop : affiche sur la sortie standard une invite de commande. Lit ensuite
//    des caractères sur l'entrée standard jusqu'à détecter la fin de l'entrée
//    ou obtenir 'q', 'Q' ou '\n'. Renvoie zéro si '\n' est obtenu. Provoque
//    sinon la terminaison normale du programme en signifiant à l’environnement
//    d’exécution un succès.
int stop(void);

#define ON_ERROR_GOTO(expr, cause, label)                                      \
  if ((expr) != 0) {                                                           \
    fprintf(stderr, "*** Error line: %d test: %s cause: %s\n",                 \
      __LINE__, #expr, cause);                                                 \
    goto label;                                                                \
  }

#define NMEMB 16

int main() {
    // Define macro SLOWER_COMPAR_LENGTH before including headers
    

    // Other includes and definitions...

    // Create lists
    lslower *s = lslower_empty();
    lslower *slth = lslower_empty();
    lslower *seq = lslower_empty();
    lslower *sgth = lslower_empty();
    ON_ERROR_GOTO(s == NULL || slth == NULL || seq == NULL || sgth == NULL, "Heap overflow", dispose);

    // Insert elements into s
    for (int k = 0; k < NMEMB; ++k) {
        slower x;
        slower_rand(&x);  // Generate random slower value
        ON_ERROR_GOTO(lslower_insert_head(s, &x) != 0, "Heap overflow", dispose);
    }

    // Partition the list
    lslower_partition_pivot(s, slth, seq, sgth);

    // Output all lists
    fputs("List slth (less than pivot):\n", stdout);
    lslower_fput(slth, stdout);
    fputc('\n', stdout);

    fputs("List seq (equal to pivot):\n", stdout);
    lslower_fput(seq, stdout);
    fputc('\n', stdout);

    fputs("List sgth (greater than pivot):\n", stdout);
    lslower_fput(sgth, stdout);
    fputc('\n', stdout);

dispose:
    lslower_dispose(&s);
    lslower_dispose(&slth);
    lslower_dispose(&seq);
    lslower_dispose(&sgth);

    return 0;
}





#define PROMPT "> "

int stop(void) {
  fputs(PROMPT, stdout);
  while (1) {
    int c = getchar();
    if (c == EOF || c == 'q' || c == 'Q') {
      fputc('\n', stdout);
      exit(EXIT_SUCCESS);
    }
    if (c == '\n') {
      return 0;
    }
  }
}
