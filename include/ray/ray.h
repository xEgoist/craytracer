#ifndef RAY_H
#define RAY_H

#include <vec3/vec3.h>

typedef struct {
  point3 orig;
  Vec3 dir;
} Ray;

point3 at(double t, Ray r) {
  Vec3 vv = mult_vec3(&r.dir, t);
  return add_vec3(&r.orig, &vv);
}

#endif
