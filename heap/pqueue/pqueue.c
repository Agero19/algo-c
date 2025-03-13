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
  const void **aref = malloc((sizeof *aref) * CAPACITY_MIN);
  if (aref == NULL) {
    return NULL;
  }
  pqueue *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->aref = aref;
  p->capacity = CAPACITY_MIN;
  p->length = 0;
  p->compar = compar;
  return p;
}

void pqueue_dispose(pqueue **qptr) {
  if (*qptr == NULL) {
    return;
  }
  free((*qptr)->aref);
  free(*qptr);
}

void *pqueue_head(pqueue *q) {
  if (q->length == 0) {
    return NULL;
  }
  return (void *) q->aref[0];
}

void *pqueue_enqueue(pqueue *q, const void *ref) {
  if (ref == NULL) {
    return NULL;
  }
  if (q->capacity == q->length) {
    if ((sizeof *q->aref) * q->length > SIZE_MAX / CAPACITY_MUL) {
      return NULL;
    }
    const void **a = realloc(q->aref,
        (sizeof *q->aref) * q->length * CAPACITY_MUL);
    if (a == NULL) {
      return NULL;
    }
    q->aref = a;
    q->capacity *= CAPACITY_MUL;
  }
  q->aref[q->length] = ref;
  ++q->length;
  size_t k = q->length - 1;
  while (k != 0 && q->compar(q->aref[k], q->aref[(k - 1) / 2]) < 0) {
    const void *r = q->aref[k];
    q->aref[k] = q->aref[(k - 1) / 2];
    q->aref[(k - 1) / 2] = r;
    k = (k - 1) / 2;
  }
  return (void *) ref;
}

void *pqueue_dequeue(pqueue *q) {
  if (q->length == 0) {
    return NULL;
  }
  const void *r = q->aref[0];
  size_t k = 0;
  while (2 * k + 1 < q->length) {
    size_t min;
    if (2 * k + 2 == q->length) {
      min = 2 * k + 1;
    } else {
      min = q->compar(q->aref[2 * k + 1], q->aref[2 * k + 2]) < 0
          ? 2 * k + 1 : 2 * k + 2;
    }
    if (q->compar(q->aref[k], q->aref[min]) < 0) {
      q->aref[k] = q->aref[min];
      k = min;
    }
  }
  q->aref[k] = q->aref[q->length - 1];
  while (k != 0 && q->compar(q->aref[k], q->aref[(k - 1) / 2]) < 0) {
    const void *r = q->aref[k];
    q->aref[k] = q->aref[(k - 1) / 2];
    q->aref[(k - 1) / 2] = r;
    k = (k - 1) / 2;
  }
  --q->length;
  return (void *) r;
}
