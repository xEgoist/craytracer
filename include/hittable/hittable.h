#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray/ray.h"
#include "vec3/vec3.h"
#include <stdbool.h>
typedef struct {
  point3 p;
  Vec3 normal;
  double t;
  bool front_face;
} hit_record;

typedef struct {
  point3 center;
  double radius;
} sphere;

void set_face_normal(hit_record *hr, Ray *r, Vec3 outward_normal) {
    if (dot(r->dir,outward_normal) < 0) {
     hr->front_face = true;
    hr->normal = outward_normal;
   } else {
    hr->front_face = false;
    hr->normal = mult_vec3(outward_normal,-1);
    }
}

bool hit(sphere s, Ray *r, double t_min, double t_max, hit_record *rec) {
  Vec3 oc = sub_vec3(r->orig, s.center);
  double a = length_squared(r->dir);
  double half_b = dot(oc, r->dir);
  double c = length_squared(oc) - s.radius * s.radius;
  double discrim = half_b * half_b - a * c;
  if (discrim < 0)
    return false;
  double sqrtd = sqrt(discrim);
  double root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }
  rec->t = root;
  rec->p = at(rec->t, *r);
  Vec3 outward_normal = div_vec3(sub_vec3(rec->p , s.center), s.radius);
   set_face_normal(rec,r,outward_normal);
    return true;
}

#endif
