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

// Helper function to display the content of an lslower list
void display_list(const lslower *list, const char *name) {
    printf("List %s: ", name);
    if (lslower_fput(list, stdout) == EOF) {
        printf("*** Error displaying list %s\n", name);
    }
    printf("\n");
}

int main() {
    fputs(
        "--- Tests on lslower module\n"
        "--- Type ctrl-d or enter 'q' or 'Q' to exit\n\n", stdout);

    srand(0);

    // Create two lslower lists: src and dest
    lslower *src = lslower_empty();
    lslower *dest = lslower_empty();
    ON_ERROR_GOTO(src == NULL, "Failed to create src list", error);
    ON_ERROR_GOTO(dest == NULL, "Failed to create dest list", error);

    // Fill the src list with random values
    for (int k = 0; k < NMEMB; ++k) {
        slower x;
        slower_rand(&x);  // Generate random slower element
        ON_ERROR_GOTO(lslower_insert_head(src, &x) != 0, "Failed to insert into src", error);
    }

    // Fill the dest list with random values
    for (int k = 0; k < NMEMB / 2; ++k) {  // Fewer elements in dest
        slower x;
        slower_rand(&x);  // Generate random slower element
        ON_ERROR_GOTO(lslower_insert_head(dest, &x) != 0, "Failed to insert into dest", error);
    }

    // Display both lists before moving
    display_list(src, "src");
    display_list(dest, "dest");

    // Move all elements from src to the head of dest
    ON_ERROR_GOTO(lslower_move_all_head(src, dest) != 0, "Failed to move all from src to dest", error);

    // Display both lists after moving
    puts("\n--- After moving src to the head of dest ---");
    display_list(src, "src (should be empty)");
    display_list(dest, "dest");

    // Cleanup
    lslower_dispose(&src);
    lslower_dispose(&dest);
    
    return 0;

error:
    if (src != NULL) {
        lslower_dispose(&src);
    }
    if (dest != NULL) {
        lslower_dispose(&dest);
    }
    return 1;
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
