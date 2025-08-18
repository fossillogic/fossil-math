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
#include "fossil/math/trig.h"
#include <math.h>

// ======================================================
// Conversion
// ======================================================
double fossil_math_trig_deg_to_rad(double degrees) {
    return degrees * (FOSSIL_MATH_PI / 180.0);
}

double fossil_math_trig_rad_to_deg(double radians) {
    return radians * (180.0 / FOSSIL_MATH_PI);
}

// ======================================================
// Basic trig
// ======================================================
double fossil_math_trig_sin(double x) { return sin(x); }
double fossil_math_trig_cos(double x) { return cos(x); }
double fossil_math_trig_tan(double x) { return tan(x); }

// Inverse
double fossil_math_trig_asin(double x) { return asin(x); }
double fossil_math_trig_acos(double x) { return acos(x); }
double fossil_math_trig_atan(double x) { return atan(x); }
double fossil_math_trig_atan2(double y, double x) { return atan2(y, x); }

// ======================================================
// Hyperbolic
// ======================================================
double fossil_math_trig_sinh(double x) { return sinh(x); }
double fossil_math_trig_cosh(double x) { return cosh(x); }
double fossil_math_trig_tanh(double x) { return tanh(x); }

// Inverse hyperbolic
double fossil_math_trig_asinh(double x) { return asinh(x); }
double fossil_math_trig_acosh(double x) { return acosh(x); }
double fossil_math_trig_atanh(double x) { return atanh(x); }
