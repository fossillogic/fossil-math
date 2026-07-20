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

FOSSIL_SUITE(cpp_math_fixture);

FOSSIL_SETUP(cpp_math_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_math_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_math_test_constants) {
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_PI, 3.14159265358979323846, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_TWO_PI, 6.28318530717958647692, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_HALF_PI, 1.57079632679489661923, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_E, 2.71828182845904523536, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_LOG2E, 1.44269504088896340736, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_LOG10E, 0.43429448190325182765, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_LN2, 0.69314718055994530942, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_LN10, 2.30258509299404568402, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_SQRT2, 1.41421356237309504880, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_SQRT1_2, 0.70710678118654752440, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_DEG2RAD, FOSSIL_MATH_PI / 180.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(FOSSIL_MATH_RAD2DEG, 180.0 / FOSSIL_MATH_PI, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_macros) {
    ASSUME_ITS_TRUE(FOSSIL_MATH_MIN(3, 5) == 3);
    ASSUME_ITS_TRUE(FOSSIL_MATH_MAX(3, 5) == 5);
    ASSUME_ITS_TRUE(FOSSIL_MATH_CLAMP(10, 0, 5) == 5);
    ASSUME_ITS_TRUE(FOSSIL_MATH_CLAMP(-2, 0, 5) == 0);
    ASSUME_ITS_TRUE(FOSSIL_MATH_CLAMP(3, 0, 5) == 3);
    ASSUME_ITS_TRUE(FOSSIL_MATH_SIGN(5) == 1);
    ASSUME_ITS_TRUE(FOSSIL_MATH_SIGN(-5) == -1);
    ASSUME_ITS_TRUE(FOSSIL_MATH_SIGN(0) == 0);
    ASSUME_ITS_TRUE(FOSSIL_MATH_SQR(4) == 16);
    ASSUME_ITS_TRUE(FOSSIL_MATH_SQR(-3) == 9);
}

FOSSIL_TEST(cpp_math_test_abs) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::abs(5.0), 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::abs(-5.0), 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::abs(0.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_safe_div) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::safe_div(10.0, 2.0, -1.0), 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::safe_div(10.0, 0.0, -1.0), -1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::safe_div(0.0, 0.0, 42.0), 42.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_equal) {
    ASSUME_ITS_TRUE(fossil::math::Math::equal(1.0, 1.0 + 1e-10, 1e-9));
    ASSUME_ITS_TRUE(!fossil::math::Math::equal(1.0, 1.1, 1e-3));
}

FOSSIL_TEST(cpp_math_test_lerp) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::lerp(0.0, 10.0, 0.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::lerp(0.0, 10.0, 1.0), 10.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::lerp(0.0, 10.0, 0.5), 5.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_smoothstep) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::smoothstep(0.0, 1.0, -1.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::smoothstep(0.0, 1.0, 0.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::smoothstep(0.0, 1.0, 1.0), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::smoothstep(0.0, 1.0, 0.5), 0.5, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_factorial) {
    ASSUME_ITS_TRUE(fossil::math::Math::factorial(0) == 1ULL);
    ASSUME_ITS_TRUE(fossil::math::Math::factorial(1) == 1ULL);
    ASSUME_ITS_TRUE(fossil::math::Math::factorial(5) == 120ULL);
    ASSUME_ITS_TRUE(fossil::math::Math::factorial(10) == 3628800ULL);
}

FOSSIL_TEST(cpp_math_test_binomial) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::binomial(5, 2), 10.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::binomial(10, 0), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::binomial(10, 10), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::binomial(10, 11), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_wrap) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::wrap(370.0, 0.0, 360.0), 10.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::wrap(-10.0, 0.0, 360.0), 350.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::wrap(180.0, 0.0, 360.0), 180.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::wrap(0.0, 0.0, 0.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST(cpp_math_test_mod) {
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::mod(10.0, 3.0), 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::mod(-10.0, 3.0), 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::mod(10.0, -3.0), -2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::mod(0.0, 3.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Math::mod(10.0, 0.0), 0.0, FOSSIL_TEST_FLOAT_EPSILON);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_math_tests) {
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_constants);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_macros);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_abs);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_safe_div);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_equal);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_lerp);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_smoothstep);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_factorial);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_binomial);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_wrap);
    FOSSIL_ADD_TEST(cpp_math_fixture, cpp_math_test_mod);

    FOSSIL_ADD_SUITE(cpp_math_fixture);
} // end of tests
