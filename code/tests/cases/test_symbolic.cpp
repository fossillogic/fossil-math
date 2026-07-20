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

FOSSIL_SUITE(cpp_symbolicpp_fixture);

FOSSIL_SETUP(cpp_symbolicpp_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_symbolicpp_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_math_test_sym_parse_and_to_string) {
    auto expr = fossil::math::Symbolic::parse("x + 2");
    char buf[64];
    size_t len = fossil::math::Symbolic::to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(len > 0);
    ASSUME_ITS_TRUE(strstr(buf, "x") != NULL);
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_eval) {
    auto expr = fossil::math::Symbolic::parse("x * y + 1");
    double val = fossil::math::Symbolic::eval(expr, [](const std::string& name) {
        if (name == "x") return 2.0;
        if (name == "y") return 3.0;
        return 0.0;
    });
    ASSUME_ITS_EQUAL_F64(val, 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_substitute) {
    auto expr = fossil::math::Symbolic::parse("x + y");
    auto sub = fossil::math::Symbolic::substitute(expr, "x", 5.0);
    double val = fossil::math::Symbolic::eval(sub, [](const std::string& name) {
        if (name == "y") return 3.0;
        return 0.0;
    });
    ASSUME_ITS_EQUAL_F64(val, 8.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Symbolic::free(expr);
    fossil::math::Symbolic::free(sub);
}

FOSSIL_TEST(cpp_math_test_sym_parse_constants) {
    auto expr = fossil::math::Symbolic::parse("pi + e");
    double val = fossil::math::Symbolic::eval(expr, nullptr);
    ASSUME_ITS_EQUAL_F64(val, FOSSIL_MATH_PI + FOSSIL_MATH_E, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_simplify_basic) {
    auto expr = fossil::math::Symbolic::parse("2 + 3");
    expr = fossil::math::Symbolic::simplify(expr);
    double val = fossil::math::Symbolic::eval(expr, nullptr);
    ASSUME_ITS_EQUAL_F64(val, 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    char buf[32];
    fossil::math::Symbolic::to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(strstr(buf, "5") != NULL);
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_to_string_parens) {
    auto expr = fossil::math::Symbolic::parse("x + y * 2");
    char buf[64];
    fossil::math::Symbolic::to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(strstr(buf, "y") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "2") != NULL);
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_eval_division_by_zero) {
    auto expr = fossil::math::Symbolic::parse("1 / 0");
    double val = fossil::math::Symbolic::eval(expr, nullptr);
    ASSUME_ITS_TRUE(isnan(val));
    fossil::math::Symbolic::free(expr);
}

FOSSIL_TEST(cpp_math_test_sym_substitute_all_vars) {
    auto expr = fossil::math::Symbolic::parse("x + y");
    auto sub1 = fossil::math::Symbolic::substitute(expr, "x", 10.0);
    auto sub2 = fossil::math::Symbolic::substitute(sub1, "y", 20.0);
    double val = fossil::math::Symbolic::eval(sub2, nullptr);
    ASSUME_ITS_EQUAL_F64(val, 30.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Symbolic::free(expr);
    fossil::math::Symbolic::free(sub1);
    fossil::math::Symbolic::free(sub2);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_symbolicpp_tests) {
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_parse_and_to_string);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_eval);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_substitute);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_parse_constants);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_simplify_basic);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_to_string_parens);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_eval_division_by_zero);
    FOSSIL_ADD_TEST(cpp_symbolicpp_fixture, cpp_math_test_sym_substitute_all_vars);

    FOSSIL_ADD_SUITE(cpp_symbolicpp_fixture);
} // end of tests
