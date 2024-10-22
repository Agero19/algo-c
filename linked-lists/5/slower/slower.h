//  slower : sequences of lower case letters. Un module permettant de lire,
//    d'écrire, de générer de manière pseudo-aléatoire et de comparer des mots
//    (suites finies) de lettres minuscules de l'alphabet usuel (sans accent ni
//    cédille). Les mots sont mémorisés dans une structure nommée « slower ». La
//    manière dont sont rangées les lettres dans la structure n'est pas
//    spécifiée.
//
//  Le module est sensible aux éventuelles définitions préalables des
//    macroconstantes LOWER_CARD, SLOWER_LENGTH et SLOWER_COMPAR_LENGTH. Seules
//    les lettres minuscules comprises entre la première, 'a', et la
//    LOWER_CARD-ième lettre de l'alphabet usuel sont valides. Les mots ont tous
//    pour longueur SLOWER_LENGTH. Seules les SLOWER_COMPAR_LENGTH premières
//    lettres des mots sont prises en compte dans le test de comparaison.
//
//  Par défaut, c'est-à-dire si ces macroconstantes ne sont pas définies au
//    préalable, LOWER_CARD vaut 4, SLOWER_LENGTH vaut 4 et SLOWER_COMPAR_LENGTH
//    vaut SLOWER_LENGTH.

#ifndef SLOWER__H
#define SLOWER__H

#define LOWER_SET__FULL "abcdefghijklmnopqrstuvwxyz"

#define LOWER_CARD__DEFAULT 4

#ifndef LOWER_CARD
#define LOWER_CARD LOWER_CARD__DEFAULT
#endif

_Static_assert(LOWER_CARD > 0 && LOWER_CARD < sizeof(LOWER_SET__FULL),
    "Illegal value of LOWER_CARD.");

#define SLOWER_LENGTH__DEFAULT 4

#ifndef SLOWER_LENGTH
#define SLOWER_LENGTH SLOWER_LENGTH__DEFAULT
#endif

#if SLOWER_LENGTH <= 0
#error Illegal value of SLOWER_LENGTH.
#endif

#ifndef SLOWER_COMPAR_LENGTH
#define SLOWER_COMPAR_LENGTH SLOWER_LENGTH
#endif

#if SLOWER_COMPAR_LENGTH <= 0 || SLOWER_COMPAR_LENGTH > SLOWER_LENGTH
#error Illegal value of SLOWER_COMPAR_LENGTH.
#endif

#include <stdio.h>
#include <stdlib.h>

//  slower : nom d'une structure capable de mémoriser un mot de SLOWER_LENGTH
//    lettres minuscules.
typedef struct {
  char reserved__usage[SLOWER_LENGTH];
} slower;

//  slower_fget : tente de lire sur le flot contrôlé par l'objet pointé par
//    stream un mot de SLOWER_LENGTH lettres minuscules comprises entre la
//    première et la LOWER_CARD-ième lettre de l'alphabet usuel. Si une erreur
//    survient lors la lecture des éventuels caractères d'espacement initiaux,
//    renvoie EOF. Sinon, si la lecture des SLOWER_LENGTH lettres minuscules n'a
//    pu être menée à son terme, renvoie une valeur strictement positive. Sinon,
//    affecte la valeur associée à l'objet pointé par ptr et renvoie zéro.
extern int slower_fget(slower *ptr, FILE *stream);

//  slower_fput : tente d'écrire sur le flot contrôlé par l'objet pointé par
//    stream les SLOWER_LENGTH lettres minuscules du mot associé à l'objet
//    pointé par ptr. Renvoie zéro en cas de succès, EOF en cas d'échec.
extern int slower_fput(const slower *ptr, FILE *stream);

//  slower_rand : génère de manière pseudo-aléatoire en utilisant la fonction
//    standard rand un mot de SLOWER_LENGTH lettres minuscules comprises entre
//    la première et la LOWER_CARD-ième lettre de l'alphabet usuel et affecte la
//    valeur associée à l'objet pointé par ptr.
extern void slower_rand(slower *ptr);

//  slower_compar : compare les deux mots associés aux objets pointés par ptr1
//    et ptr2 selon l'ordre lexicographique en ne considérant que leurs préfixes
//    de longueur SLOWER_COMPAR_LENGTH. Renvoie une valeur strictement
//    inférieure, égale ou strictement supérieure à zéro selon que le premier
//    mot est strictement inférieur, égal ou strictement supérieur au second.
extern int slower_compar(const slower *ptr1, const slower *ptr2);

#endif
