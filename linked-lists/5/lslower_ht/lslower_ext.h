//  lslower_ext : extension of the module lslower. Extension du module lslower.

#ifndef LSLOWER_EXT__H
#define LSLOWER_EXT__H

#include "lslower.h"

//  lslower_partition_pivot_tail : sans effet si la liste associée à s est vide.
//    Déplace sinon respectivement en queue des listes associées à slth, seq et
//    sgth, les cellules de la liste associée à s dont les valeurs du type
//    « slower » sont strictement inférieures, égales et strictement supérieures
//    à la valeur de type « slower » de la cellule originellement en tête de la
//    liste associée à s (à la terminaison, la liste associée à s est vide).
extern void lslower_partition_pivot_tail(lslower *s,
    lslower *slth, lslower *seq, lslower *sgth);

//  lslower_quicksort_stable : tente de recomposer de manière stable la liste
//    associée à s selon la méthode du tri rapide. Renvoie zéro en cas de
//    succès, une valeur non nulle en cas d'échec.
extern int lslower_quicksort_stable(lslower *s);

#endif
