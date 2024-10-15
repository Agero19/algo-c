//  nat : Natural. Module sur un intervalle fini des entiers naturels contenant
//    zéro. Les entiers naturels dudit intervalle sont représentés par au moins
//    un objet du type nommé « nat ». Le type « nat » possède des valeurs
//    spéciales qui ne correspondent pas à des entiers naturels de
//    l'intervalle : certaines d'entre elles, et au moins une, représente
//    l'infini (positif), d'autres, et au moins une, une valeur non définie.
//
//    Le nombre d'éléments appartenant à l'intervalle dépend de l'implantation.
//    Deux implantations doivent au minimum être proposées : l'une de portée
//    réduite à quelques dizaines éléments, l'autre, beaucoup plus conséquente.
//    La première est l'implantation par défaut ; elle peut également être
//    explicitement fixée avec l'option « -DNAT_IMPLEMENTATION=LOW ». L'option
//    « -DNAT_IMPLEMENTATION=HIGH » sélectionne la seconde.
//
//    Les opérations spécifiées dans la suite à un paramètre de type « nat » ont
//    un comportement indéterminé si la valeur de leur paramètre n'est pas le
//    résultat d'une opération qui renvoie une valeur de type « nat ».

#ifndef NAT__H
#define NAT__H

#include <stdio.h>
#include <stdlib.h>

#if !defined __STDC_VERSION__
#error
#endif

#if __STDC_VERSION__ < 202311L

#include <stdbool.h>

#if defined nullptr
#undef nullptr
#endif
#define nullptr (void *) 0

#endif

//  nat : définition du (nom de) type « nat ».
typedef const void *nat;

//  zero : renvoie un objet représentant zéro.
extern nat zero(void);

//  infty : renvoie un objet représentant l'infini.
extern nat infty(void);

//  undef : renvoie un objet représentant une valeur non définie.
extern nat undef(void);

//  succ : si l'argument représente une valeur non définie, envoie un message
//    d'erreur sur la sortie erreur et provoque un arrêt anormal du programme.
//    Si l'argument représente l'infini ou s'il représente le maximum de
//    l'intervalle des entiers naturels eu égard à l'implantation, renvoie un
//    objet représentant l'infini. Sinon, renvoie un objet représentant le
//    successeur de l'entier naturel associé à l'argument.
extern nat succ(nat x);

//  pred : si l'argument représente une valeur non définie ou s'il représente
//    zéro, envoie un message d'erreur sur la sortie erreur et provoque un arrêt
//    anormal du programme. Si l'argument représente l'infini, renvoie un objet
//    représentant l'infini. Sinon, renvoie un objet représentant le
//    prédécesseur de l'entier naturel associé à l'argument.
extern nat pred(nat x);

//  is_zero : renvoie true si l'argument représente zéro, false sinon.
extern bool is_zero(nat x);

//  is_infty : renvoie true si l'argument représente l'infini, false sinon.
extern bool is_infty(nat x);

//  is_undef : renvoie true si l'argument représente une valeur non définie,
//    false sinon.
extern bool is_undef(nat x);

#endif
