//  point : Point. Module de calculs de points et de simplification dans
//    l'utilisation du module sg. Des représentations graphiques de qualité
//    nécessitant des calculs ne peuvent être obtenues que lorsque ces calculs
//    sont effectués sur les réels virgule flottante. Le module point :
//    - définit le type point, une structure à deux composantes de type double ;
//    - propose quelques fonctions d'obtention de points particuliers à partir
//      de deux autres ;
//    - adapte les procédures de traçage et de remplissage du module sg.

#ifndef POINT__H
#define POINT__H

#include "sg.h"

//  définition du nom de type point.
typedef struct {
  double x;
  double y;
} point;

//  barycenter : renvoie le barycentre des points pa et pb affectés des
//    coefficients ca et cb, avec l'hypothèse que ca + cb n'est pas nul.
extern point barycenter(point pa, double ca, point pb, double cb);

//  symmetrical : renvoie le symétrique p du point pa par rapport à la droite
//    orthogonale au segment pa-p et passant par pb. Le point pb est donc le
//    le milieu du segment pa-p.
extern point symmetrical(point pa, point pb);

//  right_angle_triangle : renvoie le point p situé sur la médiatrice du segment
//    d'extrémités les points pa et pb tel que l'angle des segments pa-pb et
//    pa-p vaut 45 degrés. Le triangle (pa, p, pb) est donc rectangle en p.
extern point right_angle_triangle(point pa, point pb);

//  equilateral_triangle : renvoie le point p situé sur la médiatrice du segment
//    d'extrémités les points pa et pb tel que l'angle des segments pa-pb et
//    pa-p vaut 60 degrés. Le triangle (pa, p, pb) est donc équilatéral.
extern point equilateral_triangle(point pa, point pb);

//  draw_point : allume dans la fenêtre ouverte le point p avec la couleur de
//    premier plan.
extern void draw_point(point p);

//  draw_line : trace dans la fenêtre ouverte le segment débutant au point p1
//    et se terminant au point p2 avec la couleur de premier plan.
extern void draw_line(point p1, point p2);

//  draw_rectangle : trace dans la fenêtre ouverte le rectangle de coin
//    supérieur gauche le point p, de largeur width et de hauteur height avec la
//    couleur de premier plan.
extern void draw_rectangle(point p, double width, double height);

//  fill_rectangle : remplit dans la fenêtre ouverte le rectangle de coin
//    supérieur gauche le point p, de largeur width et de hauteur height avec la
//    couleur de premier plan.
extern void fill_rectangle(point p, double width, double height);

#endif
