#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <math.h>

/***************/
/* Definitions */
/***************/

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
    double z;
} vec3;

typedef struct {
    vec3 o; /* Origin */
    vec3 d; /* Direction */
} ray;

typedef enum {
    DIFFUSE,   /* Diffuse */
    SPECULAR,  /* Specular reflection */
    REFRACTIVE /* Dielectric refraction */
} material_t;

typedef struct {
    double radius;       /* Radius of the sphere */
    vec3 position;       /* Position of the sphere center */
    vec3 emission;       /* The emissive color, set to (0, 0, 0) if non-emissive */
    vec3 color;          /* Albedo */
    material_t material; /* Material type */
} sphere;

/* Clamp x to [0, 1] */
double clamp(double x);

/* Apply gamma correction and convert radiance to RGB */
int to_rgb(double x);

/******************/
/* Vec3 Functions */
/******************/

/* Constructor */
vec3 vec3_init(double x, double y, double z);

/* Operator + */
vec3 vec3_add(const vec3 v1, const vec3 v2);

/* Operator - */
vec3 vec3_sub(const vec3 v1, const vec3 v2);

/* Operator * */
vec3 vec3_mulf(const vec3 v, double scale);

/* Operator * */
vec3 vec3_mul(const vec3 v1, const vec3 v2);

/* Get the normalized vector */
vec3 vec3_unit(const vec3 v);

/* Dot product */
double vec3_dot(const vec3 v1, const vec3 v2);

/* Cross product */
vec3 vec3_cross(const vec3 v1, const vec3 v2);

/*****************/
/* Ray Functions */
/*****************/

/* Constructor */
ray ray_init(const vec3 o, const vec3 d);

/* Ray-sphere intersection test, return 0 if no intersection, return the nearest hit time if there are intersections */
double sphere_intersect(const ray *r, const sphere *s);

#endif