#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "bmprinter.h"
#include "material.h"
#include <stdlib.h>


vec3 ray_color(const Ray& r, Hitable *world, int depth)
{
    HitRecord hit_record;
    if (world->hit(r, 0.001f, 10000.0f, hit_record)) {
        Ray scattered;
        vec3 attenuation;
        if (depth < 50 && hit_record.material->scatter(r, hit_record, attenuation, scattered)) {
            return attenuation*ray_color(scattered,world, depth+1);
        }
        else {
            return vec3(0, 0, 0);
        }

    }
    
    //return vec3(0.251f, 0.612f, 1.0f);
    return vec3(1,1,1);
}

int main()
{
    int w = 800, h = 600;
    int number_of_samples = 200;
    vec3 top_left_corner(-2.0f, 1.0f, -1.0f);
    vec3 horizontal(4.0f, 0, 0);
    vec3 vertical(0, 2.0f, 0);
    vec3 origin(0, 0, 0);

    Hitable *list[4];
    list[0] = new Sphere(vec3(-0.7, 0, 0.2), 0.5, new Lambertian(vec3(0.1,0.1,0.9)));
    list[1] = new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.9,0.9, 0.9)));
    list[2] = new Sphere(vec3(1, 0, 0), 0.5, new Metal(vec3(0.9, 0.4, 0.2), 0.3));
    list[3] = new Sphere(vec3(0, 0, -0.5), 0.5, new Metal(vec3(0.4, 0.4, 0.4), 0.1));
    Hitable *world = new HitableList(list, 4);
    Camera camera(vec3(0,0,2), vec3(0,0,-1), vec3(0,1,0), 60.0f, float(w)/h);
    BMPImage im(w, h);

    srand(524071);


    for (int j = h-1; j>=0; j--) {
        for (int i = 0; i<w; i++) {
            vec3 color(0, 0, 0);
            for (int s = 0; s < number_of_samples; s++) {
                float u = float(i + (float)rand()/RAND_MAX) / w; // horizontal offset
                float v = 1.0f - (float(j + (float)rand()/RAND_MAX) / h);
                Ray ray = camera.get_ray(u, v);
                color += ray_color(ray, world, 0);
            }

            color /= number_of_samples;
            // gamma correction: 2
            color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            vec3 color_out = color * 255.99;
            im.put((int)color_out.r(), (int)color_out.g(), (int)color_out.b(), i, j);          
        }
    }


    im.save("out.bmp");
    return 0;
}