//  lslower : list of sequences of lower case letters. Module permettant de
//    gérer des listes dynamiques simplement chainées sur le type « slower »
//    défini dans le module slower.

#ifndef LSLOWER__H
#define LSLOWER__H

#include <stdio.h>
#include <stdlib.h>
#include "slower.h"

//  struct lslower, lslower : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer une liste dynamique simplement chainée
//    sur le type « slower ».
typedef struct lslower lslower;

//  lslower_empty : tente d'allouer les ressources nécessaires pour gérer une
//    nouvelle liste initialement vide. Renvoie un pointeur nul en cas de
//    dépassement de capacité. Renvoie sinon un pointeur vers le contrôleur
//    associé à la liste.
extern lslower *lslower_empty(void);

//  lslower_is_empty : renvoie true ou false selon que la liste associée à s est
//    vide ou non.
extern bool lslower_is_empty(const lslower *s);

//  lslower_length : renvoie le longueur de la liste associée à s.
extern size_t lslower_length(const lslower *s);

//  lslower_dispose : sans effet si *sptr est un pointeur nul. Libère sinon les
//    ressources allouées à la gestion de la liste associée à *sptr puis affecte
//    un pointeur nul à *sptr.
extern void lslower_dispose(lslower **sptr);

//  lslower_fput : tente d'écrire sur le flot contrôlé par l'objet pointé par
//    stream les valeurs de type « slower » mémorisées dans les cellules de la
//    liste associée à s. Le délimiteur gauche de la liste des valeurs produites
//    est vide, son séparateur, l'espace, son délimiteur droit, la fin de ligne.
//    Renvoie zéro en cas de succès, EOF en cas d'échec.
extern int lslower_fput(const lslower *s, FILE *stream);

//  lslower_insert_head, lslower_insert_tail : tente d'allouer une cellule
//    contenant une copie de *ptr. Renvoie une valeur non nulle en cas de
//    dépassement de capacité. Insère sinon la cellule allouée en tête (head),
//    en queue (tail) de la liste et renvoie zéro.
extern int lslower_insert_head(lslower *s, const slower *ptr);
extern int lslower_insert_tail(lslower *s, const slower *ptr);

//  lslower_head_value, lslower_tail_value : renvoie une valeur non nulle si la
//    liste associée à s est vide. Affecte sinon à *ptr la valeur de type
//    « slower » mémorisée dans la cellule de tête (head), de queue (tail) de la
//    liste et renvoie zéro.
extern int lslower_head_value(const lslower *s, slower *ptr);
extern int lslower_tail_value(const lslower *s, slower *ptr);

//  lslower_move_head_head, lslower_move_head_tail : renvoie une valeur non
//    nulle si la liste associée à src est vide. Déplace sinon la cellule de
//    tête de la liste associée à src en tête (head_head), en queue (head_tail)
//    de la liste associée à dest et renvoie zéro.
extern int lslower_move_head_head(lslower *src, lslower *dest);
extern int lslower_move_head_tail(lslower *src, lslower *dest);

//  lslower_move_all_head, lslower_move_all_tail : renvoie une valeur non nulle
//    si src et dest désignent le même objet (autrement dit si « src == dest »).
//    Déplace sinon en tête (all_head), en queue (all_tail) de la liste associée
//    à dest la suite des cellules de la liste associée à src et renvoie zéro (à
//    la terminaison, la liste associée à src est vide et la liste associée à
//    dest est la concaténation des listes originelles associées à src et dest).
extern int lslower_move_all_head(lslower *src, lslower *dest);
extern int lslower_move_all_tail(lslower *src, lslower *dest);

#endif
