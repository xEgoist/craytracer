#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

Vec3 add_vec3(Vec3 rhs, Vec3 lhs) {
  return (Vec3){
      rhs.x += lhs.x,
      rhs.y += lhs.y,
      rhs.z += lhs.z,
  };
}
Vec3 mult_vec3(Vec3 v, double t) {
  return (Vec3){v.x * t, v.y * t, v.z * t};
}
Vec3 div_vec3(Vec3 v, double t) { return mult_vec3(v, 1 / t); }
double length_squared(Vec3 v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
double length(Vec3 v) { return sqrt(length_squared(v)); }
typedef Vec3 point3;
typedef Vec3 color;

void print_vec3(Vec3 v) {
  printf("%f %f %f", v.x, v.y, v.z);
  return;
}

Vec3 sub_vec3(Vec3 rhs, Vec3 lhs) {
  return (Vec3) {
  rhs.x -= lhs.x,
  rhs.y -= lhs.y,
  rhs.z -= lhs.z,

  };
}

Vec3 multi_vec3(Vec3 v, Vec3 u) {
  return (Vec3){
  v.x *= u.x,
  v.y *= u.y,
  v.z *= u.z,
  };
}

double dot(Vec3 v, Vec3 u) { return u.x * v.x + u.y * v.y + u.z * v.z; }
Vec3 cross(Vec3 v, Vec3 u) {
  return (Vec3){
      v.y * u.z - v.y * u.x,
      v.y * u.x - v.x * u.y,
      v.x * u.y - v.y * v.x,
  };
}
Vec3 unit_vector(Vec3 v) { return div_vec3(v, length(v)); }
#endif
