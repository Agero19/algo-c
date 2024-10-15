#include "lslower.h"

typedef struct clslower clslower;

struct clslower {
  slower value;
  clslower *next;
};

struct lslower {
  clslower *head;
};

lslower *lslower_empty(void) {
  lslower *s = malloc(sizeof *s);
  if (s == nullptr) {
    return nullptr;
  }
  s->head = nullptr;
  return s;
}

bool lslower_is_empty(const lslower *s) {
  return s->head == nullptr;
}
