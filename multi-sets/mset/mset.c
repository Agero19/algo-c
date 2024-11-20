//  mset.c : partie implantation d'un module mutatif polymorphe pour la
//    spécification MENS du TDA MEns(T) ainsi que pour son extension optionnelle
//    MENSMIN.

#include "mset.h"

#include "mset.h"
#include <stdlib.h>

#define nullptr NULL

typedef struct cell {
    const void *ref;
    size_t multiplicity;
    struct cell *next;
} cell;

struct mset {
    cell *head;
    int (*compar)(const void *, const void *);
    size_t card;
};

mset *mset_empty(int (*compar)(const void *, const void *)) {
    mset *p = (mset *)malloc(sizeof(mset));
    if (p == nullptr) return nullptr;
    p->head = nullptr;
    p->compar = compar;
    p->card = 0;
    return p;
}


void mset_dispose(mset **msptr) {
    if (msptr != nullptr && *msptr != nullptr) {
        cell *c = (*msptr)->head;
        while (c != nullptr) {
            cell *tmp = c;
            c = c->next;
            free(tmp);
        }
        free(*msptr);
        *msptr = nullptr;
    }
}

size_t mset_card(mset *ms) {
    return ms->card;
}

void *mset_add(mset *ms, const void *ref) {
    if (ref == nullptr) return nullptr;

    cell *c = ms->head;
    while (c != nullptr) {
        if (ms->compar(c->ref, ref) == 0) {
            c->multiplicity++;
            return (void *)c->ref;
        }
        c = c->next;
    }

    cell *p = (cell *)malloc(sizeof(cell));
    if (p == nullptr) return nullptr;
    p->ref = (void *)ref;
    p->multiplicity = 1;
    p->next = ms->head;
    ms->head = p;
    ms->card++;
    return (void *)p->ref;
}

bool mset_is_empty(mset *ms) {
    return ms->head == nullptr;
}

void *mset_pick(mset *ms) {
    if (mset_is_empty(ms)) return nullptr;
    return (void *)ms->head->ref;
}

size_t mset_count(mset *ms, const void *ref) {
    size_t count = 0;
    cell *c = ms->head;
    while (c != nullptr) {
        if (ms->compar(c->ref, ref) == 0) {
            count += c->multiplicity;
        }
        c = c->next;
    }
    return count;
}

void *mset_remove(mset *ms, const void *ref) {
    cell *c = ms->head;
    cell *prev = nullptr;

    while (c != nullptr) {
        if (ms->compar(c->ref, ref) == 0) {
            if (c->multiplicity > 1) {
                c->multiplicity--;
            } else {
                if (prev != nullptr) {
                    prev->next = c->next;
                } else {
                    ms->head = c->next;
                }
                free(c);
                ms->card--;
            }
            return (void*)ref;
        }
        prev = c;
        c = c->next;
    }
    return nullptr;
}

void *mset_get(mset *ms, const void *ref) {
    cell *c = ms->head;
    while (c != nullptr) {
        if (ms->compar(c->ref, ref) == 0) {
            return (void *)c->ref;
        }
        c = c->next;
    }
    return nullptr;
}

#if defined MSET_EXT && defined WANT_MSET_EXT

void *mset_min(mset *ms) {
    if (ms == nullptr || ms->head == nullptr) {
        return nullptr;  
    }

    cell *c = ms->head;
    const void *min_ref = c->ref;
    
    while (c != nullptr) {
        if (ms->compar(c->ref, min_ref) < 0) {
            min_ref = c->ref;
        }
        c = c->next;
    }

    return (void *)min_ref;
}

#endif


void *mset_remove_all(mset *ms, const void *ref) {
    if (ms == nullptr || ref == nullptr) {
        return nullptr;  
    }

    cell *prev = nullptr;
    cell *c = ms->head;

    while (c != nullptr) {
        if (ms->compar(c->ref, ref) == 0) {  
            if (prev != nullptr) {
                prev->next = c->next;
            } else {
                ms->head = c->next;
            }

            const void *removed_ref = c->ref;
            free(c);
            ms->card--;
            return  (void *)removed_ref;  
        }

        prev = c;
        c = c->next;
    }

    return nullptr;  
}
