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

#define NMEMB 12

int main() {
    fputs(
        "--- Tests on lslower module\n"
        "--- Type ctrl-d or enter 'q' or 'Q' to exit\n\n", stdout);
    srand(0);

    lslower *s = lslower_empty();  // Create a new list
    ON_ERROR_GOTO(s == NULL, "Heap overflow", dispose);  // Check for allocation failure

    do {
        for (int k = 0; k < NMEMB; ++k) {
            slower x;
            slower_rand(&x);  // Generate random slower value
            
            // Insert the value at the head of the list
            ON_ERROR_GOTO(lslower_insert_head(s, &x) != 0, "Heap overflow", dispose);
        }

        // Print the list in reverse order (since we are inserting at the head)
        lslower_fput(s, stdout);

        // Test fetching the head value
        {
            slower x;
            ON_ERROR_GOTO(lslower_head_value(s, &x) != 0, "Internal error", dispose);
            slower_fput(&x, stdout);  // Print the head value
            fputc('\n', stdout);
        }

    } while (!stop());

dispose:
    lslower_dispose(&s);  // Free the list and avoid memory leaks
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
