//  set.h : partie interface d'un module mutatif polymorphe pour la
//    spécification ENS du TDA Ens(T) ainsi que pour son extension optionnelle
//    ENSMIN.

//  AUCUNE MODIFICATION DE CE SOURCE N'EST AUTORISÉE.

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « set * » ou « set ** »
//      ont un comportement indéterminé lorsque ce paramètre ou sa déréférence
//      n'est pas l'adresse d'un contrôleur préalablement renvoyée avec succès
//      par la fonction set_empty et non révoquée depuis par la fonction
//      set_dispose ;
//  - aucune fonction ne peut ajouter un pointeur nul à la structure de
//      données ;
//  - les fonctions de type de retour « void * » renvoient un pointeur nul en
//      cas d'échec. En cas de succès, elles renvoient une référence
//      actuellement ou auparavant stockée par la structure de données ;
//  - l'implantation des fonctions dont la spécification ne précise pas qu'elles
//      doivent gérer les cas de dépassement de capacité ne doivent avoir
//      affaire à aucun problème de la sorte.

//  L'extension est formée des éventuelles déclarations et définitions qui
//    figurent aux lignes 112-115.

//  Les identificateurs introduits par l'extension ainsi que les identificateurs
//    de macro SET_EXT et WANT_SET_EXT sont réservés pour être utilisés comme
//    indiqué ci-après :
//  - lorsque le module peut mettre l'intégralité de l'extension à disposition
//      de l'utilisateurice, la macro SET_EXT doit être définie dans l'en-tête
//      "set_ip.h" ;
//  - dans le cas contraire, la macro SET_EXT n'est pas définie dans l'en-tête
//      "set_ip.h" et ne doit pas l'être au sein de l'unité de traduction
//      de prétraitement  ;
//  - la visibilité et l'implantation de l'extension ne sont effectives qu'à la
//      double condition que la macro SET_EXT soit définie dans l'en-tête
//      "set_ip.h" et que la macro WANT_SET_EXT soit définie par
//      l'utilisateurice ;
//  - aucune modification du statut défini/non défini des macros SET_EXT et
//      WANT_SET_EXT ne doit intervenir au sein de l'unité de traduction de
//      prétraitement après que le présent en-tête ait été inclus pour la
//      première fois.

#ifndef SET__H
#define SET__H

//- STANDARD --v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

#include <stdlib.h>

//  struct set, set : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un ensemble de références d'objets
//    quelconques.
typedef struct set set;

//  set_empty : tente d'allouer les ressources nécessaires pour gérer un nouvel
//    ensemble initialement vide. La fonction de comparaison des objets via
//    leurs références est pointée par compar. Renvoie un pointeur nul en cas de
//    dépassement de capacité. Renvoie sinon un pointeur vers le contrôleur
//    associé à l'ensemble.
extern set *set_empty(int (*compar)(const void *, const void *));

//  set_dispose : sans effet si *sptr est un pointeur nul. Libère sinon les
//    ressources allouées à la gestion de l'ensemble associé à *sptr puis
//    affecte un pointeur nul à *sptr.
extern void set_dispose(set **sptr);

//  set_add : renvoie un pointeur nul si ref est un pointeur nul. Recherche
//    sinon dans l'ensemble associé à s la référence d'un objet égal à celui de
//    référence ref au sens de la fonction de comparaison. Si la recherche est
//    positive, renvoie la référence trouvée. Tente sinon d'ajouter ref à
//    l'ensemble ; renvoie un pointeur nul en cas de dépassement de capacité ;
//    renvoie sinon ref.
extern void *set_add(set *s, const void *ref);

//  set_remove : recherche dans l'ensemble associé à s la référence d'un objet
//    égal à celui de référence ref au sens de la fonction de comparaison. Si la
//    recherche est négative, renvoie un pointeur nul. Retire sinon la référence
//    trouvée de l'ensemble et renvoie la référence trouvée.
extern void *set_remove(set *s, const void *ref);

//  set_pick : renvoie un pointeur nul si l'ensemble associé à s est vide.
//    Renvoie sinon l'une des références appartenant à l'ensemble.
extern void *set_pick(set *s);

//  set_get : recherche dans l'ensemble associé à s la référence d'un objet égal
//    à celui de référence ref au sens de la fonction de comparaison. Si la
//    recherche est négative, renvoie un pointeur nul. Renvoie sinon la
//    référence trouvée.
extern void *set_get(set *s, const void *ref);

//  set_is_empty : renvoie true ou false selon que l'ensemble associé à s est
//    vide ou non.
extern bool set_is_empty(set *s);

//  set_card : renvoie le cardinal de l'ensemble associé à s.
extern size_t set_card(set *s);

//- STANDARD --^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#undef SET_EXT
#include "set_ip.h"

#if defined SET_EXT && defined WANT_SET_EXT

//- EXTENSION -v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

//  set_min : renvoie un pointeur nul si l'ensemble associé à s est vide.
//    Recherche sinon dans l'ensemble la référence d'un objet minimal au sens de
//    la fonction de comparaison. Renvoie la référence trouvée.
extern void *set_min(set *s);

//- EXTENSION -^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#endif

#endif
