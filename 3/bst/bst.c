//  bst.c : partie implantation d'un module polymorphe pour la spécification
//   ABINR du TDA ABinR(T).

#include "bst.h"
//=== Type cbst ================================================================

//--- Définition cbst ----------------------------------------------------------

typedef struct cbst cbst;

struct cbst {
  cbst *next[2];
  const void *ref;
};

//--- Raccourcis cbst ----------------------------------------------------------

#define EMPTY()     nullptr
#define IS_EMPTY(p) ((p) == nullptr)
#define LEFT(p)     ((p)->next[0])
#define RIGHT(p)    ((p)->next[1])
#define REF(p)      ((p)->ref)
#define NEXT(p, d)  ((p)->next[(d) > 0])

//--- Divers -------------------------------------------------------------------

static size_t add__size_t(size_t x1, size_t x2) {
  return x1 + x2;
}

static size_t max__size_t(size_t x1, size_t x2) {
  return x1 > x2 ? x1 : x2;
}

static size_t min__size_t(size_t x1, size_t x2) {
  return x1 < x2 ? x1 : x2;
}

//--- Fonctions cbst -----------------------------------------------------------

//  DEFUN_CBST__MEASURE : définit la fonction récursive de nom « cbst__ ## fun »
//    et de paramètre un pointeur d'arbre binaire, qui renvoie zéro si l'arbre
//    est vide et « 1 + oper(r0, r1) » sinon, où r0 et r1 sont les valeurs
//    renvoyées par les appels récursifs de la fonction avec les pointeurs des
//    sous-arbres gauche et droit de l'arbre comme paramètres.
#define DEFUN_CBST__MEASURE(fun, oper)                                         \
  static size_t cbst__ ## fun(const cbst * p) {                                \
    return IS_EMPTY(p)                                                         \
      ? 0                                                                      \
      : 1 + oper(cbst__ ## fun(LEFT(p)), cbst__ ## fun(RIGHT(p)));             \
  }

//  cbst__size, cbst__height, cbst__distance : définitions.

DEFUN_CBST__MEASURE(size, add__size_t)
DEFUN_CBST__MEASURE(height, max__size_t)
DEFUN_CBST__MEASURE(distance, min__size_t)

//  cbst__dispose : libère les ressources allouées à l'arbre binaire pointé par
//    p.
static void cbst__dispose(cbst *p) {
  if (!IS_EMPTY(p)) {
    cbst__dispose(LEFT(p));
    cbst__dispose(RIGHT(p));
    free(p);
  }
}

//  ICI, PROCHAINEMENT, LES SPÉCIFICATIONS ET DÉFINITIONS DE :
//    static void *cbst__add_endofpath(cbst **pp, const void *ref,
//        int (*compar)(const void *, const void *));
//    static void *cbst__remove_max(cbst **pp);
//    static void cbst__remove_root(cbst **pp);
//    static void *cbst__remove_climbup_left(cbst **pp, const void *ref,
//        int (*compar)(const void *, const void *));
//    static void *cbst__search(const cbst *p, const void *ref,
//        int (*compar)(const void *, const void *));
// Fonction de recherche récursive dans l'arbre binaire
static void *cbst__search(const cbst *p, const void *ref, 
  int (*compar)(const void *, const void *)) {
  if (IS_EMPTY(p)) return nullptr;

  int comp_result = compar(ref, REF(p));

  if (comp_result == 0) {
      return (void *)REF(p);  // Return the reference if found
  }

  // Use NEXT macro directly with comp_result
  return cbst__search(NEXT(p, comp_result), ref, compar);
}

static void *cbst__remove_climbup_left(cbst **pp, const void *ref, 
  int (*compar)(const void *, const void *)) {
  if (IS_EMPTY(*pp)) return nullptr;

  int comp_result = compar(ref, REF(*pp));
  
  if (comp_result < 0) {
      return cbst__remove_climbup_left(&LEFT(*pp), ref, compar);
  } else if (comp_result > 0) {
      return cbst__remove_climbup_left(&RIGHT(*pp), ref, compar);
  }

  cbst *node_to_remove = *pp;
  const void *removed_ref = REF(node_to_remove);
  *pp = LEFT(node_to_remove);  // Replace current node with left child
  free(node_to_remove);
  return (void *)removed_ref;  // Return the ref of the removed node
}

