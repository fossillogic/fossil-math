/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/math/math.h"
#include <math.h>
#include <float.h>

// ----------------------------------------------------------------------------
// Basic helpers
// ----------------------------------------------------------------------------

double fossil_math_abs(double x) {
    return (x < 0.0) ? -x : x;
}

double fossil_math_safe_div(double num, double den, double fallback) {
    return (fabs(den) < 1e-12) ? fallback : (num / den);
}

int fossil_math_equal(double a, double b, double eps) {
    return fabs(a - b) <= eps;
}

// ----------------------------------------------------------------------------
// Interpolation and scaling
// ----------------------------------------------------------------------------

double fossil_math_lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

double fossil_math_smoothstep(double edge0, double edge1, double x) {
    x = FOSSIL_MATH_CLAMP((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return x * x * (3 - 2 * x);
}

// ----------------------------------------------------------------------------
// Factorials and combinatorics
// ----------------------------------------------------------------------------

unsigned long long fossil_math_factorial(unsigned int n) {
    if (n == 0) return 1ULL;
    unsigned long long result = 1ULL;
    for (unsigned int i = 1; i <= n; ++i)
        result *= i;
    return result;
}

double fossil_math_binomial(unsigned int n, unsigned int k) {
    if (k > n) return 0.0;
    double num = 1.0;
    double den = 1.0;
    for (unsigned int i = 1; i <= k; ++i) {
        num *= (double)(n - (k - i));
        den *= (double)i;
    }
    return num / den;
}

// ----------------------------------------------------------------------------
// Numeric stability helpers
// ----------------------------------------------------------------------------

double fossil_math_wrap(double x, double min, double max) {
    double range = max - min;
    if (range == 0.0) return min;
    while (x < min) x += range;
    while (x >= max) x -= range;
    return x;
}

double fossil_math_mod(double x, double y) {
    if (y == 0.0) return 0.0;
    double m = fmod(x, y);
    if ((m < 0 && y > 0) || (m > 0 && y < 0)) m += y;
    return m;
}
