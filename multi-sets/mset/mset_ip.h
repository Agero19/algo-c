//  mset_ip.h : précisions sur l'implantation du module mset.

//  Limites : ...

// mset_empty : temps O(1) ; espace O(1)
// mset_dispose : temps O(n) ; espace O(1)
// mset_add : temps O(n) ; espace O(1)
// mset_remove : temps O(n) ; espace O(1)
// mset_remove_all : temps O(n) ; espace O(1)
// mset_pick : temps O(1) ; espace O(1)
// mset_count : temps O(n) ; espace O(1)
// mset_get : temps O(n) ; espace O(1)
// mset_is_empty : temps O(1) ; espace O(1)
// mset_card : temps O(n) ; espace O(1)


#define MSET_EXT

// mset_min : temps O(n) ; espace O(1)

