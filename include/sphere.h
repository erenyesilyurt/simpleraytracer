#ifndef SRAYTRACER_SPHERE_H_
#define SRAYTRACER_SPHERE_H_

#include "hitable.h"

class Sphere : public Hitable {
public:
    Sphere() {}
    Sphere(vec3 center, float radius, Material *mat) : center(center), radius(radius), material(mat) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    vec3 center;
    float radius;
    Material *material;
};

// Check if ray r hits the sphere within (t_min, t_max). Fill out rec if it does.
bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius*radius;

    float discriminant = b*b - 4*a*c;
    if (discriminant <= 0) {
        // no hit
        return false;
    }

    float hit_params[2] {(-b -sqrt(discriminant)) / (2.0f*a), (-b +sqrt(discriminant)) / (2.0f*a)};

    for(float t : hit_params) {
        if (t < t_max && t > t_min) {
            rec.material = material;
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;

}

#endif