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
#ifndef FOSSIL_MATH_NUMERIC_H
#define FOSSIL_MATH_NUMERIC_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * -----------------------------------------------------------------------------
 * Numeric function pointer type for single-variable double functions.
 *
 * This typedef defines a function pointer type for functions that take a single
 * double argument and return a double value. It is commonly used for passing
 * mathematical functions to numerical algorithms such as integration, differentiation,
 * root finding, and interpolation.
 *
 * Example usage:
 *     double my_func(double x) { return x * x; }
 *     fossil_func_t f = my_func;
 */
typedef double (*fossil_func_t)(double);

/**
 * @brief Enumeration for selecting numeric integration precision modes.
 *
 * This enum defines the available precision modes for numeric integration methods.
 * It allows users to choose between different algorithms based on their accuracy
 * and performance requirements.
 *
 * - FOSSIL_NUMERIC_TRAPEZOIDAL: Uses the trapezoidal rule for integration, which is
 *   simple and efficient but may be less accurate for functions with high curvature.
 *
 * - FOSSIL_NUMERIC_SIMPSON: Uses Simpson's rule, which provides better accuracy by
 *   approximating the function with parabolic segments. It requires an even number
 *   of intervals.
 *
 * - FOSSIL_NUMERIC_ROMBERG: Uses Romberg integration, which combines the trapezoidal
 *   rule with Richardson extrapolation for high accuracy. It is more computationally
 *   intensive and is suitable for functions that are smooth over the integration interval.
 */

typedef enum {
    FOSSIL_NUMERIC_TRAPEZOIDAL,
    FOSSIL_NUMERIC_SIMPSON,
    FOSSIL_NUMERIC_ROMBERG
} fossil_numeric_mode_t;

// ============================================================================
// Integration
// ============================================================================

/**
 * @brief Approximates the definite integral of a function using the trapezoidal rule.
 *
 * This function numerically integrates the given function pointer `f` over the interval [a, b]
 * using the trapezoidal rule with the specified number of subdivisions (`steps`). The trapezoidal
 * rule approximates the area under the curve by dividing it into trapezoids and summing their areas.
 *
 * @param f Function to integrate (takes a double and returns a double).
 * @param a Lower bound of integration.
 * @param b Upper bound of integration.
 * @param steps Number of subdivisions for the interval.
 * @return Approximate value of the definite integral of f over [a, b].
 */
double fossil_math_numeric_integrate_trapezoidal(fossil_func_t f, double a, double b, int steps);

/**
 * @brief Approximates the definite integral of a function using Simpson's rule.
 *
 * This function numerically integrates the given function pointer `f` over the interval [a, b]
 * using Simpson's rule with the specified number of subdivisions (`steps`). Simpson's rule provides
 * a higher-order approximation by fitting parabolas to segments of the curve.
 *
 * @param f Function to integrate (takes a double and returns a double).
 * @param a Lower bound of integration.
 * @param b Upper bound of integration.
 * @param steps Number of subdivisions for the interval (should be even).
 * @return Approximate value of the definite integral of f over [a, b].
 */
double fossil_math_numeric_integrate_simpson(fossil_func_t f, double a, double b, int steps);

/**
 * @brief Approximates the definite integral of a function using Romberg integration.
 *
 * This function numerically integrates the given function pointer `f` over the interval [a, b]
 * using Romberg integration, which combines the trapezoidal rule with Richardson extrapolation
 * for improved accuracy.
 *
 * @param f Function to integrate (takes a double and returns a double).
 * @param a Lower bound of integration.
 * @param b Upper bound of integration.
 * @param steps Number of subdivisions for the interval.
 * @return Approximate value of the definite integral of f over [a, b].
 */
double fossil_math_numeric_integrate_romberg(fossil_func_t f, double a, double b, int steps);

