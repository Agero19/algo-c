//  sg : Simple Graph. Module graphique fort limité basé sur l'environnement de
//    bureau X11. Il permet de ne gérer qu'une fenêtre. L'axe horizontal X va
//    vers la droite, l'axe vertical Y, vers le bas, l'origine (0, 0) est le
//    coin supérieur gauche. Les coordonnées et les longueurs sont exprimées en
//    pixels. Les couleurs suivent le codage RGB. Les coordonnées sont codées
//    sur le type int, les longueurs, sur le type unsigned int, les couleurs sur
//    le type unsigned long int.

#ifndef SG__H
#define SG__H

#if !defined __STDC_VERSION__
#error
#endif

#if __STDC_VERSION__ < 202311L

#if defined nullptr
#undef nullptr
#endif
#define nullptr nullptr

#endif

//  sg_open : ouvre une fenêtre de largeur, hauteur, couleur d'arrière plan,
//    couleur de premier plan et titre spécifiés par les paramètres width,
//    height, bgcolor, fgcolor et title. Ni la largeur, ni la hauteur, ni la
//    couleur d'arrière plan ne peuvent modifiées. La couleur de premier plan ou
//    le titre peuvent l'être. Le placement de la fenêtre est laissé au
//    gestionnaire de fenêtre.
extern void sg_open(unsigned int width, unsigned int height,
    unsigned long int bgcolor, unsigned long int fgcolor, const char *title);

//  Toutes les opérations qui suivent nécessitent qu'une fenêtre soit ouverte.
//    Dans le cas contraire, un message d'erreur est envoyé sur la sortie erreur
//    et il est mis fin au programme avec une terminaison normale avec échec

//  sg_close : ferme la fenêtre ouverte.
extern void sg_close(void);

//  sg_clear : vide la fenêtre ouverte en la colorant avec la couleur d'arrière
//    plan.
extern void sg_clear(void);

//  sg_set_fgcolor : modifie la couleur de premier plan de la fenêtre ouverte en
//    lui donnant la valeur spécifiée par color.
extern void sg_set_fgcolor(unsigned long int color);

//  sg_set_title : modifie le titre de la fenêtre ouverte en lui donnant la
//    valeur spécifiée par title.
extern void sg_set_title(const char *title);

//  sg_draw_point : allume dans la fenêtre ouverte le point de coordonnées
//    (x, y) avec la couleur de premier plan.
extern void sg_draw_point(int x, int y);

//  sg_draw_line : trace dans la fenêtre ouverte le segment débutant au point
//    coordonnées (x1, y1) et se terminant au point de coordonnées (x2, y2) avec
//    la couleur de premier plan.
extern void sg_draw_line(int x1, int y1, int x2, int y2);

//  sg_draw_rectangle : trace dans la fenêtre ouverte le rectangle de coin
//    supérieur gauche (x, y), de largeur width et de hauteur height avec la
//    couleur de premier plan.
extern void sg_draw_rectangle(int x, int y, unsigned int width,
    unsigned int height);

//  sg_fill_rectangle : remplit dans la fenêtre ouverte le rectangle de coin
//    supérieur gauche (x, y), de largeur width et de hauteur height avec la
//    couleur de premier plan.
extern void sg_fill_rectangle(int x, int y, unsigned int width,
    unsigned int height);

//  sg_key_event : renvoie une valeur non nulle si et seulement si une touche a
//    été frappée.
extern int sg_key_event(void);

//  sg_get_key : attend jusqu'à ce qu'une touche ait été frappée. Renvoie
//    ensuite la minuscule associée à la touche frappée.
extern int sg_get_key(void);

//  COLOR : macrofonction pour l'obtention de couleurs.
#define COLOR(red, green, blue)                                                \
  ((((unsigned long int) (blue) & 0xff) << 0)                                  \
  | (((unsigned long int) (green) & 0xff) << 8)                                \
  | (((unsigned long int) (red) & 0xff) << 16))

//  RGBMAX : valeur maximale.
#define RGBMAX  255

//  Les huit couleurs limites.

#define BLACK   COLOR(0, 0, 0)
#define RED     COLOR(RGBMAX, 0, 0)
#define LIME    COLOR(0, RGBMAX, 0)
#define BLUE    COLOR(0, 0, RGBMAX)
#define YELLOW  COLOR(RGBMAX, RGBMAX, 0)
#define CYAN    COLOR(0, RGBMAX, RGBMAX)
#define MAGENTA COLOR(RGBMAX, 0, RGBMAX)
#define WHITE   COLOR(RGBMAX, RGBMAX, RGBMAX)

#endif
