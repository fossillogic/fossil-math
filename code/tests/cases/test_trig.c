/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
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

FOSSIL_TEST_SUITE(c_trig_fixture);

FOSSIL_SETUP(c_trig_fixture) {
    // Setup the test fixture
}


FOSSIL_TEARDOWN(c_trig_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_math_test_deg_to_rad) {
    double deg = 180.0;
    double expected = FOSSIL_MATH_PI;
    double result = fossil_math_trig_deg_to_rad(deg);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);

    deg = 90.0;
    expected = FOSSIL_MATH_PI / 2.0;
    result = fossil_math_trig_deg_to_rad(deg);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_rad_to_deg) {
    double rad = FOSSIL_MATH_PI;
    double expected = 180.0;
    double result = fossil_math_trig_rad_to_deg(rad);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);

    rad = FOSSIL_MATH_PI / 2.0;
    expected = 90.0;
    result = fossil_math_trig_rad_to_deg(rad);
    ASSUME_ITS_EQUAL_F64(result, expected, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_sin_cos_tan) {
    double angle = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_sin(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_cos(angle), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_tan(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);

    angle = FOSSIL_MATH_PI / 2.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_sin(angle), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_cos(angle), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_inverse_trig) {
    double x = 1.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_asin(x), (FOSSIL_MATH_PI / 2.0), FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_acos(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_atan(1.0), (FOSSIL_MATH_PI / 4.0), FOSSIL_TEST_FLOAT_EPSILON);

    double y = 1.0, z = 1.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_atan2(y, z), (FOSSIL_MATH_PI / 4.0), FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_hyperbolic) {
    double x = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_sinh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_cosh(x), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_tanh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_inverse_hyperbolic) {
    double x = 0.0;
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_asinh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_acosh(1.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_trig_atanh(x), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_trig_tests) {
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_deg_to_rad);
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_rad_to_deg);
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_sin_cos_tan);
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_inverse_trig);
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_hyperbolic);
    FOSSIL_TEST_ADD(c_trig_fixture, c_math_test_inverse_hyperbolic);

    FOSSIL_TEST_REGISTER(c_trig_fixture);
} // end of tests
