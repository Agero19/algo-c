//  natop : Natural Operations. Module de calcul sur les objets du type nommé
//    nat défini dans le module nat.

#ifndef NATOP__H
#define NATOP__H

#include "nat.h"

//  sum : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si l'un des deux
//    arguments représente l'infini, renvoie un objet représentant l'infini.
//    Sinon, renvoie un objet représentant la somme des entiers naturels
//    associés aux deux arguments ; en cas de dépassement de capacité, renvoie
//    un objet représentant l'infini.
extern nat sum(nat x, nat y);

//  dist : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si l'un des deux
//    arguments représente l'infini, renvoie un objet représentant l'infini.
//    Sinon, renvoie un objet représentant la distance des entiers naturels
//    associés aux deux arguments.
extern nat dist(nat x, nat y);

//  min : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si l'un des deux
//    arguments représente l'infini, renvoie l'autre. Sinon, renvoie un objet
//    représentant le minimum des entiers naturels associés aux deux arguments.
extern nat min(nat x, nat y);

//  max : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si l'un des deux
//    arguments représente l'infini, renvoie un objet représentant l'infini.
//    Sinon, renvoie un objet représentant le maximum des entiers naturels
//    associés aux deux arguments.
extern nat max(nat x, nat y);

//  is_eq, is_neq, is_leq, is_lth, is_geq, is_gth : si l'un des deux arguments
//    représente une valeur non définie, renvoient false. Sinon, renvoient true
//    ou false selon que la valeur représentée par le premier argument est
//    égale, différente, inférieure ou égale, strictement inférieure, supérieure
//    ou égale, strictement supérieure, à la valeur représentée par le second ou
//    non, ces valeurs pouvant être un entier naturel ou l'infini.

extern bool is_eq(nat x, nat y);
extern bool is_neq(nat x, nat y);
extern bool is_leq(nat x, nat y);
extern bool is_lth(nat x, nat y);
extern bool is_geq(nat x, nat y);
extern bool is_gth(nat x, nat y);

//  prod : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si l'un des deux
//    arguments représente l'infini et l'autre zéro, renvoie un objet
//    représentant une valeur non définie. Sinon, si l'un des deux arguments
//    représente l'infini, renvoie un objet représentant l'infini. Sinon,
//    renvoie un objet représentant le produit des entiers naturels associés aux
//    deux arguments ; en cas de dépassement de capacité, renvoie un objet
//    représentant l'infini.
extern nat prod(nat x, nat y);

//  quot : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si les arguments
//    représentent tous les deux l'infini ou tous les deux zéro, renvoie un
//    objet représentant une valeur non définie. Sinon, si le premier argument
//    représente l'infini ou que le second représente zéro, renvoie un objet
//    représentant l'infini. Sinon, si le second argument représente l'infini,
//    renvoie un objet représentant zéro. Sinon, renvoie un objet représentant
//    le quotient de la division euclidienne du premier argument par le second.
extern nat quot(nat x, nat y);

//  rem : si l'un des deux arguments représente une valeur non définie, renvoie
//    un objet représentant une valeur non définie. Sinon, si le premier
//    argument représente l'infini ou que le second représente zéro, renvoie un
//    objet représentant une valeur non définie. Sinon, si le second argument
//    représente l'infini, renvoie le premier. Sinon, renvoie un objet
//    représentant le reste de la division euclidienne du premier argument par
//    le second.
extern nat rem(nat x, nat y);

#endif
