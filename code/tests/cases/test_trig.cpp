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
#include <fossil/pizza/framework.h>
#include "fossil/math/framework.h"


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_SUITE(cpp_trig_fixture);

FOSSIL_SETUP(cpp_trig_fixture) {
    // Setup the test fixture
}


FOSSIL_TEARDOWN(cpp_trig_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_math_test_deg_to_rad) {
    double deg = 180.0;
    double expected = FOSSIL_MATH_PI;
    double result = fossil::math::Trigonometry::deg_to_rad(deg);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);

    deg = 90.0;
    expected = FOSSIL_MATH_PI / 2.0;
    result = fossil::math::Trigonometry::deg_to_rad(deg);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_rad_to_deg) {
    double rad = FOSSIL_MATH_PI;
    double expected = 180.0;
    double result = fossil::math::Trigonometry::rad_to_deg(rad);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);

    rad = FOSSIL_MATH_PI / 2.0;
    expected = 90.0;
    result = fossil::math::Trigonometry::rad_to_deg(rad);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_sin_cos_tan) {
    double angle = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::sin(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::cos(angle), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::tan(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);

    angle = FOSSIL_MATH_PI / 2.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::sin(angle), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::cos(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_inverse_trig) {
    double x = 1.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::asin(x), (FOSSIL_MATH_PI / 2.0), FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::acos(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::atan(1.0), (FOSSIL_MATH_PI / 4.0), FOSSIL_TEST_FLOAT_EPSILON);

    double y = 1.0, z = 1.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::atan2(y, z), (FOSSIL_MATH_PI / 4.0), FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_hyperbolic) {
    double x = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::sinh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::cosh(x), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::tanh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_inverse_hyperbolic) {
    double x = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::asinh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::acosh(1.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Trigonometry::atanh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_trig_tests) {
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_deg_to_rad);
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_rad_to_deg);
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_sin_cos_tan);
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_inverse_trig);
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_hyperbolic);
    FOSSIL_TEST_ADD(cpp_trig_fixture, cpp_math_test_inverse_hyperbolic);

    FOSSIL_TEST_REGISTER(cpp_trig_fixture);
} // end of tests
