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
#ifndef FOSSIL_MATH_CALC_H
#define FOSSIL_MATH_CALC_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ==========================================================
// Types
// ==========================================================

typedef double (*fossil_math_func_t)(const double x);  // Generic function pointer

// ==========================================================
// Derivatives
// ==========================================================

/**
 * @brief Compute the numerical derivative of a function at a given point.
 *
 * Uses the central difference method to approximate the derivative.
 *
 * @param f Function pointer to the function to differentiate.
 * @param x Point at which to evaluate the derivative.
 * @param h Step size for the approximation.
 * @return Approximated derivative value at x.
 */
double fossil_math_calc_derivative(fossil_math_func_t f, double x, double h);

/**
 * @brief Compute the nth order numerical derivative of a function at a given point.
 *
 * Uses recursion and central difference to approximate higher-order derivatives.
 *
 * @param f Function pointer to the function to differentiate.
 * @param x Point at which to evaluate the derivative.
 * @param n Order of the derivative.
 * @param h Step size for the approximation.
 * @return Approximated nth derivative value at x.
 */
double fossil_math_calc_derivative_n(fossil_math_func_t f, double x, int n, double h);

// ==========================================================
// Integrals
// ==========================================================

/**
 * @brief Numerically integrate a function over an interval using the trapezoidal rule.
 *
 * Approximates the definite integral by dividing the interval into subintervals and summing trapezoidal areas.
 *
 * @param f Function pointer to the function to integrate.
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param n Number of subintervals.
 * @return Approximated integral value.
 */
double fossil_math_calc_integrate_trapezoidal(fossil_math_func_t f, double a, double b, size_t n);

/**
 * @brief Numerically integrate a function over an interval using Simpson’s rule.
 *
 * Approximates the definite integral using parabolic arcs over subintervals (n should be even).
 *
 * @param f Function pointer to the function to integrate.
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param n Number of subintervals (should be even).
 * @return Approximated integral value.
 */
double fossil_math_calc_integrate_simpson(fossil_math_func_t f, double a, double b, size_t n);

/**
 * @brief Estimate the integral of a function over an interval using Monte Carlo sampling.
 *
 * Uses random sampling to estimate the area under the curve.
 *
 * @param f Function pointer to the function to integrate.
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param samples Number of random samples to use.
 * @return Approximated integral value.
 */
double fossil_math_calc_integrate_montecarlo(fossil_math_func_t f, double a, double b, size_t samples);

// ==========================================================
// Limits
// ==========================================================

/**
 * @brief Estimate the limit of a function as x approaches a given value.
 *
 * Uses a small step size to approximate the limit.
 *
 * @param f Function pointer to the function.
 * @param x Point at which to evaluate the limit.
 * @param h Step size for the approximation.
 * @return Approximated limit value.
 */
double fossil_math_calc_limit(fossil_math_func_t f, double x, double h);

// ==========================================================
// Root Finding
// ==========================================================

/**
 * @brief Find a root of a function using the Newton-Raphson method.
 *
 * Iteratively refines the root estimate using the function and its derivative.
 *
 * @param f Function pointer to the function whose root is sought.
 * @param df Function pointer to the derivative of f.
 * @param x0 Initial guess for the root.
 * @param tol Tolerance for convergence.
 * @param max_iter Maximum number of iterations.
 * @return Approximated root value.
 */
double fossil_math_calc_root_newton(fossil_math_func_t f, fossil_math_func_t df, double x0, double tol, size_t max_iter);

/**
 * @brief Find a root of a function using the bisection method.
 *
 * Iteratively narrows the interval where the root lies until convergence.
 *
 * @param f Function pointer to the function whose root is sought.
 * @param a Lower bound of the interval.
 * @param b Upper bound of the interval.
 * @param tol Tolerance for convergence.
 * @param max_iter Maximum number of iterations.
 * @return Approximated root value.
 */
double fossil_math_calc_root_bisection(fossil_math_func_t f, double a, double b, double tol, size_t max_iter);

// ==========================================================
// Utilities
// ==========================================================

/**
 * @brief Compute the gradient vector for a multivariable function.
 *
 * Evaluates the partial derivatives for each variable to form the gradient vector.
 *
 * @param funcs Array of function pointers, each representing a partial derivative.
 * @param x Array of input variable values.
 * @param grad Output array for the gradient vector.
 * @param dim Dimension of the input space.
 * @param h Step size for the approximation.
 */
void fossil_math_calc_gradient(fossil_math_func_t* funcs, const double* x, double* grad, size_t dim, double h);

/**
 * @brief Compute the numerical partial derivative of a multivariable function.
 *
 * Approximates the partial derivative with respect to a specific variable.
 *
 * @param f Function pointer to the function.
 * @param x Array of input variable values.
 * @param i Index of the variable to differentiate with respect to.
 * @param h Step size for the approximation.
 * @return Approximated partial derivative value.
 */
