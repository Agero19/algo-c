#include <stdio.h>
#include <stdlib.h>
#include "nat.h"
#include "natio.h"

int main() {
  nat x;
  while (input(stdin, &x) != EOF) {
    output(stdout, x);
    printf("\n");
  }
  if (!feof(stdin) || ferror(stdout)) {
    fprintf(stderr, "An error occurred on standard input or output\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
