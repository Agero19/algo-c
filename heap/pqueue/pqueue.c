//  pqueue.c : partie implantation d'un module mutatif polymorphe pour la
//    spécification FILEP du TDA FileP(T).

#include "pqueue.h"

//  struct pqueue, pqueue : gestion des adresses des objets dans la file de
//    de priorité par tas binaire dynamique.

#define CAPACITY_MIN 1
#define CAPACITY_MUL 2

struct pqueue {
  int (*compar)(const void *, const void *);
  const void **aref;
  size_t capacity;
  size_t length;
};

bool pqueue_is_empty(pqueue *q) {
  return q->length == 0;
}

size_t pqueue_length(pqueue *q) {
  return q->length;
}

pqueue *pqueue_empty(int (*compar)(const void *, const void *)) {
  pqueue *q = malloc(sizeof(pqueue));
  if (q == nullptr) {
    return nullptr;
  }
  q->aref = malloc(CAPACITY_MIN * sizeof(const void *));
  if (q->aref == nullptr) {
    free(q);
    return nullptr;
  }
  q->compar = compar;
  q->capacity = CAPACITY_MIN;
  q->length = 0;
  return q;
}

void pqueue_dispose(pqueue **qptr) {
  if (qptr == nullptr || *qptr == nullptr) {
    return;
  }
  pqueue *q = *qptr;
  free(q->aref);
  free(q);
  *qptr = nullptr;
}

void *pqueue_enqueue(pqueue *q, const void *ref) {
  if (ref == nullptr) {
    return nullptr;
  }

  if (q->length == q->capacity) {
    size_t new_capacity = q->capacity * CAPACITY_MUL;
    
    const void **new_aref = realloc(q->aref, new_capacity * sizeof(const void *));

    if (new_aref == nullptr) {
      return nullptr;
    }
    q->aref = new_aref;
    q->capacity = new_capacity;
  }

  q->aref[q->length] = ref;
  q->length++;
  size_t current = q->length - 1;
  
  while (current > 0) {
    size_t parent = (current - 1) / 2;
    
    if (q->compar(q->aref[current], q->aref[parent]) < 0) {
      const void *temp = q->aref[current];
      q->aref[current] = q->aref[parent];
      q->aref[parent] = temp;
      current = parent;
    } else {
      break;
    }
  }
  return (void *) ref;
}

void *pqueue_dequeue(pqueue *q) {
  if (pqueue_is_empty(q)) {
    return nullptr;
  }

  const void *head = q->aref[0];
  
  if (q->length == 1) {
    q->length = 0;
  } else {
    q->aref[0] = q->aref[q->length - 1];
    q->length--;

    size_t current = 0;
    
    while (1) {
      size_t left = 2 * current + 1;
      size_t right = 2 * current + 2;
      size_t min_child = current;
      
      if (left < q->length && q->compar(q->aref[left], q->aref[min_child]) < 0) {
        min_child = left;
      }
      if (right < q->length && q->compar(q->aref[right], q->aref[min_child]) < 0) {
        min_child = right;
      }
      if (min_child == current) {
        break;
      }
      const void *temp = q->aref[current];
      q->aref[current] = q->aref[min_child];
      q->aref[min_child] = temp;
      current = min_child;
    }
  }
  return (void *) head;
}

void *pqueue_head(pqueue *q) {
  if (pqueue_is_empty(q)) {
    return nullptr;
  }
  return (void *) q->aref[0];
}