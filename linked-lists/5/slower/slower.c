#include <ctype.h>
#include <string.h>
#include "slower.h"

//  slower, détail d'implantation : la mémorisation dans le tableau se fait à
//    rebours.

int slower_fget(slower *ptr, FILE *stream) {
  int c;
  while ((c = fgetc(stream)) != EOF && isspace(c)) {
  }
  if (c == EOF || ungetc(c, stream) == EOF) {
    return EOF;
  }
  slower s;
  size_t k = SLOWER_LENGTH;
  while (k != 0
      && (c = fgetc(stream)) != EOF
      && memchr(LOWER_SET__FULL, c, LOWER_CARD) != nullptr) {
    --k;
    s.reserved__usage[k] = (char) c;
  }
  if (k != 0) {
    return 1;
  }
  *ptr = s;
  return 0;
}

int slower_fput(const slower *ptr, FILE *stream) {
  size_t k = SLOWER_LENGTH;
  while (k != 0) {
    --k;
    if (fputc(ptr->reserved__usage[k], stream) == EOF) {
      return EOF;
    }
  }
  return 0;
}

void slower_rand(slower *ptr) {
  size_t k = SLOWER_LENGTH;
  while (k != 0) {
    --k;
    ptr->reserved__usage[k]
      = LOWER_SET__FULL[(size_t) ((double) LOWER_CARD * rand() / RAND_MAX)];
  }
}

int slower_compar(const slower *ptr1, const slower *ptr2) {
  size_t k = SLOWER_LENGTH;
  while (k != SLOWER_LENGTH - SLOWER_COMPAR_LENGTH) {
    --k;
    int d = ptr1->reserved__usage[k] - ptr2->reserved__usage[k];
    if (d != 0) {
      return d;
    }
  }
  return 0;
}
