//  natio : Natural Input-Output. Module pour le transcodage d'objets du type
//    nommé nat défini dans le module nat.

#ifndef NATIO__H
#define NATIO__H

#include <stdio.h>
#include "nat.h"

//  input, output. Les entrées (input) sont des suites de 's' (successor) ou 'p'
//    (predecessor) terminées par '0' (zero), les éventuels caractères
//    d'espacement initiaux étant ignorés. Les sorties (output) sont des suites
//    de 's' terminées par '0'. Les notations '0', 's0' et 'ss0' sont par
//    exemple des écritures de zéro et de ses deux premiers successeurs ; les
//    notations '0', 'ps0', 'psps0' et 'ppss0' des entrées possibles de zéro.

//  input : lecture sur le flot contrôlé par l'objet pointé par stream d'une
//    suite de caractères et affectation de la valeur associée à l'objet pointé
//    par ptr. La fonction input renvoie EOF si une erreur survient lors la
//    lecture des éventuels caractères d'espacement initiaux. Elle renvoie sinon
//    1 ou 0 selon que le transcodage a pu être mené à son terme ou non. Par
//    exemple, la lecture des suites '0', 'ps0', 'psps0' et 'ppss0' provoquent
//    l'affectation d'un objet représentant zéro à l'objet pointé par ptr et le
//    renvoi de 1 ; la lecture des suites 'p0', 'sp0' et 'z' provoquent
//    l'affectation à l'objet pointé par ptr d'un objet représentant une valeur
//    indéfinie et le renvoi de 0.
extern int input(FILE *stream, nat *ptr);

//  output : écriture sur le flot contrôlé par l'objet pointé par stream de la
//    chaine "UNDEF" si x représente une valeur non définie, de la chaine
//    "INFTY" si x représente l'infini et d'une suite de caractères
//    correspondant à l'entier naturel représenté par x sinon. La fonction
//    renvoie EOF si une erreur survient lors d'une opération d'écriture. Elle
//    renvoie sinon 0 lorsque x représente une valeur non définie et 1 dans le
//    cas contraire.
extern int output(FILE *stream, nat x);

//  dinput, doutput : même chose que input et output, mais avec un format
//    externe en écriture décimale des entiers naturels.

extern int dinput(FILE *stream, nat *ptr);
extern int doutput(FILE *stream, nat x);

#endif
