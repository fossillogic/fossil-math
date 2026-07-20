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
#include "fossil/math/calc.h"
#include <math.h>

// ==========================================================
// Derivatives
// ==========================================================

double fossil_math_calc_derivative(fossil_math_func_t f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

double fossil_math_calc_derivative_n(fossil_math_func_t f, double x, int n, double h) {
    if (n == 0) return f(x);
    if (n < 0) return NAN; // Invalid order

    // Use central difference for n-th derivative (finite difference method)
    double result = 0.0;
    int sign = 1;
    for (int k = 0; k <= n; ++k) {
        // Binomial coefficient
        int coeff = 1;
        for (int i = 0; i < k; ++i) coeff *= (n - i);
        for (int i = 1; i <= k; ++i) coeff /= i;
        result += sign * coeff * f(x + (n - 2 * k) * h);
        sign = -sign;
    }
    double denom = pow(2.0 * h, n);
    return result / denom;
}

// ==========================================================
// Integrals
// ==========================================================

double fossil_math_calc_integrate_trapezoidal(fossil_math_func_t f, double a, double b, size_t n) {
    if (n == 0) return 0.0;
    double h = (b - a) / (double)n;
    double sum = 0.5 * (f(a) + f(b));
    for (size_t i = 1; i < n; ++i) sum += f(a + i * h);
    return sum * h;
}

double fossil_math_calc_integrate_simpson(fossil_math_func_t f, double a, double b, size_t n) {
    if (n % 2) n++;  // Ensure even number of intervals
    double h = (b - a) / (double)n;
    double sum = f(a) + f(b);
    for (size_t i = 1; i < n; ++i)
        sum += f(a + i * h) * (i % 2 ? 4.0 : 2.0);
    return sum * h / 3.0;
}

double fossil_math_calc_integrate_montecarlo(fossil_math_func_t f, double a, double b, size_t samples) {
    double sum = 0.0;
    for (size_t i = 0; i < samples; ++i) {
        double x = a + (b - a) * (rand() / (double)RAND_MAX);
        sum += f(x);
    }
    return (b - a) * sum / (double)samples;
}

// ==========================================================
// Limits
// ==========================================================

double fossil_math_calc_limit(fossil_math_func_t f, double x, double h) {
    return (f(x + h) + f(x - h)) / 2.0;
}

// ==========================================================
// Roots
// ==========================================================

double fossil_math_calc_root_newton(fossil_math_func_t f, fossil_math_func_t df, double x0, double tol, size_t max_iter) {
    double x = x0;
    for (size_t i = 0; i < max_iter; ++i) {
        double y = f(x);
        double dy = df(x);
        if (fabs(dy) < 1e-12) break;
        double x_next = x - y / dy;
        if (fabs(x_next - x) < tol) return x_next;
        x = x_next;
    }
    return x;
}

double fossil_math_calc_root_bisection(fossil_math_func_t f, double a, double b, double tol, size_t max_iter) {
    double fa = f(a), fb = f(b);
    if (fa * fb > 0.0) return NAN;
    for (size_t i = 0; i < max_iter; ++i) {
        double c = 0.5 * (a + b);
        double fc = f(c);
        if (fabs(fc) < tol || (b - a) / 2 < tol) return c;
        if (fa * fc < 0.0) { b = c; fb = fc; } else { a = c; fa = fc; }
    }
    return 0.5 * (a + b);
}

// ==========================================================
// Multivariable
// ==========================================================

void fossil_math_calc_gradient(fossil_math_func_t* funcs, const double* x, double* grad, size_t dim, double h) {
    for (size_t i = 0; i < dim; ++i)
        grad[i] = fossil_math_calc_partial(funcs[i], x, i, h);
}

double fossil_math_calc_partial(fossil_math_func_t f, const double* x, size_t i, double h) {
    double xi = x[i];
    double forward = xi + h;
    double backward = xi - h;
    return (f(forward) - f(backward)) / (2.0 * h);
}
