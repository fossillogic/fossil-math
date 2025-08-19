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

/** 
 * ======================================================
 * Distance calculations
 * ======================================================
 */

/**
 * @brief Calculates the Euclidean distance between two 2D points.
 * 
 * @param a First 2D point.
 * @param b Second 2D point.
 * @return Distance between points a and b.
 */
double fossil_math_geom_distance2d(fossil_math_geom_point2d a,
                                   fossil_math_geom_point2d b);

/**
 * @brief Calculates the Euclidean distance between two 3D points.
 * 
 * @param a First 3D point.
 * @param b Second 3D point.
 * @return Distance between points a and b.
 */
double fossil_math_geom_distance3d(fossil_math_geom_point3d a,
                                   fossil_math_geom_point3d b);

/** 
 * ======================================================
 * Circle geometry
 * ======================================================
 */

/**
 * @brief Calculates the area of a circle.
 * 
 * @param c Circle structure.
 * @return Area of the circle.
 */
double fossil_math_geom_circle_area(fossil_math_geom_circle c);

/**
 * @brief Calculates the circumference of a circle.
 * 
 * @param c Circle structure.
 * @return Circumference of the circle.
 */
double fossil_math_geom_circle_circumference(fossil_math_geom_circle c);

/**
 * @brief Checks if a 2D point lies inside or on the boundary of a circle.
 * 
 * @param p 2D point.
 * @param c Circle structure.
 * @return 1 if the point is inside or on the circle, 0 otherwise.
 */
int fossil_math_geom_point_in_circle(fossil_math_geom_point2d p,
                                     fossil_math_geom_circle c);

/** 
 * ======================================================
 * Triangle geometry
 * ======================================================
 */

/**
 * @brief Calculates the area of a triangle given its three vertices.
 * 
 * @param a First vertex of the triangle.
 * @param b Second vertex of the triangle.
 * @param c Third vertex of the triangle.
 * @return Area of the triangle.
 */
double fossil_math_geom_triangle_area(fossil_math_geom_point2d a,
                                      fossil_math_geom_point2d b,
                                      fossil_math_geom_point2d c);

/**
 * @brief Calculates the perimeter of a triangle given its three vertices.
 * 
 * @param a First vertex of the triangle.
 * @param b Second vertex of the triangle.
 * @param c Third vertex of the triangle.
 * @return Perimeter of the triangle.
 */
double fossil_math_geom_triangle_perimeter(fossil_math_geom_point2d a,
                                           fossil_math_geom_point2d b,
                                           fossil_math_geom_point2d c);

/** 
 * ======================================================
 * Transformations (2D)
 * ======================================================
 */

/**
 * @brief Translates a 2D point by given offsets.
 * 
 * @param p The point to translate.
 * @param dx Offset along the x-axis.
 * @param dy Offset along the y-axis.
 * @return Translated 2D point.
 */
fossil_math_geom_point2d fossil_math_geom_translate2d(fossil_math_geom_point2d p, double dx, double dy);

/**
 * @brief Scales a 2D point by given scale factors.
 * 
 * @param p The point to scale.
 * @param sx Scale factor along the x-axis.
 * @param sy Scale factor along the y-axis.
 * @return Scaled 2D point.
 */
fossil_math_geom_point2d fossil_math_geom_scale2d(fossil_math_geom_point2d p, double sx, double sy);

/**
 * @brief Rotates a 2D point around the origin by a given angle (in radians).
 * 
 * @param p The point to rotate.
 * @param angle_rad Angle in radians.
 * @return Rotated 2D point.
 */
fossil_math_geom_point2d fossil_math_geom_rotate2d(fossil_math_geom_point2d p, double angle_rad);

/** 
 * ======================================================
 * Plane geometry (3D)
 * ======================================================
 */

/**
 * @brief Calculates the shortest distance from a 3D point to a plane.
 * 
 * @param p The 3D point.
 * @param plane The plane structure.
 * @return Distance from the point to the plane.
 */
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
