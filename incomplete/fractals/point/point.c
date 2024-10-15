#include <math.h>
#include "point.h"

point barycenter(point pa, double ca, point pb, double cb) {
  return
    (point) {
      ca / (ca + cb) * pa.x + cb / (ca + cb) * pb.x,
      ca / (ca + cb) * pa.y + cb / (ca + cb) * pb.y,
    };
}

point symmetrical(point pa, point pb) {
  return
    (point) {
      2.0 * pb.x - pa.x,
      2.0 * pb.y - pa.y,
    };
}

point right_angle_triangle(point pa, point pb) {
  return
    (point) {
      pa.x + 0.5 * (pb.x - pa.x) - 0.5 * (pb.y - pa.y),
      pa.y + 0.5 * (pb.x - pa.x) + 0.5 * (pb.y - pa.y),
    };
}

point equilateral_triangle(point pa, point pb) {
  return
    (point) {
      pa.x + 0.5 * (pb.x - pa.x) - sqrt(3.0) / 2.0 * (pb.y - pa.y),
      pa.y + sqrt(3.0) / 2.0 * (pb.x - pa.x) + 0.5 * (pb.y - pa.y),
    };
}

void draw_point(point p) {
  sg_draw_point((int) round(p.x), (int) round(p.y));
}

void draw_line(point p1, point p2) {
  sg_draw_line(
      (int) round(p1.x), (int) round(p1.y),
      (int) round(p2.x), (int) round(p2.y));
}

void draw_rectangle(point p, double width, double height) {
  sg_draw_rectangle(
      (int) round(p.x), (int) round(p.y),
      (unsigned int) width, (unsigned int) height);
}

void fill_rectangle(point p, double width, double height) {
  sg_fill_rectangle(
      (int) round(p.x), (int) round(p.y),
      (unsigned int) width, (unsigned int) height);
}
