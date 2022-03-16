#include "color/color.h"
#include "ray/ray.h"
#include "vec3/vec3.h"
#include <stdio.h>
#include <stdlib.h>
#define PROJECT_NAME "craytracer"
const int image_width = 256;
const int image_height = 256;

double hit_sphere(point3 center, double radius, Ray r) {
  Vec3 oc = sub_vec3(r.orig, center);
  double a = dot(r.dir, r.dir);
  double b = 2.0 * dot(oc, r.dir);
  double c = dot(oc, oc) - radius * radius;
  double discrim = b * b - 4 * a * c;
  if (discrim < 0) {
    return -1.0;
  }
  return (-b - sqrt(discrim)) / (2.0 * a);
}

color ray_color(Ray r) {
  double t = hit_sphere((point3){0, 0, -1}, 0.5, r);
  if (t > 0.0) {
    Vec3 N = unit_vector(sub_vec3(at(t, r), (Vec3){0, 0, -1}));
    return mult_vec3((color){N.x + 1, N.y + 1, N.z + 1}, 0.5);
  }
  Vec3 unit_direction = unit_vector(r.dir);
  t = 0.5 * (unit_direction.y + 1.0);
  color cc = mult_vec3((color){1.0, 1.0, 1.0}, (1.0 - t));
  color multit = mult_vec3((color){0.5, 0.7, 1.0}, t);
  return add_vec3(cc, multit);
}

int main() {
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)((double)image_width / aspect_ratio);
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;
  point3 origin = {0, 0, 0};
  Vec3 horiz = {viewport_width, 0, 0};
  Vec3 vert = {0, viewport_height, 0};
  Vec3 horiz_2 = div_vec3(horiz, 2);
  Vec3 vert_2 = div_vec3(vert, 2);
  Vec3 orig_horiz = sub_vec3(origin, horiz_2);
  Vec3 orig_horiz_vert = sub_vec3(orig_horiz, vert_2);
  Vec3 lower_left_corner =
      sub_vec3(orig_horiz_vert, (Vec3){0, 0, focal_length});

  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height - 1; j >= 0; --j) {
    fprintf(stderr, "\rScanLines Remaining: %d ", j);
    fflush(stderr);
    for (int i = 0; i < image_width; ++i) {
      double u = (double)i / (image_width - 1);
      double v = (double)j / (image_height - 1);
      //------- Ray calculations------
      Vec3 uh = mult_vec3(horiz, u);
      Vec3 vv = mult_vec3(vert, v);
      Vec3 luh = add_vec3(lower_left_corner, uh);
      Vec3 uuhvv = add_vec3(luh, vv);
      Vec3 minusorig = sub_vec3(uuhvv, origin);
      Ray r = {origin, minusorig};
      color pixel_color = ray_color(r);
      write_color(pixel_color);
    }
  }

  fprintf(stderr, "\nDone.\n");
  return EXIT_SUCCESS;
}
