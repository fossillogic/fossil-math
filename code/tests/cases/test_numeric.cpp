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
#include <fossil/maip/framework.h>
#include "fossil/math/framework.h"


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_SUITE(cpp_numeric_fixture);

FOSSIL_SETUP(cpp_numeric_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_numeric_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

static double test_funcpp_linear(double x) { return 2.0 * x + 1.0; }
static double test_funcpp_quad(double x) { return x * x; }
static double test_funcpp_sin(double x) { return sin(x); }

FOSSIL_TEST(cpp_numeric_test_integrate_trapezoidal_linear) {
    double result = fossil::math::Numeric::integrateTrapezoidal(test_funcpp_linear, 0.0, 1.0, 100);
    ASSUME_ITS_EQUAL_F64(result, 2.0, 1e-4); // ∫(2x+1)dx from 0 to 1 = 2
}

FOSSIL_TEST(cpp_numeric_test_integrate_trapezoidal_quad) {
    double result = fossil::math::Numeric::integrateTrapezoidal(test_funcpp_quad, 0.0, 1.0, 100);
    ASSUME_ITS_EQUAL_F64(result, 1.0/3.0, 1e-4); // ∫x^2 dx from 0 to 1 = 1/3
}

FOSSIL_TEST(cpp_numeric_test_integrate_simpson_linear) {
    double result = fossil::math::Numeric::integrateSimpson(test_funcpp_linear, 0.0, 1.0, 100);
    ASSUME_ITS_EQUAL_F64(result, 2.0, 1e-6);
}

FOSSIL_TEST(cpp_numeric_test_integrate_simpson_quad) {
    double result = fossil::math::Numeric::integrateSimpson(test_funcpp_quad, 0.0, 1.0, 100);
    ASSUME_ITS_EQUAL_F64(result, 1.0/3.0, 1e-6);
}

FOSSIL_TEST(cpp_numeric_test_integrate_romberg_sin) {
    double result = fossil::math::Numeric::integrateRomberg(test_funcpp_sin, 0.0, FOSSIL_MATH_PI, 8);
    ASSUME_ITS_EQUAL_F64(result, 2.0, 1e-4); // ∫sin(x)dx from 0 to pi = 2
}

FOSSIL_TEST(cpp_numeric_test_integrate_mode_simpson) {
    double result = fossil::math::Numeric::integrate(test_funcpp_quad, 0.0, 1.0, 100, FOSSIL_NUMERIC_SIMPSON);
    ASSUME_ITS_EQUAL_F64(result, 1.0/3.0, 1e-6);
}

// ============================================================================
// Derivative
// ============================================================================

FOSSIL_TEST(cpp_numeric_test_derivative_linear) {
    double result = fossil::math::Numeric::derivative(test_funcpp_linear, 1.0, 1e-6);
    ASSUME_ITS_EQUAL_F64(result, 2.0, 1e-4); // derivative of 2x+1 is 2
}

FOSSIL_TEST(cpp_numeric_test_derivative_quad) {
    double result = fossil::math::Numeric::derivative(test_funcpp_quad, 2.0, 1e-6);
    ASSUME_ITS_EQUAL_F64(result, 4.0, 1e-3); // derivative of x^2 at x=2 is 4
}

// ============================================================================
// Root Finding
// ============================================================================

static double test_funcpp_root(double x) { return x*x - 2.0; }

FOSSIL_TEST(cpp_numeric_test_solve_newton_sqrt2) {
    double root = fossil::math::Numeric::solve(test_funcpp_root, 1.0, 1e-6, 20);
    ASSUME_ITS_EQUAL_F64(root, sqrt(2.0), 1e-4);
}

// ============================================================================
// Linear Interpolation
// ============================================================================

FOSSIL_TEST(cpp_numeric_test_interpolate_simple) {
    double y = fossil::math::Numeric::interpolate(0.0, 0.0, 2.0, 4.0, 1.0);
    ASSUME_ITS_EQUAL_F64(y, 2.0, 1e-8); // line from (0,0) to (2,4), at x=1, y=2
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_numeric_tests) {
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_trapezoidal_linear);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_trapezoidal_quad);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_simpson_linear);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_simpson_quad);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_romberg_sin);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_integrate_mode_simpson);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_derivative_linear);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_derivative_quad);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_solve_newton_sqrt2);
    FOSSIL_ADD_TEST(cpp_numeric_fixture, cpp_numeric_test_interpolate_simple);

    FOSSIL_ADD_SUITE(cpp_numeric_fixture);
} // end of tests
