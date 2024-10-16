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
    fputs(
        "--- Tests on lslower module\n"
        "--- Type ctrl-d or enter 'q' or 'Q' to exit\n\n", stdout);

    srand(0);  // Seed random number generator for consistent results

    do {
        lslower *s = lslower_empty();
        ON_ERROR_GOTO(s == NULL, "Heap overflow", dispose);

        for (int k = 0; k < NMEMB; ++k) {
            slower x;
            slower_rand(&x);  // Generate random slower value

            ON_ERROR_GOTO(lslower_insert_head(s, &x) != 0, "Heap overflow", dispose);
        }

        // Output the entire list
        lslower_fput(s, stdout);
        fputc('\n', stdout);

    dispose:
        lslower_dispose(&s);  // Free the list and its resources
    } while (!stop());

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
