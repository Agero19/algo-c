//  Affiche sur la sortie standard la liste des mots lus sur l'entrée standard
//    rangée dans l'ordre lexicographique de strcmp.
//  Limites :
//  - les mots sont obtenus par lecture sur l'entrée des suites consécutives de
//    longueur maximale mais majorée par WORD_LENGTH_MAX de caractères qui ne
//    sont pas de la catégorie isspace ;
//  - toute suite de tels caractères de longueur strictement supérieure à
//    WORD_LENGTH_MAX se retrouve ainsi découpée en plusieurs mots.
//  Attention ! Le point suivant est à retravailler. Le laisser en l'état est
//    contraire aux exigences prônées :
//  - l'avertissement qui figure lignes 32-33 est une nuisance si le mot lu a
//    exactement la longueur WORD_LENGTH_MAX.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define STR(s)  #s
#define XSTR(s) STR(s)

#define WORD_LENGTH_MAX 31

int main() {
  int r = EXIT_SUCCESS;
    stack *s = stack_empty(); 
    if (s == NULL) {
        goto error_capacity;
    }

    char w[WORD_LENGTH_MAX + 1];
    while (scanf("%" XSTR(WORD_LENGTH_MAX) "s", w) == 1) {
        if (strlen(w) == WORD_LENGTH_MAX) {
            fprintf(stderr, "*** Warning: Word '%s...' possibly sliced\n", w);
        }

        char *t = malloc(strlen(w) + 1);
        if (t == NULL) {
            goto error_capacity;
        }
        strcpy(t, w);

        
        stack *temp_stack = stack_empty(); 
        if (temp_stack == NULL) {
            free(t);
            goto error_capacity;
        }

        
        while (!stack_is_empty(s)) {
            char *top = stack_pop(s);
            if (strcmp(t, top) <= 0) {
                
                if (stack_push(s, top) == NULL) {
                    free(top);
                    stack_dispose(&temp_stack);
                    goto error_capacity;
                }
                break;
            }
            
            if (stack_push(temp_stack, top) == NULL) {
                free(top);
                stack_dispose(&temp_stack);
                goto error_capacity;
            }
        }

        
        if (stack_push(s, t) == NULL) {
            free(t);
            stack_dispose(&temp_stack);
            goto error_capacity;
        }

        
        while (!stack_is_empty(temp_stack)) {
            char *temp_top = stack_pop(temp_stack);
            if (stack_push(s, temp_top) == NULL) {
                free(temp_top);
                stack_dispose(&temp_stack);
                goto error_capacity;
            }
        }

        stack_dispose(&temp_stack);
    }

    if (!feof(stdin)) {
        goto error_read;
    }

    printf("\nSorted list of words: \n");
    while (!stack_is_empty(s)) {
        char *t = stack_pop(s);
        printf("%s\n", t);
        free(t);
    }
    goto dispose;

error_capacity:
    fprintf(stderr, "*** Error: Not enough memory\n");
    goto error;

error_read:
    fprintf(stderr, "*** Error: A read error occurs\n");
    goto error;

error:
    r = EXIT_FAILURE;
    goto dispose;

dispose:
    if (s != NULL) {
        while (!stack_is_empty(s)) {
            free(stack_pop(s));
        }
    }
    stack_dispose(&s);
    return r;

}