/**
 * @brief Numerically integrates a function over an interval with selectable precision mode.
 *
 * This function provides a unified interface for numeric integration, allowing the caller
 * to select the desired precision mode (e.g., trapezoidal, Simpson, Romberg) via the
 * `mode` parameter.
 *
 * @param f Function to integrate (takes a double and returns a double).
 * @param a Lower bound of integration.
 * @param b Upper bound of integration.
 * @param steps Number of subdivisions for the interval.
 * @param mode Precision mode for integration (e.g., trapezoidal, Simpson, Romberg).
 * @return Approximate value of the definite integral of f over [a, b].
 */
double fossil_math_numeric_integrate(fossil_func_t f, double a, double b, int steps, fossil_numeric_mode_t mode);

// ============================================================================
// Derivative
// ============================================================================

/**
 * @brief Approximates the derivative of a function at a point using central difference.
 *
 * This function computes the numerical derivative of the given function pointer `f` at the
 * specified point `x` using the central difference method with a small increment `h`.
 *
 * @param f Function whose derivative is to be computed (takes a double and returns a double).
 * @param x Point at which to compute the derivative.
 * @param h Small increment for finite difference.
 * @return Approximate derivative of f at x.
 */
double fossil_math_numeric_derivative(fossil_func_t f, double x, double h);

// ============================================================================
// Root Finding
// ============================================================================

/**
 * @brief Attempts to find a root of the function near an initial guess using Newton-Raphson.
 *
 * This function applies the Newton-Raphson method to find a root of the given function pointer `f`
 * near the initial guess `guess`. The process iterates until the result converges within the
 * specified tolerance `tol` or the maximum number of iterations `max_iter` is reached.
 *
 * @param f Function whose root is to be found (takes a double and returns a double).
 * @param guess Initial guess for the root.
 * @param tol Tolerance for convergence.
 * @param max_iter Maximum number of iterations.
 * @return Approximate root of f near the initial guess.
 */
double fossil_math_numeric_solve(fossil_func_t f, double guess, double tol, int max_iter);

// ============================================================================
// Linear Interpolation
// ============================================================================

/**
 * @brief Computes the interpolated y-value at a given x, using two known points.
 *
 * This function performs linear interpolation between two known points (`x0`, `y0`) and (`x1`, `y1`)
 * to estimate the y-value at a given x. The result is computed using the formula for linear interpolation.
 *
 * @param x0 First x-coordinate.
 * @param y0 First y-coordinate.
 * @param x1 Second x-coordinate.
 * @param y1 Second y-coordinate.
 * @param x The x-value at which to interpolate.
 * @return Interpolated y-value at x.
 */
