//  heapsort.c : partie implantation d'un module polymorphe pour le tri par tas.

#include "heapsort.h"

//  heapsort_down : il est supposé que base est l'adresse du premier composant
//    d'un tableau de longueur nmemb et de taille de composants size, que
//    nmemb >= 1, que k <= nmemb - 1 et que le tableau est un maximier sur
//    [ k + 1 ... nmemb - 1 ] relativement à la fonction de comparaison pointée
//    par compar. Descend le composant d'indice k à la bonne place de manière à
//    faire du tableau un maximier sur [ k ... nmemb - 1 ].
//static void heapsort_down(char *base, size_t nmemb, size_t size,
//    int (*compar)(const void *, const void *), size_t k);

//  heapsort_down_from_0 : il est supposé que base est l'adresse du premier
//    composant d'un tableau de longueur n + 1 et de taille de composants size,
//    que n >= 1 et que le tableau est un maximier sur [ 0 ... n ] relativement
//    à la fonction de comparaison pointée par compar. Effectue l'échange des
//    composants d'indices n et 0 puis la descente du composant d'indice 0 à la
//    bonne place de manière à faire du tableau un maximier sur [ 0 ... n - 1 ].
//static void heapsort_down_from_0(char *base, size_t n, size_t size,
//    int (*compar)(const void *, const void *));
