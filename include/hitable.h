#ifndef SRAYTRACER_HITABLE_H_
#define SRAYTRACER_HITABLE_H_

#include "ray.h"

class Material;
/*
/ t: hit param
/ p: hit point
/ normal: surface normal at hit point
*/
struct HitRecord {
    float t;
    vec3 p;
    vec3 normal;
    Material *material;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif