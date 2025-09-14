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
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
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

    /**
     * @class Trigonometry
     * @brief Provides static methods for trigonometric and hyperbolic operations.
     *
     * This class offers a C++ interface to the underlying Fossil Logic C trigonometric API.
     * All methods are static and directly wrap the corresponding C functions.
     */
    class Trigonometry {
    public:
        // ======================================================
        // Conversion
        // ======================================================

        /**
         * @brief Converts degrees to radians.
         * @param degrees Angle in degrees.
         * @return Angle in radians.
         */
        static double deg_to_rad(double degrees) {
            return fossil_math_trig_deg_to_rad(degrees);
        }

        /**
         * @brief Converts radians to degrees.
         * @param radians Angle in radians.
         * @return Angle in degrees.
         */
        static double rad_to_deg(double radians) {
            return fossil_math_trig_rad_to_deg(radians);
        }

        // ======================================================
        // Basic trig functions
        // ======================================================

        /**
         * @brief Computes the sine of an angle (in radians).
         * @param x Angle in radians.
         * @return Sine of the angle.
         */
        static double sin(double x) {
            return fossil_math_trig_sin(x);
        }

        /**
         * @brief Computes the cosine of an angle (in radians).
         * @param x Angle in radians.
         * @return Cosine of the angle.
         */
        static double cos(double x) {
            return fossil_math_trig_cos(x);
        }

        /**
         * @brief Computes the tangent of an angle (in radians).
         * @param x Angle in radians.
         * @return Tangent of the angle.
         */
        static double tan(double x) {
            return fossil_math_trig_tan(x);
        }

        // Inverse

        /**
         * @brief Computes the arcsine (inverse sine) of a value.
         * @param x Value whose arcsine is to be computed.
         * @return Angle in radians.
         */
        static double asin(double x) {
            return fossil_math_trig_asin(x);
        }

        /**
         * @brief Computes the arccosine (inverse cosine) of a value.
         * @param x Value whose arccosine is to be computed.
         * @return Angle in radians.
         */
        static double acos(double x) {
            return fossil_math_trig_acos(x);
        }

        /**
         * @brief Computes the arctangent (inverse tangent) of a value.
         * @param x Value whose arctangent is to be computed.
         * @return Angle in radians.
         */
        static double atan(double x) {
            return fossil_math_trig_atan(x);
        }

        /**
         * @brief Computes the arctangent of y/x using the signs of the arguments to determine the correct quadrant.
         * @param y Ordinate value.
         * @param x Abscissa value.
         * @return Angle in radians.
         */
        static double atan2(double y, double x) {
            return fossil_math_trig_atan2(y, x);
        }

        // ======================================================
        // Hyperbolic
        // ======================================================

        /**
         * @brief Computes the hyperbolic sine of a value.
         * @param x Value whose hyperbolic sine is to be computed.
         * @return Hyperbolic sine of the value.
         */
        static double sinh(double x) {
            return fossil_math_trig_sinh(x);
        }

        /**
         * @brief Computes the hyperbolic cosine of a value.
         * @param x Value whose hyperbolic cosine is to be computed.
         * @return Hyperbolic cosine of the value.
         */
        static double cosh(double x) {
            return fossil_math_trig_cosh(x);
        }

        /**
         * @brief Computes the hyperbolic tangent of a value.
         * @param x Value whose hyperbolic tangent is to be computed.
         * @return Hyperbolic tangent of the value.
         */
        static double tanh(double x) {
            return fossil_math_trig_tanh(x);
        }

        // Inverse hyperbolic

        /**
         * @brief Computes the inverse hyperbolic sine of a value.
         * @param x Value whose inverse hyperbolic sine is to be computed.
         * @return Inverse hyperbolic sine of the value.
         */
        static double asinh(double x) {
            return fossil_math_trig_asinh(x);
        }

        /**
         * @brief Computes the inverse hyperbolic cosine of a value.
         * @param x Value whose inverse hyperbolic cosine is to be computed.
         * @return Inverse hyperbolic cosine of the value.
         */
        static double acosh(double x) {
            return fossil_math_trig_acosh(x);
        }

        /**
         * @brief Computes the inverse hyperbolic tangent of a value.
         * @param x Value whose inverse hyperbolic tangent is to be computed.
         * @return Inverse hyperbolic tangent of the value.
         */
        static double atanh(double x) {
            return fossil_math_trig_atanh(x);
        }
    };

} // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_TRIG_H */
