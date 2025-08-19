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
#ifndef FOSSIL_MATH_GEOM_H
#define FOSSIL_MATH_GEOM_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ======================================================
// Structures
// ======================================================
typedef struct {
    double x;
    double y;
} fossil_math_geom_point2d;

typedef struct {
    double x;
    double y;
    double z;
} fossil_math_geom_point3d;

typedef struct {
    fossil_math_geom_point2d center;
    double radius;
} fossil_math_geom_circle;

typedef struct {
    fossil_math_geom_point3d normal;
    double d; // plane equation: normal·p + d = 0
} fossil_math_geom_plane;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

// ======================================================
// Distance calculations
// ======================================================
double fossil_math_geom_distance2d(fossil_math_geom_point2d a,
                                   fossil_math_geom_point2d b);

double fossil_math_geom_distance3d(fossil_math_geom_point3d a,
                                   fossil_math_geom_point3d b);

// ======================================================
// Circle geometry
// ======================================================
double fossil_math_geom_circle_area(fossil_math_geom_circle c);
double fossil_math_geom_circle_circumference(fossil_math_geom_circle c);
int    fossil_math_geom_point_in_circle(fossil_math_geom_point2d p,
                                        fossil_math_geom_circle c);

// ======================================================
// Triangle geometry
// ======================================================
double fossil_math_geom_triangle_area(fossil_math_geom_point2d a,
                                      fossil_math_geom_point2d b,
                                      fossil_math_geom_point2d c);

double fossil_math_geom_triangle_perimeter(fossil_math_geom_point2d a,
                                           fossil_math_geom_point2d b,
                                           fossil_math_geom_point2d c);

// ======================================================
// Transformations (2D)
// ======================================================
fossil_math_geom_point2d fossil_math_geom_translate2d(fossil_math_geom_point2d p, double dx, double dy);
fossil_math_geom_point2d fossil_math_geom_scale2d(fossil_math_geom_point2d p, double sx, double sy);
fossil_math_geom_point2d fossil_math_geom_rotate2d(fossil_math_geom_point2d p, double angle_rad);

// ======================================================
// Plane geometry (3D)
// ======================================================
double fossil_math_geom_point_plane_distance(fossil_math_geom_point3d p,
                                             fossil_math_geom_plane plane);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

namespace math {



} // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_GEOM_H */
