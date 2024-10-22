#include "lslower.h"

typedef struct clslower clslower;

struct clslower {
  slower value;
  clslower *next;
};

struct lslower {
  clslower *head;
  clslower *tail;
};
