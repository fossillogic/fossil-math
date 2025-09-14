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

FOSSIL_TEST_SUITE(c_algebra_fixture);

FOSSIL_SETUP(c_algebra_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_algebra_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_math_test_dot_product) {
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double result = fossil_math_algebra_dot(a, b, 3);
    ASSUME_ITS_EQUAL_F64(result, 32.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_vector_add) {
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double result[3];
    fossil_math_algebra_add(a, b, result, 3);
    ASSUME_ITS_EQUAL_F64(result[0], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 9.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_vector_sub) {
    double a[] = {5.0, 7.0, 9.0};
    double b[] = {1.0, 2.0, 3.0};
    double result[3];
    fossil_math_algebra_sub(a, b, result, 3);
    ASSUME_ITS_EQUAL_F64(result[0], 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_scalar_mul) {
    double a[] = {1.0, -2.0, 3.0};
    double result[3];
    fossil_math_algebra_scalar_mul(a, 2.0, result, 3);
    ASSUME_ITS_EQUAL_F64(result[0], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], -4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_matrix_mul) {
    double A[] = {1, 2, 3, 4}; // 2x2
    double B[] = {5, 6, 7, 8}; // 2x2
    double C[4];
    int ret = fossil_math_algebra_matrix_mul(A, 2, 2, B, 2, 2, C);
    ASSUME_ITS_TRUE(ret == 0);
    ASSUME_ITS_EQUAL_F64(C[0], 19.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[1], 22.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[2], 43.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[3], 50.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_matrix_transpose) {
    double A[] = {1, 2, 3, 4, 5, 6}; // 2x3
    double T[6];
    int ret = fossil_math_algebra_matrix_transpose(A, 2, 3, T);
    ASSUME_ITS_TRUE(ret == 0);
    ASSUME_ITS_EQUAL_F64(T[0], 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[1], 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[2], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[3], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[4], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[5], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_matrix_identity) {
    double M[9];
    int ret = fossil_math_algebra_matrix_identity(M, 3);
    ASSUME_ITS_TRUE(ret == 0);
    ASSUME_ITS_EQUAL_F64(M[0], 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[1], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[2], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[3], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[4], 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[5], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[6], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[7], 0.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(M[8], 1.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_matrix_determinant) {
    double M[] = {1, 2, 3, 4}; // 2x2
    double det = 0.0;
    int ret = fossil_math_algebra_matrix_determinant(M, 2, &det);
    ASSUME_ITS_TRUE(ret == 0);
    ASSUME_ITS_EQUAL_F64(det, -2.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_poly_eval) {
    double coeffs[] = {1, 2, 3}; // 1 + 2x + 3x^2
    double val = fossil_math_algebra_poly_eval(coeffs, 2, 2.0);
    ASSUME_ITS_EQUAL_F64(val, 17.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_poly_derivative) {
    double coeffs[] = {1, 2, 3}; // 1 + 2x + 3x^2
    double deriv[2];
    fossil_math_algebra_poly_derivative(coeffs, 2, deriv);
    ASSUME_ITS_EQUAL_F64(deriv[0], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(deriv[1], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_poly_add) {
    double A[] = {1, 2, 3}; // deg 2
    double B[] = {4, 5};    // deg 1
    double result[3];
    size_t degR;
    fossil_math_algebra_poly_add(A, 2, B, 1, result, &degR);
    ASSUME_ITS_TRUE(degR == 2);
    ASSUME_ITS_EQUAL_F64(result[0], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_poly_mul) {
    double A[] = {1, 2}; // 1 + 2x
    double B[] = {3, 4}; // 3 + 4x
    double result[3];
    size_t degR;
    fossil_math_algebra_poly_mul(A, 1, B, 1, result, &degR);
    ASSUME_ITS_TRUE(degR == 2);
    ASSUME_ITS_EQUAL_F64(result[0], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 10.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 8.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(c_math_test_solve_quadratic_real) {
    double r1, r2;
    int ret = fossil_math_algebra_solve_quadratic(1, -3, 2, &r1, &r2); // x^2 - 3x + 2 = 0
    ASSUME_ITS_TRUE(ret == 0);
    ASSUME_ITS_TRUE(
        (fabs(r1 - 2.0) < FOSSIL_TEST_FLOAT_EPSILON && fabs(r2 - 1.0) < FOSSIL_TEST_FLOAT_EPSILON) ||
        (fabs(r1 - 1.0) < FOSSIL_TEST_FLOAT_EPSILON && fabs(r2 - 2.0) < FOSSIL_TEST_FLOAT_EPSILON)
    );
}

FOSSIL_TEST_CASE(c_math_test_solve_quadratic_complex) {
    double r1, r2;
    int ret = fossil_math_algebra_solve_quadratic(1, 0, 1, &r1, &r2); // x^2 + 1 = 0
    ASSUME_ITS_TRUE(ret == -2);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_algebra_tests) {
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_matrix_transpose);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_matrix_identity);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_matrix_determinant);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_poly_eval);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_poly_derivative);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_poly_add);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_poly_mul);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_scalar_mul);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_matrix_mul);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_solve_quadratic_real);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_solve_quadratic_complex);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_vector_add);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_vector_sub);
    FOSSIL_TEST_ADD(c_algebra_fixture, c_math_test_dot_product);

    FOSSIL_TEST_REGISTER(c_algebra_fixture);
} // end of tests
