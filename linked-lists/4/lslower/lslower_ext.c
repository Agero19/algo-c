#include "lslower.h"
#include "lslower_ext.h"

int lslower_move_all_head(lslower *src, lslower *dest) {
    if (src == dest) {
        return 1;  // Error: src and dest cannot be the same
    }

    if (lslower_is_empty(src)) {
        return 0;  // Source is empty, nothing to move
    }

    // Find the tail of the src list
    clslower *src_tail = src->head;  // Correct type: clslower *
    while (src_tail->next != NULL) {
        src_tail = src_tail->next;
    }

    // Attach src list to the head of dest list
    src_tail->next = dest->head;  // dest->head is also of type clslower *
    dest->head = src->head;       // Move entire list from src to dest

    // Clear the src list
    src->head = NULL;

    return 0;  // Success
}

void lslower_partition_pivot(lslower *s, lslower *slth, lslower *seq, lslower *sgth) {
    if (lslower_is_empty(s)) {
        return;  // Nothing to partition if the list is empty
    }

    // Get the pivot value from the head of the original list
    slower pivot = s->head->value;  // Directly access the pivot value

    // Iterate through the list s, partitioning the elements into slth, seq, and sgth
    clslower *current = s->head;
    clslower *next_node;

    while (current != NULL) {
        next_node = current->next;  // Save the next node

        // Compare current value with pivot
        int cmp = slower_compar(&current->value, &pivot);

        if (cmp < 0) {
            // Move to slth (less than pivot)
            current->next = slth->head;
            slth->head = current;
        } else if (cmp == 0) {
            // Move to seq (equal to pivot)
            current->next = seq->head;
            seq->head = current;
        } else {
            // Move to sgth (greater than pivot)
            current->next = sgth->head;
            sgth->head = current;
        }

        current = next_node;  // Move to the next node
    }

    // Clear the original list s
    s->head = NULL;
}
