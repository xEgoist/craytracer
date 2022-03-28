#ifndef CAMERA_H
#define CAMERA_H

#include "ray/ray.h"
#include "utils.h"
#include "vec3/vec3.h"
typedef struct camera {
  double aspect_ratio;
  double viewport_height;
  double viewport_width;
  double focal_length;
  point3 origin;
  Vec3 horizontal;
  Vec3 vertical;
  point3 lower_left_corner;
} camera;

camera new_camera() {
  double aspect_ratio = 16.0 / 9.0;
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;
  point3 origin = {0, 0, 0};
  Vec3 horizontal = {viewport_width, 0.0, 0.0};
  Vec3 vertical = {0.0, viewport_height, 0.0};
  point3 lower_left_corner =
      sub_vec3(sub_vec3(sub_vec3(origin, div_vec3(horizontal, 2)),
                        div_vec3(vertical, 2)),
               (Vec3){0, 0, focal_length});
  return (camera){
      aspect_ratio, viewport_height, viewport_width, focal_length,
      origin,       horizontal,      vertical,       lower_left_corner,
  };
}

Ray get_ray(camera cam, double u, double v) {
  Vec3 uh = mult_vec3(cam.horizontal, u);
  Vec3 vv = mult_vec3(cam.vertical, v);
  return (Ray){
      cam.origin,
      sub_vec3(add_vec3(add_vec3(cam.lower_left_corner, uh), vv), cam.origin)};
}

#endif
