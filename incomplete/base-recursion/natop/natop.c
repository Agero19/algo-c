#include "natop.h"

nat sum(nat x, nat y) {
  if (is_undef(x) || is_undef(y)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (is_zero(x) || is_infty(y)) {
    return y;
  }
  return sum(pred(x), succ(y));
}