double fossil_math_calc_partial(fossil_math_func_t f, const double* x, size_t i, double h);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

    namespace math {

        /**
         * @brief C++ wrappers for core mathematical calculation functions.
         *
         * The Calc class provides static methods that wrap the C functions defined in fossil/math/calc.h,
         * offering a C++-friendly interface for numerical calculus operations such as derivatives, integrals,
         * limits, root finding, and utility calculations. Each method directly delegates to its corresponding
         * C implementation, ensuring high performance and cross-language compatibility.
         */
        class Calc {
        public:
            /**
             * @brief Compute the numerical derivative of a function at a given point.
             * @param f Function pointer to the function to differentiate.
             * @param x Point at which to evaluate the derivative.
             * @param h Step size for the central difference approximation.
             * @return Approximated derivative value at x.
             */
            static double derivative(fossil_math_func_t f, double x, double h) {
            return fossil_math_calc_derivative(f, x, h);
            }

            /**
             * @brief Compute the nth order numerical derivative of a function at a given point.
             * @param f Function pointer to the function to differentiate.
             * @param x Point at which to evaluate the derivative.
             * @param n Order of the derivative.
             * @param h Step size for the approximation.
             * @return Approximated nth derivative value at x.
             */
            static double derivative_n(fossil_math_func_t f, double x, int n, double h) {
            return fossil_math_calc_derivative_n(f, x, n, h);
            }

            /**
             * @brief Numerically integrate a function over an interval using the trapezoidal rule.
             * @param f Function pointer to the function to integrate.
             * @param a Lower bound of the interval.
             * @param b Upper bound of the interval.
             * @param n Number of subintervals.
             * @return Approximated integral value.
             */
            static double integrate_trapezoidal(fossil_math_func_t f, double a, double b, size_t n) {
            return fossil_math_calc_integrate_trapezoidal(f, a, b, n);
            }

            /**
             * @brief Numerically integrate a function over an interval using Simpson’s rule.
             * @param f Function pointer to the function to integrate.
             * @param a Lower bound of the interval.
             * @param b Upper bound of the interval.
             * @param n Number of subintervals (should be even).
             * @return Approximated integral value.
             */
            static double integrate_simpson(fossil_math_func_t f, double a, double b, size_t n) {
            return fossil_math_calc_integrate_simpson(f, a, b, n);
            }

            /**
             * @brief Estimate the integral of a function over an interval using Monte Carlo sampling.
             * @param f Function pointer to the function to integrate.
             * @param a Lower bound of the interval.
             * @param b Upper bound of the interval.
             * @param samples Number of random samples to use.
             * @return Approximated integral value.
             */
            static double integrate_montecarlo(fossil_math_func_t f, double a, double b, size_t samples) {
            return fossil_math_calc_integrate_montecarlo(f, a, b, samples);
            }

            /**
             * @brief Estimate the limit of a function as x approaches a given value.
             * @param f Function pointer to the function.
             * @param x Point at which to evaluate the limit.
             * @param h Step size for the approximation.
             * @return Approximated limit value.
             */
            static double limit(fossil_math_func_t f, double x, double h) {
            return fossil_math_calc_limit(f, x, h);
            }

            /**
             * @brief Find a root of a function using the Newton-Raphson method.
             * @param f Function pointer to the function whose root is sought.
             * @param df Function pointer to the derivative of f.
             * @param x0 Initial guess for the root.
             * @param tol Tolerance for convergence.
             * @param max_iter Maximum number of iterations.
             * @return Approximated root value.
             */
            static double root_newton(fossil_math_func_t f, fossil_math_func_t df, double x0, double tol, size_t max_iter) {
            return fossil_math_calc_root_newton(f, df, x0, tol, max_iter);
            }

            /**
             * @brief Find a root of a function using the bisection method.
             * @param f Function pointer to the function whose root is sought.
             * @param a Lower bound of the interval.
             * @param b Upper bound of the interval.
             * @param tol Tolerance for convergence.
             * @param max_iter Maximum number of iterations.
             * @return Approximated root value.
             */
            static double root_bisection(fossil_math_func_t f, double a, double b, double tol, size_t max_iter) {
            return fossil_math_calc_root_bisection(f, a, b, tol, max_iter);
            }

            /**
             * @brief Compute the gradient vector for a multivariable function.
             * @param funcs Array of function pointers, each representing a partial derivative.
             * @param x Array of input variable values.
             * @param grad Output array for the gradient vector.
             * @param dim Dimension of the input space.
             * @param h Step size for the approximation.
             */
            static void gradient(fossil_math_func_t* funcs, const double* x, double* grad, size_t dim, double h) {
            fossil_math_calc_gradient(funcs, x, grad, dim, h);
            }

            /**
             * @brief Compute the numerical partial derivative of a multivariable function.
             * @param f Function pointer to the function.
             * @param x Array of input variable values.
             * @param i Index of the variable to differentiate with respect to.
             * @param h Step size for the approximation.
             * @return Approximated partial derivative value.
             */
            static double partial(fossil_math_func_t f, const double* x, size_t i, double h) {
            return fossil_math_calc_partial(f, x, i, h);
            }
        };

    } // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_GEOM_H */
