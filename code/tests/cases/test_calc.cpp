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

FOSSIL_SUITE(cpp_calc_fixture);

FOSSIL_SETUP(cpp_calc_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_calc_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

#include <cmath>

// ==========================================================
// Derivatives Test Cases
// ==========================================================

static double test_funcpp_quad(double x) { return x * x; }
static double test_funcpp_sin(double x) { return sin(x); }

FOSSIL_TEST(cpp_math_test_calc_derivative) {
    double h = 1e-6;
    double d_quad = fossil::math::Calc::derivative(test_funcpp_quad, 2.0, h);
    ASSUME_ITS_EQUAL_F64(d_quad, 4.0, 1e-4);

    double d_sin = fossil::math::Calc::derivative(test_funcpp_sin, 0.0, h);
    ASSUME_ITS_EQUAL_F64(d_sin, 1.0, 1e-4);
}

FOSSIL_TEST(cpp_math_test_calc_derivative_n) {
    double h = 1e-6;
    double d2_quad = fossil::math::Calc::derivative_n(test_funcpp_quad, 2.0, 2, h);
    ASSUME_ITS_EQUAL_F64(d2_quad, 2.0, 1e-3);
 
    double d1_sin = fossil::math::Calc::derivative_n(test_funcpp_sin, 0.0, 1, h);
    ASSUME_ITS_EQUAL_F64(d1_sin, 1.0, 1e-4);

    double d2_sin = fossil::math::Calc::derivative_n(test_funcpp_sin, 0.0, 2, h);
    ASSUME_ITS_EQUAL_F64(d2_sin, 0.0, 1e-3);

    double d_neg = fossil::math::Calc::derivative_n(test_funcpp_quad, 1.0, -1, h);
    ASSUME_ITS_TRUE(isnan(d_neg));
}

// ==========================================================
// Integrals Test Cases
// ==========================================================

FOSSIL_TEST(cpp_math_test_calc_integrate_trapezoidal) {
    double result = fossil::math::Calc::integrate_trapezoidal(test_funcpp_quad, 0.0, 1.0, 1000);
    ASSUME_ITS_EQUAL_F64(result, 1.0 / 3.0, 1e-3);
}

FOSSIL_TEST(cpp_math_test_calc_integrate_simpson) {
    double result = fossil::math::Calc::integrate_simpson(test_funcpp_quad, 0.0, 1.0, 1000);
    ASSUME_ITS_EQUAL_F64(result, 1.0 / 3.0, 1e-5);
}

FOSSIL_TEST(cpp_math_test_calc_integrate_montecarlo) {
    double result = fossil::math::Calc::integrate_montecarlo(test_funcpp_quad, 0.0, 1.0, 100000);
    ASSUME_ITS_EQUAL_F64(result, 1.0 / 3.0, 1e-2);
}

// ==========================================================
// Limits Test Cases
// ==========================================================

FOSSIL_TEST(cpp_math_test_calc_limit) {
    double h = 1e-6;
    double lim = fossil::math::Calc::limit(test_funcpp_sin, 0.0, h);
    ASSUME_ITS_EQUAL_F64(lim, 0.0, 1e-6);
}

// ==========================================================
// Root Finding Test Cases
// ==========================================================

static double test_funcpp_root(double x) { return x * x - 2.0; }
static double test_funcpp_root_deriv(double x) { return 2.0 * x; }

FOSSIL_TEST(cpp_math_test_calc_root_newton) {
    double root = fossil::math::Calc::root_newton(test_funcpp_root, test_funcpp_root_deriv, 1.0, 1e-6, 100);
    ASSUME_ITS_EQUAL_F64(root, sqrt(2.0), 1e-6);
}

FOSSIL_TEST(cpp_math_test_calc_root_bisection) {
    double root = fossil::math::Calc::root_bisection(test_funcpp_root, 0.0, 2.0, 1e-6, 100);
    ASSUME_ITS_EQUAL_F64(root, sqrt(2.0), 1e-6);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_calc_tests) {
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_derivative);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_derivative_n);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_integrate_trapezoidal);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_integrate_simpson);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_integrate_montecarlo);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_limit);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_root_newton);
    FOSSIL_ADD_TEST(cpp_calc_fixture, cpp_math_test_calc_root_bisection);

    FOSSIL_ADD_SUITE(cpp_calc_fixture);
} // end of tests