double fossil_math_numeric_interpolate(double x0, double y0, double x1, double y1, double x);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

    namespace math {

        /**
         * @brief Numeric utility class providing static methods for common numerical operations.
         *
         * This class wraps the C numeric functions in a C++-friendly interface,
         * allowing for easier use in C++ codebases. All methods are static and
         * operate directly on the provided function pointers or values.
         */
        class Numeric {
        public:
            /**
             * @brief Approximates the definite integral of a function using the trapezoidal rule.
             *
             * This method computes the numerical integral of the provided function pointer `f`
             * over the interval [a, b] using the trapezoidal rule. The interval is divided into
             * `steps` subdivisions, and the area under the curve is estimated by summing the
             * areas of the resulting trapezoids.
             *
             * @param f Function to integrate (takes a double and returns a double).
             * @param a Lower bound of integration.
             * @param b Upper bound of integration.
             * @param steps Number of subdivisions for the interval.
             * @return Approximate value of the definite integral of f over [a, b].
             */
            static double integrateTrapezoidal(fossil_func_t f, double a, double b, int steps) {
            return fossil_math_numeric_integrate_trapezoidal(f, a, b, steps);
            }

            /**
             * @brief Approximates the definite integral of a function using Simpson's rule.
             *
             * This method computes the numerical integral of the provided function pointer `f`
             * over the interval [a, b] using Simpson's rule. The interval is divided into
             * `steps` subdivisions (should be even), and the integral is estimated by fitting
             * parabolas to segments of the curve.
             *
             * @param f Function to integrate (takes a double and returns a double).
             * @param a Lower bound of integration.
             * @param b Upper bound of integration.
             * @param steps Number of subdivisions for the interval (should be even).
             * @return Approximate value of the definite integral of f over [a, b].
             */
            static double integrateSimpson(fossil_func_t f, double a, double b, int steps) {
            return fossil_math_numeric_integrate_simpson(f, a, b, steps);
            }

            /**
             * @brief Approximates the definite integral of a function using Romberg integration.
             *
             * This method computes the numerical integral of the provided function pointer `f`
             * over the interval [a, b] using Romberg integration, which combines the trapezoidal
             * rule with Richardson extrapolation for improved accuracy.
             *
             * @param f Function to integrate (takes a double and returns a double).
             * @param a Lower bound of integration.
             * @param b Upper bound of integration.
             * @param steps Number of subdivisions for the interval.
             * @return Approximate value of the definite integral of f over [a, b].
             */
            static double integrateRomberg(fossil_func_t f, double a, double b, int steps) {
            return fossil_math_numeric_integrate_romberg(f, a, b, steps);
            }

            /**
             * @brief Numerically integrates a function over an interval with selectable precision mode.
             *
             * This method provides a unified interface for numeric integration, allowing the caller
             * to select the desired precision mode (e.g., trapezoidal, Simpson, Romberg) via the
             * `mode` parameter.
             *
             * @param f Function to integrate (takes a double and returns a double).
             * @param a Lower bound of integration.
             * @param b Upper bound of integration.
             * @param steps Number of subdivisions for the interval.
             * @param mode Precision mode for integration (e.g., trapezoidal, Simpson, Romberg).
             * @return Approximate value of the definite integral of f over [a, b].
             */
            static double integrate(fossil_func_t f, double a, double b, int steps, fossil_numeric_mode_t mode) {
            return fossil_math_numeric_integrate(f, a, b, steps, mode);
            }

            /**
             * @brief Approximates the derivative of a function at a point using central difference.
             *
             * This method computes the numerical derivative of the provided function pointer `f`
             * at the specified point `x` using the central difference method with a small increment `h`.
             *
             * @param f Function whose derivative is to be computed (takes a double and returns a double).
             * @param x Point at which to compute the derivative.
             * @param h Small increment for finite difference.
             * @return Approximate derivative of f at x.
             */
            static double derivative(fossil_func_t f, double x, double h) {
            return fossil_math_numeric_derivative(f, x, h);
            }

            /**
             * @brief Attempts to find a root of the function near an initial guess using Newton-Raphson.
             *
             * This method applies the Newton-Raphson method to find a root of the provided function pointer `f`
             * near the initial guess `guess`. The process iterates until the result converges within the
             * specified tolerance `tol` or the maximum number of iterations `max_iter` is reached.
             *
             * @param f Function whose root is to be found (takes a double and returns a double).
             * @param guess Initial guess for the root.
             * @param tol Tolerance for convergence.
             * @param max_iter Maximum number of iterations.
             * @return Approximate root of f near the initial guess.
             */
            static double solve(fossil_func_t f, double guess, double tol, int max_iter) {
            return fossil_math_numeric_solve(f, guess, tol, max_iter);
            }

            /**
             * @brief Computes the interpolated y-value at a given x, using two known points.
             *
             * This method performs linear interpolation between two known points (`x0`, `y0`) and (`x1`, `y1`)
             * to estimate the y-value at a given x. The result is computed using the formula for linear interpolation.
             *
             * @param x0 First x-coordinate.
             * @param y0 First y-coordinate.
             * @param x1 Second x-coordinate.
             * @param y1 Second y-coordinate.
             * @param x The x-value at which to interpolate.
             * @return Interpolated y-value at x.
             */
            static double interpolate(double x0, double y0, double x1, double y1, double x) {
            return fossil_math_numeric_interpolate(x0, y0, x1, y1, x);
            }
        };

    } // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_GEOM_H */
