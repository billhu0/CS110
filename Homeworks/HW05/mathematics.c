#include "mathematics.h"

/*********************/
/* Utility Functions */
/*********************/

/* Clamp x to [0, 1] */
double clamp(double x) {
    return x < 0 ? 0 : x > 1 ? 1 : x;
}

/* Apply gamma correction and convert radiance to RGB */
int to_rgb(double x) {
    return (int)(pow(clamp(x), 1 / 2.2) * 255 + .5);
}

/******************/
/* Vec3 Functions */
/******************/

/* Constructor */
vec3 vec3_init(double x, double y, double z) {
    vec3 res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}
/* Operator + */
vec3 vec3_add(const vec3 v1, const vec3 v2) {
    vec3 res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return res;
}
/* Operator - */
vec3 vec3_sub(const vec3 v1, const vec3 v2) {
    vec3 res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return res;
}
/* Operator * */
vec3 vec3_mulf(const vec3 v, double scale) {
    vec3 res;
    res.x = v.x * scale;
    res.y = v.y * scale;
    res.z = v.z * scale;
    return res;
}
/* Operator * */
vec3 vec3_mul(const vec3 v1, const vec3 v2) {
    vec3 res;
    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;
    res.z = v1.z * v2.z;
    return res;
}
/* Get the normalized vector */
vec3 vec3_unit(const vec3 v) {
    return vec3_mulf(v, (double)1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
/* Dot product */
double vec3_dot(const vec3 v1, const vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
/* Cross product */
vec3 vec3_cross(const vec3 v1, const vec3 v2) {
    vec3 res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return res;
}

/*****************/
/* Ray Functions */
/*****************/

/* Constructor */
ray ray_init(const vec3 o, const vec3 d) {
    ray res;
    res.o = o;
    res.d = d;
    return res;
}

/* Ray-sphere intersection test, return 0 if no intersection, return the nearest hit time if there are intersections */
double sphere_intersect(const ray *r, const sphere *s) {
    const double epsilon = 1e-4;
    vec3 dist = vec3_sub(s->position, r->o);
    double b = vec3_dot(dist, r->d);
    double det = b * b - vec3_dot(dist, dist) + s->radius * s->radius;
    double t;
    if (det < 0)
        return 0;
    det = sqrt(det);
    return (t = b - det) > epsilon ? t : ((t = b + det) > epsilon ? t : 0);
}