#ifndef SRAYTRACER_HITABLE_LIST_H_
#define SRAYTRACER_HITABLE_LIST_H_

#include "hitable.h"

class HitableList : public Hitable {
public:
    HitableList() {}
    HitableList(Hitable **list, int n) : list(list), list_size(n) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    Hitable **list;
    int list_size;
};

// check every hitable in the list for collision with ray, trying to find the closest one.
bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord hit;
    bool hit_something = false;
    float closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, hit)) {
            hit_something = true;
            closest_so_far = hit.t;
            rec = hit;
        }
    }
    return hit_something;
}

#endif
