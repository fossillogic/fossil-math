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

FOSSIL_SUITE(c_symbolic_fixture);

FOSSIL_SETUP(c_symbolic_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_symbolic_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

static double test_var_lookup(const char* name) {
    if (strcmp(name, "x") == 0) return 2.0;
    if (strcmp(name, "y") == 0) return 3.0;
    return 0.0;
}

FOSSIL_TEST(c_math_test_sym_parse_and_to_string) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("x + 2");
    char buf[64];
    size_t len = fossil_math_sym_to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(len > 0);
    ASSUME_ITS_TRUE(strstr(buf, "x") != NULL);
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_eval) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("x * y + 1");
    double val = fossil_math_sym_eval(expr, test_var_lookup);
    ASSUME_ITS_EQUAL_F64(val, 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_substitute) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("x + y");
    fossil_math_sym_expr_t* sub = fossil_math_sym_substitute(expr, "x", 5.0);
    double val = fossil_math_sym_eval(sub, test_var_lookup);
    ASSUME_ITS_EQUAL_F64(val, 8.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_sym_free(expr);
    fossil_math_sym_free(sub);
}

FOSSIL_TEST(c_math_test_sym_parse_constants) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("pi + e");
    double val = fossil_math_sym_eval(expr, NULL);
    ASSUME_ITS_EQUAL_F64(val, FOSSIL_MATH_PI + FOSSIL_MATH_E, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_simplify_basic) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("2 + 3");
    expr = fossil_math_sym_simplify(expr);
    double val = fossil_math_sym_eval(expr, NULL);
    ASSUME_ITS_EQUAL_F64(val, 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    char buf[32];
    fossil_math_sym_to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(strstr(buf, "5") != NULL);
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_to_string_parens) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("x + y * 2");
    char buf[64];
    fossil_math_sym_to_string(expr, buf, sizeof(buf));
    ASSUME_ITS_TRUE(strstr(buf, "y") != NULL);
    ASSUME_ITS_TRUE(strstr(buf, "2") != NULL);
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_eval_division_by_zero) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("1 / 0");
    double val = fossil_math_sym_eval(expr, NULL);
    ASSUME_ITS_TRUE(isnan(val));
    fossil_math_sym_free(expr);
}

FOSSIL_TEST(c_math_test_sym_substitute_all_vars) {
    fossil_math_sym_expr_t* expr = fossil_math_sym_parse("x + y");
    fossil_math_sym_expr_t* sub1 = fossil_math_sym_substitute(expr, "x", 10.0);
    fossil_math_sym_expr_t* sub2 = fossil_math_sym_substitute(sub1, "y", 20.0);
    double val = fossil_math_sym_eval(sub2, test_var_lookup);
    ASSUME_ITS_EQUAL_F64(val, 30.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_sym_free(expr);
    fossil_math_sym_free(sub1);
    fossil_math_sym_free(sub2);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_symbolic_tests) {
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_parse_and_to_string);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_eval);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_substitute);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_parse_constants);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_simplify_basic);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_to_string_parens);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_eval_division_by_zero);
    FOSSIL_ADD_TEST(c_symbolic_fixture, c_math_test_sym_substitute_all_vars);

    FOSSIL_ADD_SUITE(c_symbolic_fixture);
} // end of tests
