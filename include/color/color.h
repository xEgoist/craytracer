#ifndef COLOR_H
#define COLOR_H

#include "utils/utils.h"
#include <stdio.h>
#include <vec3/vec3.h>

void write_color(color pixel_color, int sample_per_pixel) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  double scale = 1.0 / sample_per_pixel;

  r *= scale;
  g *= scale;
  b *= scale;

  printf("%d %d %d\n", (int)(256 * clamp(r, 0.0, 0.999)),
         (int)(256 * clamp(g, 0.0, 0.999)), (int)(256 * clamp(b, 0.0, 0.999)));
}

#endif
