#include <stdio.h>
#include <stdlib.h>

int main() {
  int r = EXIT_SUCCESS;
  long int n = 0;
  int c;
  while ((c = getchar()) != EOF) {
    ++n;
    printf("%ld\t", n);
    while (c != EOF && c != '\n') {
      putchar(c);
      c = getchar();
    }
    putchar('\n');
  }
  if (!feof(stdin)) {
    r = EXIT_FAILURE;
  }
  return r;
}
