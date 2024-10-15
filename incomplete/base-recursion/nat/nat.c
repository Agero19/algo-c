#include "nat.h"

#define LOW   1
#define HIGH  2

#if !defined NAT_IMPLEMENTATION
#define NAT_IMPLEMENTATION LOW
#endif
#if !(NAT_IMPLEMENTATION == LOW || NAT_IMPLEMENTATION == HIGH)
#error Illegal value of NAT_IMPLEMENTATION.
#endif

#define ABORT_IF(expr, func)                                                   \
  if (expr) {                                                                  \
    fprintf(stderr,                                                            \
      "*** nat: fatal error: illegal '%s' operation\n",                        \
      func);                                                                   \
    abort();                                                                   \
  }

//------------------------------------------------------------------------------
#if NAT_IMPLEMENTATION == LOW

#define CAPACITY 36

#if CAPACITY < 4
#error Internal error.
//  Au moins ZERO0, ZERO1, INFTY0 et INFTY1 modulo CAPACITY doivent pouvoir être
//    des indices différents du tableau natscale.
#endif

#define SEED  201710

const char natscale[CAPACITY] = {
  0,
};

#define INCR  (CAPACITY % 4 == 2 ? CAPACITY - 1 : CAPACITY / 2 + 1)
#define DECR  (CAPACITY - INCR)

#define ZERO0   SEED
#define ZERO1   (ZERO0 + INCR)
#define ONE     (ZERO1 + INCR)
#define INFTY1  (ZERO0 + DECR)
#define INFTY0  (INFTY1 + DECR)
#define MAX     (INFTY0 + DECR)

#define NAT(k)  natscale + (k) % CAPACITY

#define NAT_UNDEF0  nullptr
#define NAT_UNDEF1  natscale + (CAPACITY)

nat zero(void) {
  return rand() % 2 == 0 ? NAT(ZERO0) : NAT(ZERO1);
}

bool is_zero(nat x) {
  return x == NAT(ZERO0) || x == NAT(ZERO1);
}

nat infty(void) {
  return rand() % 2 == 0 ? NAT(INFTY0) : NAT(INFTY1);
}

bool is_infty(nat x) {
  return x == NAT(INFTY0) || x == NAT(INFTY1);
}

nat undef(void) {
  return rand() % 2 == 0 ? NAT_UNDEF0 : NAT_UNDEF1;
}

bool is_undef(nat x) {
  return x == NAT_UNDEF0 || x == NAT_UNDEF1;
}

nat succ(nat x) {
  ABORT_IF(is_undef(x), __func__);
  if (is_infty(x) || x == NAT(MAX)) {
    return infty();
  }
  if (is_zero(x)) {
    return NAT(ONE);
  }
  return NAT((const char *) x - natscale + INCR);
}

nat pred(nat x) {
  ABORT_IF(is_zero(x) || is_undef(x), __func__);
  if (is_infty(x)) {
    return infty();
  }
  if (x == NAT(ONE)) {
    return zero();
  }
  return NAT((const char *) x - natscale + DECR);
}

//------------------------------------------------------------------------------
#else

typedef struct natitem natitem;

struct natitem {
  natitem *prev;
  natitem *next;
};

static natitem natbase;

static natitem *natmax = &natbase;

#define ZERO  (&natbase)
#define INFTY ((char *) &natbase + 1)
#define UNDEF nullptr

nat zero(void) {
  return ZERO;
}

bool is_zero(nat x) {
  return x == ZERO;
}

nat infty(void) {
  return INFTY;
}

bool is_infty(nat x) {
  return x == INFTY;
}

nat undef(void) {
  return UNDEF;
}

bool is_undef(nat x) {
  return x == UNDEF;
}

nat succ(nat x) {
  ABORT_IF(is_undef(x), __func__);
  if (is_infty(x)) {
    return infty();
  }
  if (x != natmax) {
    return ((natitem *) x)->next;
  }
  natitem *p = malloc(sizeof *p);
  if (p == nullptr) {
    return infty();
  }
  p->prev = natmax;
  natmax->next = p;
  natmax = p;
  return p;
}

nat pred(nat x) {
  ABORT_IF(is_zero(x) || is_undef(x), __func__);
  if (is_infty(x)) {
    return infty();
  }
  return ((natitem *) x)->prev;
}

//------------------------------------------------------------------------------
#endif
