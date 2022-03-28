#include "color/color.h"
#include "hittable/hittable_list.h"
#include "ray/ray.h"
#include "utils/camera.h"
#include "utils/utils.h"
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
  // IMAGE
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)((double)image_width / aspect_ratio);
  int sample_per_pixel = 100;
  // WORLD
  hittable_list world = new_hittable_list();
  add_hittable_list(&world, (sphere){(point3){0, 0, -1}, 0.5});
  add_hittable_list(&world, (sphere){(point3){0, -100.5, -1}, 100});
  // CAMERA
  camera cam = new_camera();

  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height - 1; j >= 0; --j) {
    fprintf(stderr, "\rScanLines Remaining: %d ", j);
    fflush(stderr);
    for (int i = 0; i < image_width; ++i) {
      color pixel_color = {0, 0, 0};
      for (int s = 0; s < sample_per_pixel; ++s) {
        double u = ((double)i + random_double()) / (image_width - 1);
        double v = ((double)j + random_double()) / (image_height - 1);
        Ray r = get_ray(cam, u, v);
        pixel_color = add_vec3(pixel_color, ray_color(&r, &world));
      }
      write_color(pixel_color, sample_per_pixel);
    }
  }

  fprintf(stderr, "\nDone.\n");
  return EXIT_SUCCESS;
}
