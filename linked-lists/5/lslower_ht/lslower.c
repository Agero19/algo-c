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

lslower *lslower_empty(void) {
    lslower *list = (lslower *)malloc(sizeof(lslower));
    if (!list) {
        return NULL;  // Allocation failure
    }
    list->head = NULL;
    list->tail = NULL;  // Initialize tail as well
    return list;
}

bool lslower_is_empty(const lslower *s) {
    return s->head == NULL;
}

int lslower_insert_head(lslower *s, const slower *ptr) {
    clslower *new_node = (clslower *)malloc(sizeof(clslower));
    if (!new_node) {
        return -1;  // Allocation failure
    }
    new_node->value = *ptr;
    new_node->next = s->head;

    if (lslower_is_empty(s)) {
        s->tail = new_node;  // If the list was empty, tail must also point to the new node
    }
    s->head = new_node;
    return 0;
}

int lslower_insert_tail(lslower *s, const slower *ptr) {
    clslower *new_node = (clslower *)malloc(sizeof(clslower));
    if (!new_node) {
        return -1;  // Allocation failure
    }
    new_node->value = *ptr;
    new_node->next = NULL;

    if (lslower_is_empty(s)) {
        s->head = new_node;  // If the list was empty, head must point to the new node
    } else {
        s->tail->next = new_node;  // Link the current tail to the new node
    }
    s->tail = new_node;  // Update the tail pointer
    return 0;
}

size_t lslower_length(const lslower *s) {
    size_t length = 0;
    clslower *current = s->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int lslower_fput(const lslower *s, FILE *stream) {
    clslower *current = s->head;
    int first = 1;  // To avoid printing a space before the first element

    while (current != NULL) {
        if (!first) {
            fputc(' ', stream);  // Add a space between elements
        }
        first = 0;
        if (slower_fput(&current->value, stream) == EOF) {
            return EOF;
        }
        current = current->next;
    }
    fputc('\n', stream);  // End with a newline
    return 0;  // Success
}

void lslower_dispose(lslower **sptr) {
    if (!sptr || !*sptr) {
        return;  // No operation if sptr is null or *sptr is null
    }
    clslower *current = (*sptr)->head;
    while (current != NULL) {
        clslower *next = current->next;
        free(current);
        current = next;
    }
    free(*sptr);  // Free the list itself
    *sptr = NULL;  // Set the pointer to null
}

int lslower_head_value(const lslower *s, slower *ptr) {
    if (lslower_is_empty(s)) {
        return -1;  // Error, the list is empty
    }
    *ptr = s->head->value;
    return 0;  // Success
}

int lslower_tail_value(const lslower *s, slower *ptr) {
    if (lslower_is_empty(s)) {
        return -1;  // Error, the list is empty
    }
    *ptr = s->tail->value;
    return 0;  // Success
}



int lslower_move_all_head(lslower *src, lslower *dest) {
    if (src == dest) {
        return 1;  // Error: src and dest must not be the same
    }

    if (lslower_is_empty(src)) {
        return 0;  // No elements to move
    }

    // Attach src's list to the head of dest
    clslower *src_tail = src->head;
    while (src_tail->next != NULL) {  // NULL is used in C
        src_tail = src_tail->next;
    }
    
    // Move the entire list from src to the head of dest
    src_tail->next = dest->head;  // Connect the tail of src to the head of dest
    dest->head = src->head;  // Move the head of src to the head of dest
    src->head = NULL;  // src is now empty

    return 0;  // Success
}
