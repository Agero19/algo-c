//  mset.h : partie interface d'un module mutatif polymorphe pour la
//    spécification MENS du TDA MEns(T) ainsi que pour son extension optionnelle
//    MENSMIN.

//  AUCUNE MODIFICATION DE CE SOURCE N'EST AUTORISÉE.

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « mset * » ou « mset ** »
//      ont un comportement indéterminé lorsque ce paramètre ou sa déréférence
//      n'est pas l'adresse d'un contrôleur préalablement renvoyée avec succès
//      par la fonction mset_empty et non révoquée depuis par la fonction
//      mset_dispose ;
//  - aucune fonction ne peut ajouter un pointeur nul à la structure de
//      données ;
//  - les fonctions de type de retour « void * » renvoient un pointeur nul en
//      cas d'échec. En cas de succès, elles renvoient une référence
//      actuellement ou auparavant stockée par la structure de données ;
//  - l'implantation des fonctions dont la spécification ne précise pas qu'elles
//      doivent gérer les cas de dépassement de capacité ne doivent avoir
//      affaire à aucun problème de la sorte.

//  L'extension est formée des éventuelles déclarations et définitions qui
//    figurent aux lignes 121-125.

//  Les identificateurs introduits par l'extension ainsi que les identificateurs
//    de macro MSET_EXT et WANT_MSET_EXT sont réservés pour être utilisés comme
//    indiqué ci-après :
//  - lorsque le module peut mettre l'intégralité de l'extension à disposition
//      de l'utilisateurice, la macro MSET_EXT doit être définie dans l'en-tête
//      "mset_ip.h" ;
//  - dans le cas contraire, la macro MSET_EXT n'est pas définie dans l'en-tête
//      "mset_ip.h" et ne doit pas l'être au sein de l'unité de traduction
//      de prétraitement  ;
//  - la visibilité et l'implantation de l'extension ne sont effectives qu'à la
//      double condition que la macro MSET_EXT soit définie dans l'en-tête
//      "mset_ip.h" et que la macro WANT_MSET_EXT soit définie par
//      l'utilisateurice ;
//  - aucune modification du statut défini/non défini des macros MSET_EXT et
//      WANT_MSET_EXT ne doit intervenir au sein de l'unité de traduction de
//      prétraitement après que le présent en-tête ait été inclus pour la
//      première fois.

#ifndef MSET__H
#define MSET__H

//- STANDARD --v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

#include <stdlib.h>
#include <stdbool.h>
//  struct mset, mset : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un multi-ensemble de références
//    d'objets quelconques.
typedef struct mset mset;

//  mset_empty : tente d'allouer les ressources nécessaires pour gérer un
//    nouveau multi-ensemble initialement vide. La fonction de comparaison des
//    objets via leurs références est pointée par compar. Renvoie un pointeur
//    nul en cas de dépassement de capacité. Renvoie sinon un pointeur vers le
//    contrôleur associé au multi-ensemble.
extern mset *mset_empty(int (*compar)(const void *, const void *));

//  mset_dispose : sans effet si *msptr est un pointeur nul. Libère sinon les
//    ressources allouées à la gestion du multi-ensemble associé à *msptr puis
//    affecte un pointeur nul à *msptr.
extern void mset_dispose(mset **msptr);

//  mset_add : renvoie un pointeur nul si ref est un pointeur nul. Tente sinon
//    d'ajouter ref au multi-ensemble associé à ms. Renvoie un pointeur nul en
//    cas de dépassement de capacité ; renvoie sinon ref.
extern void *mset_add(mset *ms, const void *ref);

//  mset_remove : recherche dans le multi-ensemble associé à ms la référence
//    d'un objet égal à celui de référence ref au sens de la fonction de
//    comparaison. Si la recherche est négative, renvoie un pointeur nul. Retire
//    sinon la référence trouvée du multi-ensemble et renvoie la référence
//    trouvée.
extern void *mset_remove(mset *ms, const void *ref);

//  mset_remove_all : retire du multi-ensemble associé à ms toutes les
//    références d'objets égaux à celui de référence ref au sens de la fonction
//    de comparaison. Renvoie un pointeur nul si aucune référence de la sorte
//    n'existe. Renvoie sinon l'une des références retirées.
extern void *mset_remove_all(mset *ms, const void *ref);

//  mset_pick : renvoie un pointeur nul si le multi-ensemble associé à ms est
//    vide. Renvoie sinon l'une des références appartenant au multi-ensemble.
extern void *mset_pick(mset *ms);

//  mset_count : renvoie la multiplicité des objets dont la référence appartient
//    au multi-ensemble associé à ms et qui sont égaux à celui de référence ref
//    au sens de la fonction de comparaison.
extern size_t mset_count(mset *ms, const void *ref);

//  mset_get : recherche dans le multi-ensemble associé à ms la référence d'un
//    objet égal à celui de référence ref au sens de la fonction de comparaison.
//    Si la recherche est négative, renvoie un pointeur nul. Renvoie sinon la
//    référence trouvée.
extern void *mset_get(mset *ms, const void *ref);

//  mset_is_empty : renvoie true ou false selon que le multi-ensemble associé à
//    ms est vide ou non.
extern bool mset_is_empty(mset *ms);

//  mset_card : renvoie le cardinal du multi-ensemble associé à ms.
extern size_t mset_card(mset *ms);

//- STANDARD --^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#undef MSET_EXT
#include "mset_ip.h"

#if defined MSET_EXT && defined WANT_MSET_EXT

//- EXTENSION -v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

//  mset_min : renvoie un pointeur nul si le multi-ensemble associé à ms est
//    vide. Recherche sinon dans le multi-ensemble la référence d'un objet
//    minimal au sens de la fonction de comparaison. Renvoie la référence
//    trouvée.
extern void *mset_min(mset *ms);

//- EXTENSION -^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#endif

#endif
