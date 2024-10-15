#include <stdio.h>
#include <stdlib.h>
#include "nat.h"
#include "natio.h"
#include "natop.h"

#define TEST_N(opr, x, y)                                                      \
  {                                                                            \
    printf("%s(", #opr);                                                       \
    output(stdout, x);                                                         \
    printf(", ");                                                              \
    output(stdout, y);                                                         \
    printf(") = ");                                                            \
    output(stdout, opr(x, y));                                                 \
    printf("\n");                                                              \
  }

int main() {
  nat x;
  nat y;
  while (input(stdin, &x) != EOF && input(stdin, &y) != EOF) {
    TEST_N(sum, x, y);
  }
  if (!feof(stdin) || ferror(stdout)) {
    fprintf(stderr, "An error occurred on standard input or output\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