void *cbst__remove_max(cbst **pp) {
  if (IS_EMPTY(*pp)) return nullptr;
  
  if (IS_EMPTY(RIGHT(*pp))) {
      cbst *max_node = *pp;
      *pp = LEFT(*pp);  
      return max_node;
  }
  
  return cbst__remove_max(&RIGHT(*pp));
}


//  ICI, PROCHAINEMENT, LES SPÉCIFICATIONS ET DÉFINITIONS DE :
//    static size_t cbst__number(const cbst *p, const void *ref,
//        int (*compar)(const void *, const void *), size_t number);
//    static size_t cbst__rank(const cbst *p, const void *ref,
//        int (*compar)(const void *, const void *), size_t rank);

static void *cbst__add_endofpath(cbst **pp, const void *ref, 
  int (*compar)(const void *, const void *)) {
   
   if (*pp == nullptr) { 
       cbst *new_node = malloc(sizeof(cbst));
       if (new_node == nullptr) {
           return nullptr; 
       }
       new_node->ref = ref;
       new_node->next[0] = new_node->next[1] = nullptr; 
       *pp = new_node; 
       return (void *)ref;  // Return the ref instead of the node
   }

   int comp_result = compar(ref, REF(*pp));
   
   if (comp_result == 0) {
       return nullptr; // Already exists
   }

   int dir = (comp_result > 0) ? 1 : 0;
   return cbst__add_endofpath(&((*pp)->next[dir]), ref, compar); // Use NEXT via dir
}

#define REPR__TAB 4

//  ICI, PROCHAINEMENT, LA SPÉCIFICATION ET LA DÉFINITION DE :
//    static void cbst__repr_graphic(const cbst *p,
//      void (*put)(const void *ref), size_t level);
// Fonction d'affichage graphique

#define SPACE " "

static void cbst__repr_graphic(const cbst *p, void (*put)(const void *ref), size_t level) {
  if (IS_EMPTY(p)) {
      return;
  }

  cbst__repr_graphic(LEFT(p), put, level + 1);

  printf("%*s", 1 + REPR__TAB * (int)level, SPACE);

  put(REF(p));
  printf(" (height: %zu)\n", cbst__height(p));

  cbst__repr_graphic(RIGHT(p), put, level + 1);
}

//=== Type bst =================================================================

//--- Définition bst -----------------------------------------------------------

struct bst {
  int (*compar)(const void *, const void *);
  cbst *root;
};

//--- Fonctions bst ------------------------------------------------------------

bst *bst_empty(int (*compar)(const void *, const void *)) {
  bst *t = malloc(sizeof *t);
  if (t == nullptr) {
    return nullptr;
  }
  t->compar = compar;
  t->root = EMPTY();
  return t;
}

void bst_dispose(bst **tptr) {
  if (*tptr == nullptr) {
    return;
  }
  cbst__dispose((*tptr)->root);
  free(*tptr);
  *tptr = nullptr;
}

//  ICI, PROCHAINEMENT, LES DÉFINITIONS DE :
//    bst_add_endofpath
//    bst_remove_climbup_left
//    bst_search
void *bst_search(bst *t, const void *ref) {
  return cbst__search(t->root, ref, t->compar);
}

void *bst_add_endofpath(bst *t, const void *ref) {
  return cbst__add_endofpath(&t->root, ref, t->compar);
}

void *bst_remove_climbup_left(bst *t, const void *ref) {
  return cbst__remove_climbup_left(&t->root, ref, t->compar);
}

size_t bst_size(bst *t) {
  return cbst__size(t->root);
}

size_t bst_height(bst *t) {
  return cbst__height(t->root);
}

size_t bst_distance(bst *t) {
  return cbst__distance(t->root);
}

//  ICI, PROCHAINEMENT, LES DÉFINITIONS DE :
//    bst_number
//    bst_rank

//  ICI, PROCHAINEMENT, LA DÉFINITION DE :
//    bst_repr_graphic

void bst_repr_graphic(bst *t, void (*put)(const void *ref)) {
  cbst__repr_graphic(t->root, put, 0);  
}







