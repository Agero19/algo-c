#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h" 

int main() {

#if 0

    char ucharAddr[UCHAR_MAX + 1];  
    int r = EXIT_SUCCESS;
    long int n = 0;
    int c;

    stack *char_stack = stack_empty(); // Creer le stack vide 
    if (char_stack == NULL) {
        fprintf(stderr, "Failed to allocate memory for the stack.\n");
        return EXIT_FAILURE;
    }

    int is_new_line = 1; 

    while ((c = getchar()) != EOF) {
        // Si flag vaut 1 on print numero 
        if (is_new_line) {

            ++n;
            printf("%ld\t", n);
            is_new_line = 0;
        }

        if (c == '\n') {
            // Si on rencontre \n commencer a depiler le stack en reverse
            while (!stack_is_empty(char_stack)) {
                const void *encoded_char = stack_pop(char_stack);
                putchar((int)((char *)encoded_char - ucharAddr));
            }

            putchar('\n'); 
            is_new_line = 1; 

        } else {
            // Sinon ajouter le character en haut de stack
            if (stack_push(char_stack, (c + ucharAddr)) == NULL) {
                fprintf(stderr, "Failed to push character onto the stack.\n");
                r = EXIT_FAILURE;
                break;
            }
        }
    }

    if (!stack_is_empty(char_stack)) {

        while (!stack_is_empty(char_stack)) {
            const void *encoded_char = stack_pop(char_stack);
            putchar((int)((char *)encoded_char - ucharAddr));
        }

        putchar('\n'); 
    }

    stack_dispose(&char_stack); 

    if (!feof(stdin)) {
        r = EXIT_FAILURE;
    }

    return r;

#else
  char ucharAddr[UCHAR_MAX + 1];  
  int r = EXIT_SUCCESS;
  long int n = 0;
  int c;

  stack *char_stack = stack_empty(); // Creer le stack vide 
  if (char_stack == NULL) {
    fprintf(stderr, "Failed to allocate memory for the stack.\n");
    return EXIT_FAILURE;
  }

  int is_new_line = 1; 

  while ((c = getchar()) != EOF) {
        // Si flag vaut 1 on print numero 
    if (is_new_line) {

      ++n;
      printf("%ld\t", n);
      is_new_line = 0;
    }

    if (c == '\n') {
      // Si on rencontre \n commencer a depiler le stack en reverse
      while (!stack_is_empty(char_stack)) {
          const void *encoded_char = stack_pop(char_stack);
          putchar((int)((char *)encoded_char - ucharAddr));
      }

      putchar('\n'); 
      is_new_line = 1; 

    } else {
            // Sinon ajouter le character en haut de stack
      if (stack_push(char_stack, (c + ucharAddr)) == NULL) {
        fprintf(stderr, "Failed to push character onto the stack.\n");
        r = EXIT_FAILURE;
        break;
      }
    }
}

    if (!stack_is_empty(char_stack)) {

        while (!stack_is_empty(char_stack)) {
            const void *encoded_char = stack_pop(char_stack);
            putchar((int)((char *)encoded_char - ucharAddr));
        }

        putchar('\n'); 
    }

    stack_dispose(&char_stack); 

    if (!feof(stdin)) {
        r = EXIT_FAILURE;
    }

    return r;


#endif
}
