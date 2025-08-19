/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/math/geom.h"
#include <math.h>

// ======================================================
// Distance
// ======================================================
double fossil_math_geom_distance2d(fossil_math_geom_point2d a,
                                   fossil_math_geom_point2d b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double fossil_math_geom_distance3d(fossil_math_geom_point3d a,
                                   fossil_math_geom_point3d b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// ======================================================
// Circle
// ======================================================
double fossil_math_geom_circle_area(fossil_math_geom_circle c) {
    return FOSSIL_MATH_PI * c.radius * c.radius;
}

double fossil_math_geom_circle_circumference(fossil_math_geom_circle c) {
    return 2.0 * FOSSIL_MATH_PI * c.radius;
}

int fossil_math_geom_point_in_circle(fossil_math_geom_point2d p,
                                     fossil_math_geom_circle c) {
    return fossil_math_geom_distance2d(p, c.center) <= c.radius;
}

// ======================================================
// Triangle
// ======================================================
double fossil_math_geom_triangle_area(fossil_math_geom_point2d a,
                                      fossil_math_geom_point2d b,
                                      fossil_math_geom_point2d c) {
    return fabs(0.5 * (a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y)));
}

double fossil_math_geom_triangle_perimeter(fossil_math_geom_point2d a,
                                           fossil_math_geom_point2d b,
                                           fossil_math_geom_point2d c) {
    return fossil_math_geom_distance2d(a, b)
         + fossil_math_geom_distance2d(b, c)
         + fossil_math_geom_distance2d(c, a);
}

// ======================================================
// 2D Transformations
// ======================================================
fossil_math_geom_point2d fossil_math_geom_translate2d(fossil_math_geom_point2d p, double dx, double dy) {
    p.x += dx;
    p.y += dy;
    return p;
}

fossil_math_geom_point2d fossil_math_geom_scale2d(fossil_math_geom_point2d p, double sx, double sy) {
    p.x *= sx;
    p.y *= sy;
    return p;
}

fossil_math_geom_point2d fossil_math_geom_rotate2d(fossil_math_geom_point2d p, double angle_rad) {
    double cos_a = cos(angle_rad);
    double sin_a = sin(angle_rad);
    fossil_math_geom_point2d result;
    result.x = p.x * cos_a - p.y * sin_a;
    result.y = p.x * sin_a + p.y * cos_a;
    return result;
}

// ======================================================
// Plane (3D)
// ======================================================
double fossil_math_geom_point_plane_distance(fossil_math_geom_point3d p,
                                             fossil_math_geom_plane plane) {
    double num = fabs(plane.normal.x * p.x +
                      plane.normal.y * p.y +
                      plane.normal.z * p.z + plane.d);
    double denom = sqrt(plane.normal.x * plane.normal.x +
                        plane.normal.y * plane.normal.y +
                        plane.normal.z * plane.normal.z);
    return num / denom;
}
