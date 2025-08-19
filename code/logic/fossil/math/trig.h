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
#ifndef FOSSIL_MATH_TRIG_H
#define FOSSIL_MATH_TRIG_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Function prototypes
// *****************************************************************************

// ======================================================
// Conversion
// ======================================================

/**
 * @brief Converts degrees to radians.
 * 
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
double fossil_math_trig_deg_to_rad(double degrees);

/**
 * @brief Converts radians to degrees.
 * 
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
double fossil_math_trig_rad_to_deg(double radians);

// ======================================================
// Basic trig functions
// ======================================================

/**
 * @brief Computes the sine of an angle (in radians).
 * 
 * @param x Angle in radians.
 * @return Sine of the angle.
 */
double fossil_math_trig_sin(double x);

/**
 * @brief Computes the cosine of an angle (in radians).
 * 
 * @param x Angle in radians.
 * @return Cosine of the angle.
 */
double fossil_math_trig_cos(double x);

/**
 * @brief Computes the tangent of an angle (in radians).
 * 
 * @param x Angle in radians.
 * @return Tangent of the angle.
 */
double fossil_math_trig_tan(double x);

// Inverse

/**
 * @brief Computes the arcsine (inverse sine) of a value.
 * 
 * @param x Value whose arcsine is to be computed.
 * @return Angle in radians.
 */
double fossil_math_trig_asin(double x);

/**
 * @brief Computes the arccosine (inverse cosine) of a value.
 * 
 * @param x Value whose arccosine is to be computed.
 * @return Angle in radians.
 */
double fossil_math_trig_acos(double x);

/**
 * @brief Computes the arctangent (inverse tangent) of a value.
 * 
 * @param x Value whose arctangent is to be computed.
 * @return Angle in radians.
 */
double fossil_math_trig_atan(double x);

/**
 * @brief Computes the arctangent of y/x using the signs of the arguments to determine the correct quadrant.
 * 
 * @param y Ordinate value.
 * @param x Abscissa value.
 * @return Angle in radians.
 */
double fossil_math_trig_atan2(double y, double x);

// ======================================================
// Hyperbolic
// ======================================================

/**
 * @brief Computes the hyperbolic sine of a value.
 * 
 * @param x Value whose hyperbolic sine is to be computed.
 * @return Hyperbolic sine of the value.
 */
double fossil_math_trig_sinh(double x);

/**
 * @brief Computes the hyperbolic cosine of a value.
 * 
 * @param x Value whose hyperbolic cosine is to be computed.
 * @return Hyperbolic cosine of the value.
 */
double fossil_math_trig_cosh(double x);

/**
 * @brief Computes the hyperbolic tangent of a value.
 * 
 * @param x Value whose hyperbolic tangent is to be computed.
 * @return Hyperbolic tangent of the value.
 */
double fossil_math_trig_tanh(double x);

// Inverse hyperbolic

/**
 * @brief Computes the inverse hyperbolic sine of a value.
 * 
 * @param x Value whose inverse hyperbolic sine is to be computed.
 * @return Inverse hyperbolic sine of the value.
 */
double fossil_math_trig_asinh(double x);

/**
 * @brief Computes the inverse hyperbolic cosine of a value.
 * 
 * @param x Value whose inverse hyperbolic cosine is to be computed.
 * @return Inverse hyperbolic cosine of the value.
 */
double fossil_math_trig_acosh(double x);

/**
 * @brief Computes the inverse hyperbolic tangent of a value.
 * 
 * @param x Value whose inverse hyperbolic tangent is to be computed.
 * @return Inverse hyperbolic tangent of the value.
 */
double fossil_math_trig_atanh(double x);

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

#endif /* FOSSIL_MATH_TRIG_H */
