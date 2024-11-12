#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

struct cell {
    int value;
    struct cell *next;
};

int insert_index(struct cell **headptr, size_t idx, int val);
int delete_head(struct cell **headptr);

int main(void) {
    return EXIT_SUCCESS;
}

int insert_index(struct cell **headptr, size_t idx, int val) {
    if (*headptr == NULL || idx == 0) {
        struct cell *new_cell = malloc(sizeof(*new_cell));
        if (new_cell == NULL) {
            return -1;
        }
        new_cell->value = val;
        new_cell->next = *headptr;
        *headptr = new_cell;
        return 0;
    }
    return insert_index(&((*headptr)->next), idx-1, val);
}

int delete_head(struct cell **headptr) {
    if (*headptr == NULL) {
        return 1;
    }
    struct cell *p = *headptr;
    *headptr = p->next;
    free(p);
    return 0;
}