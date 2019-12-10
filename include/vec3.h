#ifndef SRAYTRACER_VEC3_H_
#define SRAYTRACER_VEC3_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>


class vec3 {
public:
    vec3() {}
    vec3(float e1, float e2, float e3) : e{e1, e2, e3} {}
    float x() { return e[0]; }
    float y() { return e[1]; }
    float z() { return e[2]; }
    float r() { return e[0]; }
    float g() { return e[1]; }
    float b() { return e[2]; }
    
    const vec3& operator+() const { return *this; }
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v2);
    vec3& operator-=(const vec3 &v2);
    vec3& operator*=(const vec3 &v2);
    vec3& operator/=(const vec3 &v2);
    vec3& operator*=(const float t);
    vec3& operator/=(const float t);

    float length() const {
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    float squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    void make_unit_vector();

    float e[3];
};

inline std::istream& operator>>(std::istream &is, vec3 t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void vec3::make_unit_vector() {
    float k = 1.0 / length();
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(const vec3 &v, float t) {
    return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3(
        (v1.e[1]*v2.e[2] - v1.e[2] * v2.e[1]),
        (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
        (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])
    );
}

inline vec3& vec3::operator+=(const vec3 &v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];

    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];

    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];

    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];

    return *this;
}

inline vec3& vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

inline vec3& vec3::operator/=(const float t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;

    return *this;
}

inline vec3 unit_vector(vec3 v) 
{
    float t = 1.0f / v.length();
    return v * t;
}

inline vec3 normalize(vec3 &v, float min_value, float max_value)
{
    v.e[0] -= min_value;
    v.e[1] -= min_value;
    v.e[2] -= min_value;

    return v / (max_value - min_value);
}

#endif