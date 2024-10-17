#include "lslower.h"

// typedef struct clslower clslower;

// struct clslower {
//   slower value;
//   clslower *next;
// };

// struct lslower {
//   clslower *head;
// };

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

int lslower_insert_head(lslower *s, const slower *ptr) {
    // Allocate memory for the new node
    clslower *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return 1;  // Allocation failed
    }

    // Copy the slower value into the new node
    new_node->value = *ptr;
    
    // Insert the new node at the head of the list
    new_node->next = s->head;
    s->head = new_node;
    
    return 0;  // Success
}


void lslower_dispose(lslower **sptr) {
    if (*sptr == NULL) {
        return;  // No list to dispose
    }

    clslower *current = (*sptr)->head;
    clslower *next_node;

    // Traverse the list and free each node
    while (current != NULL) {
        next_node = current->next;  // Save the next node
        free(current);              // Free the current node
        current = next_node;        // Move to the next node
    }

    free(*sptr);   // Free the list controller
    *sptr = NULL;  // Set the pointer to NULL to avoid dangling pointers
}


int lslower_fput(const lslower *s, FILE *stream) {
    if (s == NULL || stream == NULL) {
        return EOF;
    }

    clslower *current = s->head;
    
    // Traverse the list and print each value
    while (current != NULL) {
        slower_fput(&current->value, stream);  // Assuming slower_fput is defined to print slower values
        if (current->next != NULL) {
            fputc(' ', stream);  // Print space between values
        }
        current = current->next;
    }
    fputc('\n', stream);  // End with a newline
    
    return 0;  // Success
}

int lslower_head_value(const lslower *s, slower *ptr) {
    if (lslower_is_empty(s)) {
        return 1;  // List is empty
    }

    // Copy the value from the head of the list
    *ptr = s->head->value;
    
    return 0;  // Success
}

int lslower_move_head_head(lslower *src, lslower *dest) {
    if (lslower_is_empty(src)) {
        return 1;  // Source list is empty
    }

    // Create a new node and copy the head value from src
    clslower *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return 1;  // Memory allocation failed
    }

    new_node->value = src->head->value;  // Copy the head value
    new_node->next = dest->head;         // Point to the current head of dest
    dest->head = new_node;                // Update the head of dest

    // Update the head of src
    clslower *old_head = src->head;
    src->head = src->head->next;          // Move head to the next node
    free(old_head);                       // Free the old head node

    return 0;  // Success
}
