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
double fossil_math_trig_deg_to_rad(double degrees);
double fossil_math_trig_rad_to_deg(double radians);

// ======================================================
// Basic trig functions
// ======================================================
double fossil_math_trig_sin(double x);
double fossil_math_trig_cos(double x);
double fossil_math_trig_tan(double x);

// Inverse
double fossil_math_trig_asin(double x);
double fossil_math_trig_acos(double x);
double fossil_math_trig_atan(double x);
double fossil_math_trig_atan2(double y, double x);

// ======================================================
// Hyperbolic
// ======================================================
double fossil_math_trig_sinh(double x);
double fossil_math_trig_cosh(double x);
double fossil_math_trig_tanh(double x);

// Inverse hyperbolic
double fossil_math_trig_asinh(double x);
double fossil_math_trig_acosh(double x);
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
