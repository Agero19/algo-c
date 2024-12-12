#include <stdio.h>

char *strchr_recursive(const char *s, int c) {
    if (*s == '\0') return NULL;         // Базовый случай: конец строки, символ не найден
    if (*s == (char)c) return (char *)s; // Базовый случай: символ найден
    return strchr_recursive(s + 1, c);  // Рекурсивный вызов, передвигаем указатель
}

char *strpbrk_recursive(const char *s1, const char *s2) {
    if (*s1 == '\0') return NULL; // Базовый случай: конец строки, символ не найден

    const char *s2_ptr = s2;
    while (*s2_ptr != '\0') {
        if (*s1 == *s2_ptr) return (char *)s1; // Символ найден
        s2_ptr++;
    }
    return strpbrk_recursive(s1 + 1, s2); // Рекурсивный вызов
}

char *strrchr_recursive(const char *s, int c) {
    if (*s == '\0') return NULL; // Базовый случай: конец строки

    char *found = strrchr_recursive(s + 1, c); // Рекурсивный вызов для оставшейся части строки

    if (found) return found;           // Если символ найден в хвосте, возвращаем указатель
    if (*s == (char)c) return (char *)s; // Проверяем текущий символ
    return NULL;                        // Символ не найден
}

size_t strspn_recursive(const char *s1, const char *s2) {
    if (*s1 == '\0') return 0; // Базовый случай: конец строки

    const char *s2_ptr = s2;
    while (*s2_ptr != '\0') {
        if (*s1 == *s2_ptr) return 1 + strspn_recursive(s1 + 1, s2); // Совпадение найдено
        s2_ptr++;
    }
    return 0; // Нет совпадений
}
