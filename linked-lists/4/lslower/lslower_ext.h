//  lslower_ext : extension of the module lslower. Extension du module lslower.

#ifndef LSLOWER_EXT__H
#define LSLOWER_EXT__H

#include "lslower.h"

//  lslower_move_all_head : renvoie une valeur non nulle si src et dest
//    désignent le même objet (autrement dit si « src == dest ») ou en cas de
//    dépassement de capacité. Déplace sinon en tête de la liste associée à dest
//    la suite des cellules de la liste associée à src et renvoie zéro (à la
//    terminaison, la liste associée à src est vide et la liste associée à dest
//    est la concaténation des listes originelles associées à src et dest).
extern int lslower_move_all_head(lslower *src, lslower *dest);

//  lslower_partition_pivot : sans effet si la liste associée à s est vide.
//    Déplace sinon respectivement dans les listes associées à slth, seq et
//    sgth, les cellules de la liste associée à s dont les valeurs du type
//    « slower » sont strictement inférieures, égales et strictement supérieures
//    à la valeur de type « slower » de la cellule originellement en tête de la
//    liste associée à s (à la terminaison, la liste associée à s est vide).
extern void lslower_partition_pivot(lslower *s,
    lslower *slth, lslower *seq, lslower *sgth);

//  lslower_quicksort : tente de recomposer la liste associée à s selon la
//    méthode du tri rapide. Renvoie zéro en cas de succès, une valeur non nulle
//    en cas d'échec.
extern int lslower_quicksort(lslower *s);

#endif
