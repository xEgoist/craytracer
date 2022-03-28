#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

double random_double() {

  // srand(time(0));
  return rand() / (RAND_MAX + 1.0);
}
inline double random_double_min_max(double min, double max) {
  return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}
#include "ray/ray.h"
#include "vec3/vec3.h"
#endif
