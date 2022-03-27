#ifndef CONSTS_H
#define CONSTS_H
#include <math.h>


const double pi = 3.1415926535897932385;


inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
#include "ray/ray.h"
#include "vec3/vec3.h"
#endif
