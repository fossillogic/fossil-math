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
#include "fossil/math/numeric.h"
#include <math.h>
#include <float.h>

// ============================================================================
// Integration
// ============================================================================

/**
 * @brief Trapezoidal rule implementation.
 */
double fossil_math_numeric_integrate_trapezoidal(fossil_func_t f, double a, double b, int steps) {
    if (!f || steps <= 0 || fossil_math_equal(a, b, DBL_EPSILON)) return 0.0;

    double h = fossil_math_safe_div(b - a, (double)steps, 0.0);
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < steps; ++i)
        sum += f(a + i * h);

    return sum * h;
}

/**
 * @brief Simpson's rule implementation.
 */
double fossil_math_numeric_integrate_simpson(fossil_func_t f, double a, double b, int steps) {
    if (!f || steps <= 0 || fossil_math_equal(a, b, DBL_EPSILON)) return 0.0;
    if (steps % 2) steps++; // Simpson's rule requires even steps

    double h = fossil_math_safe_div(b - a, (double)steps, 0.0);
    double sum = f(a) + f(b);

    for (int i = 1; i < steps; i += 2)
        sum += 4.0 * f(a + i * h);
    for (int i = 2; i < steps; i += 2)
        sum += 2.0 * f(a + i * h);

    return sum * h / 3.0;
}

/**
 * @brief Romberg integration implementation.
 */
double fossil_math_numeric_integrate_romberg(fossil_func_t f, double a, double b, int steps) {
    if (!f || steps <= 0 || fossil_math_equal(a, b, DBL_EPSILON)) return 0.0;
    int k, j;
    // Limit the maximum value of k to prevent N from overflowing
    int max_k = 20; // Limit k so that N = 1 << 20 = 1048576 (safe for memory and loop)
    int n = steps > max_k ? max_k : steps;
    double **R = (double **)malloc((n + 1) * sizeof(double *));
    if (!R) return 0.0;
    for (k = 0; k <= n; ++k) {
        R[k] = (double *)malloc((n + 1) * sizeof(double));
        if (!R[k]) {
            // Free previously allocated memory on failure
            for (int m = 0; m < k; ++m) free(R[m]);
            free(R);
            return 0.0;
        }
        // Initialize all elements to zero to avoid undefined behavior
        for (j = 0; j <= n; ++j) R[k][j] = 0.0;
    }

    for (k = 0; k <= n; ++k) {
        size_t N = 1 << k;
        if (N > 1048575) N = 1048575; // fallback to max safe N (prevent overflow)
        double h = fossil_math_safe_div(b - a, (double)N, 0.0);
        double sum = 0.5 * (f(a) + f(b));
        // Ensure N does not exceed SIZE_MAX and loop is safe
        // Limit N to avoid undefined behavior on platforms with aggressive optimizations
        size_t safe_N = N > 1048575 ? 1048575 : N;
        for (size_t i = 1; i <= safe_N; ++i)
            sum += f(a + i * h);
        R[k][0] = sum * h;
        for (j = 1; j <= k; ++j) {
            if (k > 0) {
                R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j) - 1);
            }
        }
    }
    double result = R[n][n];
    for (k = 0; k <= n; ++k)
        free(R[k]);
    free(R);
    return result;
}

/**
 * @brief Numeric integration with selectable precision mode.
 */
double fossil_math_numeric_integrate(fossil_func_t f, double a, double b, int steps, fossil_numeric_mode_t mode) {
    switch (mode) {
        case FOSSIL_NUMERIC_SIMPSON:
            return fossil_math_numeric_integrate_simpson(f, a, b, steps);
        case FOSSIL_NUMERIC_ROMBERG:
            return fossil_math_numeric_integrate_romberg(f, a, b, FOSSIL_MATH_MIN(steps, 6)); // Limit Romberg depth
        case FOSSIL_NUMERIC_TRAPEZOIDAL:
        default:
            return fossil_math_numeric_integrate_trapezoidal(f, a, b, steps);
    }
}

// ============================================================================
// Derivative
// ============================================================================

/**
 * @brief Central difference derivative approximation.
 */
double fossil_math_numeric_derivative(fossil_func_t f, double x, double h) {
    if (!f || h <= 0.0) return NAN;
    return fossil_math_safe_div(f(x + h) - f(x - h), 2.0 * h, NAN);
}

// ============================================================================
// Root Finding
// ============================================================================

/**
 * @brief Newton-Raphson method for root finding.
 */
double fossil_math_numeric_solve(fossil_func_t f, double guess, double tol, int max_iter) {
    if (!f || max_iter <= 0 || tol <= 0.0) return NAN;

    double x = guess;
    double h = 1e-6; // Step for derivative estimation
    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = fossil_math_safe_div(f(x + h) - f(x - h), 2.0 * h, NAN);
        if (fabs(dfx) < DBL_EPSILON) break;

        double x_next = x - fossil_math_safe_div(fx, dfx, 0.0);
        if (fabs(x_next - x) < tol)
            return x_next;
        x = x_next;
    }
    return x;
}

// ============================================================================
// Linear Interpolation
// ============================================================================

/**
 * @brief Linear interpolation between two known points.
 */
double fossil_math_numeric_interpolate(double x0, double y0, double x1, double y1, double x) {
    if (fossil_math_equal(x1, x0, DBL_EPSILON)) return NAN;
    double t = fossil_math_safe_div(x - x0, x1 - x0, 0.0);
    return fossil_math_lerp(y0, y1, t);
}
