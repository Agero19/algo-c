#include <stdio.h>


// IF MODULE WAS GIVEN

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

// OR SIMPLY

int recursive_add(a, b) {
    // # Base case: if b is 0, the sum is just a
    if (b == 0) {
        return a
    }
    // # If b is positive, increment a and decrement b
    else if (b > 0) {
        return recursive_add(a + 1, b - 1)
    }
    // # If b is negative, decrement a and increment b
    else {
        return recursive_add(a - 1, b + 1)
    }
}


