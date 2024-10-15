#include <stdlib.h>
#include "point.h"
#include "sg.h"

#define WIDTH   640
#define HEIGHT  400

//  draw_cross : trace un X dont le centre est au point p et dont les branches
//    ont pour longueur d * sqrt(2).
void draw_cross(point p, int d);

#define NBARYCENTERS 10

int main() {
  sg_open(WIDTH, HEIGHT, BLACK, WHITE, "Point Trial");
  {
    sg_clear();
    sg_set_title("Point Trial: barycenter, 1:1, 2:1, 3:1..."
        " Hit any key to continue");
    for (int k = 0; k < NBARYCENTERS; ++k) {
      int dx = WIDTH / 10;
      double y = 1.0 * HEIGHT / (NBARYCENTERS + 1) * (k + 1);
      point pa = (point) {
        0 + dx, y
      };
      point pb = (point) {
        WIDTH - dx, y
      };
      sg_set_fgcolor(MAGENTA);
      draw_line(pa, pb);
      sg_set_fgcolor(WHITE);
      draw_cross(pa, 4);
      draw_cross(pb, 4);
      point pc = barycenter(pa, k + 1, pb, 1);
      sg_set_fgcolor(CYAN);
      draw_cross(pc, 4);
    }
    sg_get_key();
  }
  {
    sg_clear();
    sg_set_title("Point Trial: symmetrical, pa, pb, result."
        " Hit any key to continue");
    point pa = {
      0.25 * WIDTH, 0.75 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pa, 4);
    sg_get_key();
    point pb = {
      0.4 * WIDTH, 0.6 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pb, 4);
    sg_get_key();
    point pc = symmetrical(pa, pb);
    sg_set_fgcolor(CYAN);
    draw_cross(pc, 4);
    sg_get_key();
    sg_set_fgcolor(MAGENTA);
    draw_line(pa, pc);
    sg_get_key();
  }
  {
    sg_clear();
    sg_set_title("Point Trial: right_angle_triangle, pa, pb, result."
        " Hit any key to continue");
    point pa = {
      0.25 * WIDTH, 0.75 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pa, 4);
    sg_get_key();
    point pb = {
      0.6 * WIDTH, 0.4 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pb, 4);
    sg_get_key();
    point pc = right_angle_triangle(pa, pb);
    sg_set_fgcolor(CYAN);
    draw_cross(pc, 4);
    sg_get_key();
    sg_set_fgcolor(MAGENTA);
    draw_line(pa, pc);
    draw_line(pb, pc);
    sg_get_key();
  }
  {
    sg_clear();
    sg_set_title("Point Trial: equilateral_triangle, pa, pb, result."
        " Hit any key to continue");
    point pa = {
      0.25 * WIDTH, 0.75 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pa, 4);
    sg_get_key();
    point pb = {
      0.3 * WIDTH, 0.3 * HEIGHT
    };
    sg_set_fgcolor(CYAN);
    draw_cross(pb, 4);
    sg_get_key();
    point pc = equilateral_triangle(pa, pb);
    sg_set_fgcolor(CYAN);
    draw_cross(pc, 4);
    sg_get_key();
    sg_set_fgcolor(MAGENTA);
    draw_line(pa, pc);
    draw_line(pb, pc);
    draw_line(pa, pb);
    sg_get_key();
  }
  sg_close();
  return EXIT_SUCCESS;
}

void draw_cross(point p, int d) {
  draw_line(
      (point) { p.x - d, p.y - d },
      (point) { p.x + d, p.y + d });
  draw_line(
      (point) { p.x - d, p.y + d },
      (point) { p.x + d, p.y - d });
}
