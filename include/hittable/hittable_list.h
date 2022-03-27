#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <stdlib.h>
typedef struct hittable_list {
    sphere* objects;
    long idx;
    long size;
}hittable_list;

void add_hittable_list(hittable_list *hl, sphere obj) {
    *(hl->objects+(hl->idx)) = obj;
    hl->idx+=1;
}
void clear_hittable_list(hittable_list *hl) {
    free(hl->objects);
    hl-> objects = calloc(600,sizeof(sphere));
}

hittable_list new_hittable_list() {
    return (hittable_list) {
    calloc(600, sizeof(sphere)),
    0,
    600*sizeof(sphere),
    };
}

bool hit_hittable_list(hittable_list hl, Ray *r, double t_min, double t_max,
hit_record *hr){
hit_record temp_rec;
bool hit_anything = false;
double closest_so_far = t_max;

for (long i = 0;i < hl.idx; i++) {
    if (hit(hl.objects[i],r,t_min,closest_so_far,&temp_rec)){
    hit_anything = true;
    closest_so_far = temp_rec.t;
    *hr = temp_rec;
    }

}

return hit_anything; }

#endif 
