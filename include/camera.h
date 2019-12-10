#ifndef SRAYTRACER_CAMERA_H_
#define SRAYTRACER_CAMERA_H_

#include "ray.h"

class Camera {
public:
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vertical_fov, float aspect_ratio)
    {
        vec3 u, v, w;
        float theta = vertical_fov*M_PI/180; // convert to radians
        float half_height = tan(theta/2);
        float half_width = aspect_ratio * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width*u - half_height*v - w;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
    }
    
    Ray get_ray(float u, float v) {
        return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
    vec3 lower_left_corner;
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
};

#endif