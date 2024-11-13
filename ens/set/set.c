//  set.c : partie implantation d'un module mutatif polymorphe pour la
//    spécification ENS du TDA Ens(T) ainsi que pour son extension optionnelle
//    ENSMIN.

#include "set.h"
#include "stdbool.h"

#ifndef nullptr 
#define nullptr NULL
#endif

/*
 *  IMPLANTATION DU STANDARD
 */

typedef struct cell{
    void *data;
    struct cell *next;
} cell;

struct set {
    cell *head;
    size_t size;
    int (*compar)(const void *, const void *);
};

// Creer le set vide . Renvoie pointer vers set en cas d'succes, 
// pointeur null sinon
set *set_empty(int (*compar)(const void *, const void *)) {
    set *new_set = malloc(sizeof(set));
    if (new_set == nullptr) {
        return nullptr;
    } 

    new_set->head = nullptr;
    new_set->size = 0;
    new_set->compar = compar;

    return new_set;
}

// Verifier si le liste est vide
bool set_is_empty(set *s) {
    return s->size == 0;
}

// Renvoie la cardinale de set
size_t set_card(set *s) {
    return s->size;
}

// Vide le set pointe par sptr, en mettant sptr a null a la fin;
void set_dispose(set **sptr) {
    if (sptr == nullptr || *sptr == nullptr) return;

    cell* current = (*sptr)->head;
    while(current != nullptr) {
        cell *next = current->next;
        free(current);
        current = next;
    }
    free(*sptr);
    *sptr = nullptr;
}

// Renvoie une des References de l'ensemble
void *set_pick(set *s) {
    if (set_is_empty(s)) return nullptr;
    return s->head->data;
}

// Chercher la reference dans l'ensemble associe a une objet egale a ref
void *set_get(set *s, const void *ref) {
    cell *current = s->head;

    while (current != nullptr) {
        if (s->compar(current->data, ref) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

// Add a set
void *set_add(set *s, const void *ref) {
    if (ref == nullptr) return nullptr;

    // Verifier si  objet deja inclus dans set
    cell *current = s->head;
    while (current) {
        if (s->compar(current->data, ref) == 0) {
            return current->data;  // Cas positive
        }
        current = current->next;
    }

    // Creer nouveau cellule et ajouter objet en tete
    cell *new_cell = malloc(sizeof(cell));
    if (new_cell == nullptr) return nullptr;

    new_cell->data = (void *)ref;
    new_cell->next = s->head;
    s->head = new_cell;
    s->size++;

    return new_cell->data; //Cas negatif - ajout de cellule
}

void *set_remove(set *s, const void *ref) {
    if (s == nullptr || ref == nullptr) return nullptr;

    struct cell *current = s->head;
    struct cell *previous = nullptr;

    while (current != nullptr) {
        if (s->compar(current->data, ref) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                s->head = current->next;
            }
            void *removed_data = current->data;
            free(current);
            s->size--;
            return removed_data;
        }
        previous = current;
        current = current->next;
    }

    return nullptr;
}



#if defined SET_EXT && defined WANT_SET_EXT

/*
 *  IMPLANTATION DE L'EXTENSION OPTIONNELLE
 */

#endif
