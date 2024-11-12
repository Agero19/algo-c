#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

char *str_filter(const char *s, int (*filter) (int));

int main(void) {
    const char *test = "Hello";
    char *slot = str_filter(test, islower);
    return EXIT_SUCCESS;
}

char *str_filter(const char *s, int (*filter) (int)) {
    size_t n = 0;
    for (const char *p = s; *p != '\0'; ++p) {
        n += (filter(*p) != 0);
    }
    
    char *s2 = malloc(n+1);
    if (s2 == NULL) {
        return NULL;
    }

    char *p2 = s2;
    for (const char *p = s; *p != '\0'; ++p) {
        if (filter(*p)) {
            *p2 = *p;
            ++p2;
        }
    }
    *p2 = '\0';
    printf("memory allocated from %s\n", s);
    printf("memory allocated for %s\n", s2);
    return s2;
}