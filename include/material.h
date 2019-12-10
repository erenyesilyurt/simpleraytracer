#ifndef SRAYTRACER_MATERIAL_H_
#define SRAYTRACER_MATERIAL_H_

#include "hitable.h"

class Material {
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& record, vec3& attenuation, Ray& scattered) const = 0;
};

float rand_normalized()
{
    return (float)rand()/RAND_MAX;
}

inline vec3 random_in_unit_sphere() 
{
    vec3 p;
    do {
        p = 2.0f*vec3(rand_normalized(), rand_normalized(), rand_normalized()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0f);
    return p;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v, n)*n;
}

class Metal : public Material {
public:
    Metal(const vec3& a, float fuzziness) : albedo(a) {
        if (fuzziness < 1)
            fuzz = fuzziness;
        else
            fuzz = 1;
    }
    virtual bool scatter(const Ray& r_in, const HitRecord& record, vec3& attenuation, Ray& scattered) const
    {
        vec3 reflected = reflect(r_in.direction(), record.normal);
        scattered = Ray(record.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), record.normal) > 0);
    }

    vec3 albedo;
    float fuzz;
};

class Lambertian : public Material {
public:
    Lambertian(const vec3& a): albedo(a) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& record, vec3& attenuation, Ray& scattered) const
    {
        vec3 target = record.p + record.normal + random_in_unit_sphere();
        scattered = Ray(record.p, target-record.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};

#endif