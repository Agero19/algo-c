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


int add(int a, int b) {
    if (b == 0) return a; // Базовый случай
    return add(a + 1, b - 1); // Увеличиваем a и уменьшаем b
}

int subtract(int a, int b) {
    if (b == 0) return a; // Базовый случай
    return subtract(a - 1, b - 1); // Уменьшаем оба числа
}

int multiply(int a, int b) {
    if (b == 0) return 0; // Базовый случай
    if (b > 0) return a + multiply(a, b - 1); // Добавляем a b раз
    return -multiply(a, -b); // Обработка отрицательных b
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero is not allowed.\n");
        return 0; // Обработка деления на ноль
    }
    if (a < b) return 0; // Базовый случай: частное равно 0, если делимое меньше делителя
    return 1 + divide(a - b, b); // Уменьшаем делимое на делитель, увеличиваем результат
}

int remainder(int a, int b) {
    if (b == 0) {
        printf("Division by zero is not allowed.\n");
        return 0; // Обработка деления на ноль
    }
    if (a < b) return a; // Базовый случай:


