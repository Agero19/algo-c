#include "lslower.h"
#include "lslower_ext.h"

int lslower_move_all_head(lslower *src, lslower *dest) {
    if (src == dest) {
        return 1;  // Error: src and dest are not same
    }
    if (lslower_is_empty(src)) {
        return 0;  
    }
    // Find tail of list
    clslower *src_tail = src->head; 
    while (src_tail->next != nullptr) {
        src_tail = src_tail->next;
    }
    // Attach src to head of dest
    src_tail->next = dest->head; 
    dest->head = src->head;  // Move entire list from src to dest
    src->head = nullptr;
    return 0;
}

void lslower_partition_pivot(lslower *s, lslower *slth, lslower *seq, lslower *sgth) {
    if (lslower_is_empty(s)) {
        return;  // Nothing partition if empty
    }
    // Get pivot from head of s
    slower pivot = s->head->value;

    clslower *current = s->head;
    clslower *next_node;
    // Loop over s partitioning to slth, seq, sgth
    while (current != nullptr) {
        next_node = current->next;  // Save next
        // Compare current to pivot
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
    // Clear original s
    s->head = nullptr;
}
