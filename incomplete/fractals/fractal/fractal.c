#include <stdio.h>
#include <string.h>
#include "fractal.h"
#include "point.h"
#include "sg.h"

#define QUIT  'q'

#define TITLE_ORDER " / order = "

//  ndigits : renvoie le nombre de chiffres de n dans son écriture en base base,
//    en supposant n >= 0 et base >= 2.
static size_t ndigits(int n, int base) {
  if (n < base) {
    return 1;
  }
  return 1 + ndigits(n / base, base);
}

//  set_title : efface la fenêtre, affiche le titre title avec affichage de
//    l'ordre n, en supposant n >= 0.
static void make_title(const char *title, int n) {
  sg_clear();
  char s[strlen(title) + strlen(TITLE_ORDER) + ndigits(n, 10) + 1];
  sprintf(s, "%s%s%d", title, TITLE_ORDER, n);
  sg_set_title(s);
}

//  graduate_color : fixe la couleur de premier plan entre le vert et le marron
//    proportionnellement à k, en supposant 0 <= k <= n et n >= 1.
static void graduate_color(int k, int n) {
  sg_set_fgcolor(
      COLOR((int) (RGBMAX * (double) k / n), RGBMAX / 2, RGBMAX / 4));
}

#define MARGIN(size) (size) / 10

//--- Carrés emboités ----------------------------------------------------------

#define RF4_SHIFT 9.0

//  r_fitted_4 : produit l'emboité d'ordre n du quadrilatère de sommets pa, pb,
//    pc et pd avec rotation droite de proportion 1 / (RF4_SHIFT + 1).
static void r_fitted_4(int n, point pa, point pb, point pc, point pd) {
  if (n < 0) {
    return;
  }
  draw_line(pa, pb);
  draw_line(pb, pc);
  draw_line(pc, pd);
  draw_line(pd, pa);
  if (n == 0) {
    return;
  }
  r_fitted_4(n - 1,
      barycenter(pa, RF4_SHIFT, pb, 1.0),
      barycenter(pb, RF4_SHIFT, pc, 1.0),
      barycenter(pc, RF4_SHIFT, pd, 1.0),
      barycenter(pd, RF4_SHIFT, pa, 1.0));
}

int fitted_squares(const char *title, unsigned int size, int n) {
  unsigned int d = MARGIN(size);
  for (int k = 0; k <= n; ++k) {
    make_title(title, k);
    graduate_color(k, n);
    r_fitted_4(k,
        (point) { d, d },
        (point) { size - d, d },
        (point) { size - d, size - d },
        (point) { d, size - d });
    if (sg_get_key() == QUIT) {
      return -1;
    }
  }
  return 0;
}

/*
 *  À COMPLÉTER SUR LE MÊME MODÈLE.
 */
