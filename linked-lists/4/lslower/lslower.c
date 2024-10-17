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
    if (new_node == nullptr) {
        return 1;  
    }

    // Copy value into the new node
    new_node->value = *ptr;
    
    // Insert new node at the head
    new_node->next = s->head;
    s->head = new_node;
    return 0;  
}


void lslower_dispose(lslower **sptr) {
    if (*sptr == nullptr) {
        return;  // No list to dispose
    }

    clslower *current = (*sptr)->head;
    clslower *next_node;
    // Traverse the list and free each node
    while (current != nullptr) {
        next_node = current->next;  // Save next
        free(current);              // Free current
        current = next_node;        // Move next 
    }

    free(*sptr);   // Free controller
    *sptr = nullptr;
}


int lslower_fput(const lslower *s, FILE *stream) {
    if (s == NULL || stream == NULL) {
        return EOF;
    }

    clslower *current = s->head;
    // Traverse list , print values
    while (current != nullptr) {
        slower_fput(&current->value, stream);  
        // Assuming slower_fput is defined in slower.c
        if (current->next != nullptr) {
            fputc(' ', stream);  // space between values
        }
        current = current->next;
    }
    fputc('\n', stream);
    return 0;  
}

int lslower_head_value(const lslower *s, slower *ptr) {
    if (lslower_is_empty(s)) {
        return 1;  // List is empty
    }
    // Copy the value from the head of the list
    *ptr = s->head->value;
    return 0;  
}

int lslower_move_head_head(lslower *src, lslower *dest) {
    if (lslower_is_empty(src) || src == nullptr || dest == nullptr) {
        return 1;  // Source is empty
    }

    // Create new node ,copy the head from src
    // clslower *new_node = malloc(sizeof(*new_node));
    // if (new_node == nullptr) {
    //     return 1;  
    // }

    clslower *current = src->head;
    src->head = current->next;
    current->next = dest->head;
    dest->head = current;

    // new_node->value = src->head->value;  // Copy head value
    // new_node->next = dest->head;         // Point to head of dest
    // dest->head = new_node;                // Update head of dest

    // // Update the head of src
    // clslower *old_head = src->head;
    // src->head = src->head->next;          // Move head to next node
    // free(old_head);                       // Free old head

    return 0;  
}
