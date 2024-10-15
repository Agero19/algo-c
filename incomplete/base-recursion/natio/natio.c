#include <ctype.h>
#include <errno.h>
#include "natio.h"

#define CHRZERO '0'
#define CHRSUCC 's'
#define CHRPRED 'p'

#define STRINFTY  "INFTY"
#define STRUNDEF  "UNDEF"

//  input_leadingspaces : lecture sur le flot contrôlé par l'objet pointé par
//    stream d'une suite éventuellement vide de caractères d'espacement. La
//    lecture prend fin dès qu'une erreur survient ou qu'un caractère qui
//    n'appartient pas à la catégorie des caractères d'espacement est rencontré.
//    La fonction renvoie EOF dans le premier cas, la valeur renvoyée par la
//    réinjection du dernier caractère lu dans le second cas.
static int input_leadingspaces(FILE *stream);

//  input_body : même spécification que input mais en supposant que les
//    éventuels caractères d'espacement initiaux ont été lus.
static int input_body(FILE *stream, nat *ptr);

int input(FILE *stream, nat *ptr) {
  *ptr = undef();
  if (input_leadingspaces(stream) == EOF) {
    return EOF;
  }
  return input_body(stream, ptr);
}

int input_leadingspaces(FILE *stream) {
  int c = fgetc(stream);
  if (c == EOF) {
    return EOF;
  }
  if (!isspace(c)) {
    return ungetc(c, stream);
  }
  return input_leadingspaces(stream);
}

int input_body(FILE *stream, nat *ptr) {
  int c = fgetc(stream);
  if (c == EOF) {
    return 0;
  }
  if (c == CHRZERO) {
    *ptr = zero();
    return 1;
  }
  if (!(c == CHRSUCC || c == CHRPRED)
      || input_body(stream, ptr) == 0) {
    return 0;
  }
  if (c == CHRSUCC) {
    *ptr = succ(*ptr);
  } else {
    if (is_zero(*ptr)) {
      *ptr = undef();
      return 0;
    }
    *ptr = pred(*ptr);
  }
  return 1;
}

//  output_body : même spécification que output mais en supposant que x ne
//    représente pas une valeur non définie.
static int output_body(FILE *stream, nat x);

int output(FILE *stream, nat x) {
  if (is_undef(x)) {
    return fputs(STRUNDEF, stream) == EOF ? EOF : 0;
  }
  if (is_infty(x)) {
    return fputs(STRINFTY, stream) == EOF ? EOF : 1;
  }
  return output_body(stream, x);
}

int output_body(FILE *stream, nat x) {
  if (is_zero(x)) {
    return fputc(CHRZERO, stream) == EOF ? EOF : 1;
  }
  if (fputc(CHRSUCC, stream) == EOF) {
    return EOF;
  }
  return output_body(stream, pred(x));
}
