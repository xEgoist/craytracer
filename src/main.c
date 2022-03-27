#include "color/color.h"
#include "hittable/consts.h"
#include "hittable/hittable_list.h"
#include "ray/ray.h"
#include "vec3/vec3.h"
#include <stdio.h>
#include <stdlib.h>
#define PROJECT_NAME "craytracer"
const int image_width = 256;
const int image_height = 256;

double hit_sphere(point3 center, double radius, Ray r) {
  Vec3 oc = sub_vec3(r.orig, center);
  double a = length_squared(r.dir);
  double half_b = dot(oc, r.dir);
  double c = length_squared(oc) - radius * radius;
  double discrim = half_b * half_b - a * c;
  if (discrim < 0) {
    return -1.0;
  }
  return (-half_b - sqrt(discrim)) / a;
}

color ray_color(Ray *r, hittable_list *world) {
  hit_record rec;
  if (hit_hittable_list(*world, r, 0, INFINITY, &rec)) {
    return mult_vec3((add_vec3(rec.normal, (color){1, 1, 1})), 0.5);
  }
  Vec3 unit_direction = unit_vector(r->dir);
  double t = 0.5 * (unit_direction.y + 1.0);
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
  hittable_list world = new_hittable_list();
  add_hittable_list(&world, (sphere){(point3){0, 0, -1}, 0.5});
  add_hittable_list(&world, (sphere){(point3){0, -100.5, -1}, 100});
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
      color pixel_color = ray_color(&r, &world);
      write_color(pixel_color);
    }
  }

  fprintf(stderr, "\nDone.\n");
  return EXIT_SUCCESS;
}
