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
#ifndef FOSSIL_MATH_CORE_H
#define FOSSIL_MATH_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C"
{
#endif

// ======================================================
// Constants
// ======================================================

/**
 * @brief Value of PI (π)
 */
#define FOSSIL_MATH_PI        3.14159265358979323846

/**
 * @brief Value of 2 * PI (2π)
 */
#define FOSSIL_MATH_TWO_PI    (2.0 * FOSSIL_MATH_PI)

/**
 * @brief Value of PI / 2 (π/2)
 */
#define FOSSIL_MATH_HALF_PI   (0.5 * FOSSIL_MATH_PI)

/**
 * @brief Value of Euler's number (e)
 */
#define FOSSIL_MATH_E         2.71828182845904523536

/**
 * @brief Base-2 logarithm of e (log₂e)
 */
#define FOSSIL_MATH_LOG2E     1.44269504088896340736

/**
 * @brief Base-10 logarithm of e (log₁₀e)
 */
#define FOSSIL_MATH_LOG10E    0.43429448190325182765

/**
 * @brief Natural logarithm of 2 (ln2)
 */
#define FOSSIL_MATH_LN2       0.69314718055994530942

/**
 * @brief Natural logarithm of 10 (ln10)
 */
#define FOSSIL_MATH_LN10      2.30258509299404568402

/**
 * @brief Square root of 2 (√2)
 */
#define FOSSIL_MATH_SQRT2     1.41421356237309504880

/**
 * @brief Square root of 1/2 (√½)
 */
#define FOSSIL_MATH_SQRT1_2   0.70710678118654752440

/**
 * @brief Degrees to radians conversion factor
 */
#define FOSSIL_MATH_DEG2RAD   (FOSSIL_MATH_PI / 180.0)

/**
 * @brief Radians to degrees conversion factor
 */
#define FOSSIL_MATH_RAD2DEG   (180.0 / FOSSIL_MATH_PI)

// ======================================================
// Utility Macros
// ======================================================

/**
 * @brief Returns the minimum of two values.
 * @param a First value
 * @param b Second value
 * @return The lesser of a and b
 */
#define FOSSIL_MATH_MIN(a,b) ((a) < (b) ? (a) : (b))

/**
 * @brief Returns the maximum of two values.
 * @param a First value
 * @param b Second value
 * @return The greater of a and b
 */
#define FOSSIL_MATH_MAX(a,b) ((a) > (b) ? (a) : (b))

/**
 * @brief Clamps a value between a minimum and maximum.
 * @param x Value to clamp
 * @param min Minimum bound
 * @param max Maximum bound
 * @return x clamped to [min, max]
 */
#define FOSSIL_MATH_CLAMP(x,min,max) (FOSSIL_MATH_MIN(FOSSIL_MATH_MAX((x),(min)),(max)))

/**
 * @brief Returns the sign of a value.
 * @param x Input value
 * @return 1 if x > 0, -1 if x < 0, 0 if x == 0
 */
#define FOSSIL_MATH_SIGN(x) (((x) > 0) - ((x) < 0))

/**
 * @brief Returns the square of a value.
 * @param x Input value
 * @return x squared
 */
#define FOSSIL_MATH_SQR(x) ((x) * (x))

// ======================================================
// Function Prototypes
// ======================================================

/**
 * @brief Returns the absolute value of a double.
 * @param x Input value
 * @return Absolute value of x
 */
double fossil_math_abs(double x);

/**
 * @brief Safely divides two doubles, returning a fallback if denominator is zero.
 * @param num Numerator
 * @param den Denominator
 * @param fallback Value to return if den == 0
 * @return num / den if den != 0, otherwise fallback
 */
double fossil_math_safe_div(double num, double den, double fallback);

/**
 * @brief Checks if two doubles are equal within a given epsilon.
 * @param a First value
 * @param b Second value
 * @param eps Tolerance
 * @return 1 if |a-b| < eps, 0 otherwise
 */
int fossil_math_equal(double a, double b, double eps);

/**
 * @brief Linearly interpolates between two values.
 * @param a Start value
 * @param b End value
 * @param t Interpolation factor [0,1]
 * @return Interpolated value
 */
double fossil_math_lerp(double a, double b, double t);

/**
 * @brief Performs smooth Hermite interpolation between two edges.
 * @param edge0 Lower edge
 * @param edge1 Upper edge
 * @param x Value to interpolate
 * @return Interpolated value
 */
double fossil_math_smoothstep(double edge0, double edge1, double x);

/**
 * @brief Computes the factorial of n.
 * @param n Input value
 * @return n!
 */
unsigned long long fossil_math_factorial(unsigned int n);

/**
 * @brief Computes the binomial coefficient (n choose k).
 * @param n Number of items
 * @param k Number of selections
 * @return Binomial coefficient
 */
double fossil_math_binomial(unsigned int n, unsigned int k);

/**
 * @brief Wraps a value x to the range [min, max).
 * @param x Value to wrap
 * @param min Minimum bound
 * @param max Maximum bound
 * @return Wrapped value
 */
double fossil_math_wrap(double x, double min, double max);

/**
 * @brief Computes the floating-point remainder of x/y.
 * @param x Dividend
 * @param y Divisor
 * @return Remainder of x divided by y
 */
double fossil_math_mod(double x, double y);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

    namespace math {

        /**
         * @class Math
         * @brief Provides static utility functions for common mathematical operations.
         *
         * This class acts as a wrapper for the fossil_math C API, exposing a set of static methods
         * for mathematical computations. Each method delegates its implementation to the corresponding
         * fossil_math_* function, ensuring consistent behavior and usage.
         *
         * The available operations include:
         * - Absolute value calculation
         * - Safe division with fallback for zero denominators
         * - Equality comparison within a specified epsilon
         * - Linear interpolation between two values
         * - Smooth Hermite interpolation (smoothstep)
         * - Factorial computation for non-negative integers
         * - Binomial coefficient calculation ("n choose k")
         * - Wrapping a value within a specified range
         * - Floating-point modulus operation
         *
         * All methods are static and can be called without instantiating the class.
         *
         * @note These functions are intended for use with double-precision floating-point values,
         *       except for factorial and binomial, which operate on unsigned integers.
         *
         * @see fossil_math_abs
         * @see fossil_math_safe_div
         * @see fossil_math_equal
         * @see fossil_math_lerp
         * @see fossil_math_smoothstep
         * @see fossil_math_factorial
         * @see fossil_math_binomial
         * @see fossil_math_wrap
         * @see fossil_math_mod
         */
        class Math {
        public:
            /**
             * @brief Returns the absolute value of a double.
             * @param x Input value
             * @return Absolute value of x
             */
            static double abs(double x) { return fossil_math_abs(x); }

            /**
             * @brief Safely divides two doubles, returning a fallback if denominator is zero.
             * @param num Numerator
             * @param den Denominator
             * @param fallback Value to return if den == 0
             * @return num / den if den != 0, otherwise fallback
             */
            static double safe_div(double num, double den, double fallback) { return fossil_math_safe_div(num, den, fallback); }

            /**
             * @brief Checks if two doubles are equal within a given epsilon.
             * @param a First value
             * @param b Second value
             * @param eps Tolerance
             * @return true if |a-b| < eps, false otherwise
             */
            static bool equal(double a, double b, double eps) { return fossil_math_equal(a, b, eps) != 0; }

            /**
             * @brief Linearly interpolates between two values.
             * @param a Start value
             * @param b End value
             * @param t Interpolation factor [0,1]
             * @return Interpolated value
             */
            static double lerp(double a, double b, double t) { return fossil_math_lerp(a, b, t); }

            /**
             * @brief Performs smooth Hermite interpolation between two edges.
             * @param edge0 Lower edge
             * @param edge1 Upper edge
             * @param x Value to interpolate
             * @return Interpolated value
             */
            static double smoothstep(double edge0, double edge1, double x) { return fossil_math_smoothstep(edge0, edge1, x); }

            /**
             * @brief Computes the factorial of n.
             * @param n Input value
             * @return n!
             */
            static unsigned long long factorial(unsigned int n) { return fossil_math_factorial(n); }

            /**
             * @brief Computes the binomial coefficient (n choose k).
             * @param n Number of items
             * @param k Number of selections
             * @return Binomial coefficient
             */
            static double binomial(unsigned int n, unsigned int k) { return fossil_math_binomial(n, k); }

            /**
             * @brief Wraps a value x to the range [min, max).
             * @param x Value to wrap
             * @param min Minimum bound
             * @param max Maximum bound
             * @return Wrapped value
             */
            static double wrap(double x, double min, double max) { return fossil_math_wrap(x, min, max); }

            /**
             * @brief Computes the floating-point remainder of x/y.
             * @param x Dividend
             * @param y Divisor
             * @return Remainder of x divided by y
             */
            static double mod(double x, double y) { return fossil_math_mod(x, y); }
        };

    } // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_CORE_H */
