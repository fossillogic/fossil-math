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

FOSSIL_TEST_SUITE(cpp_algebra_fixture);

FOSSIL_SETUP(cpp_algebra_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_algebra_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_math_test_dot_product) {
    std::vector<double> a{1.0, 2.0, 3.0};
    std::vector<double> b{4.0, 5.0, 6.0};
    double result = fossil::math::Algebra::dot(a, b);
    ASSUME_ITS_EQUAL_F64(result, 32.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_vector_add) {
    std::vector<double> a{1.0, 2.0, 3.0};
    std::vector<double> b{4.0, 5.0, 6.0};
    auto result = fossil::math::Algebra::add(a, b);
    ASSUME_ITS_EQUAL_F64(result[0], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 9.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_vector_sub) {
    std::vector<double> a{5.0, 7.0, 9.0};
    std::vector<double> b{1.0, 2.0, 3.0};
    auto result = fossil::math::Algebra::sub(a, b);
    ASSUME_ITS_EQUAL_F64(result[0], 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_scalar_mul) {
    std::vector<double> a{1.0, -2.0, 3.0};
    auto result = fossil::math::Algebra::scalar_mul(a, 2.0);
    ASSUME_ITS_EQUAL_F64(result[0], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], -4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_matrix_mul) {
    std::vector<double> A{1, 2, 3, 4}; // 2x2
    std::vector<double> B{5, 6, 7, 8}; // 2x2
    auto C = fossil::math::Algebra::matrix_mul(A, 2, 2, B, 2, 2);
    ASSUME_ITS_EQUAL_F64(C[0], 19.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[1], 22.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[2], 43.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(C[3], 50.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_matrix_transpose) {
    std::vector<double> A{1, 2, 3, 4, 5, 6}; // 2x3
    auto T = fossil::math::Algebra::matrix_transpose(A, 2, 3);
    ASSUME_ITS_EQUAL_F64(T[0], 1.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[1], 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[2], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[3], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[4], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(T[5], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_matrix_identity) {
    auto M = fossil::math::Algebra::matrix_identity(3);
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

FOSSIL_TEST_CASE(cpp_math_test_matrix_determinant) {
    std::vector<double> M{1, 2, 3, 4}; // 2x2
    double det = fossil::math::Algebra::matrix_determinant(M, 2);
    ASSUME_ITS_EQUAL_F64(det, -2.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_poly_eval) {
    std::vector<double> coeffs{1, 2, 3}; // 1 + 2x + 3x^2
    double val = fossil::math::Algebra::poly_eval(coeffs, 2.0);
    ASSUME_ITS_EQUAL_F64(val, 17.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_poly_derivative) {
    std::vector<double> coeffs{1, 2, 3}; // 1 + 2x + 3x^2
    auto deriv = fossil::math::Algebra::poly_derivative(coeffs);
    ASSUME_ITS_EQUAL_F64(deriv[0], 2.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(deriv[1], 6.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_poly_add) {
    std::vector<double> A{1, 2, 3}; // deg 2
    std::vector<double> B{4, 5};    // deg 1
    auto result = fossil::math::Algebra::poly_add(A, B);
    ASSUME_ITS_TRUE(result.size() == 3);
    ASSUME_ITS_EQUAL_F64(result[0], 5.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_poly_mul) {
    std::vector<double> A{1, 2}; // 1 + 2x
    std::vector<double> B{3, 4}; // 3 + 4x
    auto result = fossil::math::Algebra::poly_mul(A, B);
    ASSUME_ITS_TRUE(result.size() == 3);
    ASSUME_ITS_EQUAL_F64(result[0], 3.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[1], 10.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(result[2], 8.0, FOSSIL_TEST_FLOAT_EPSILON);
}

FOSSIL_TEST_CASE(cpp_math_test_solve_quadratic_real) {
    auto roots = fossil::math::Algebra::solve_quadratic(1, -3, 2); // x^2 - 3x + 2 = 0
    ASSUME_ITS_TRUE(
        (fabs(roots.first - 2.0) < FOSSIL_TEST_FLOAT_EPSILON && fabs(roots.second - 1.0) < FOSSIL_TEST_FLOAT_EPSILON) ||
        (fabs(roots.first - 1.0) < FOSSIL_TEST_FLOAT_EPSILON && fabs(roots.second - 2.0) < FOSSIL_TEST_FLOAT_EPSILON)
    );
}

FOSSIL_TEST_CASE(cpp_math_test_solve_quadratic_complex) {
    try {
        auto roots = fossil::math::Algebra::solve_quadratic(1, 0, 1); // x^2 + 1 = 0
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::runtime_error&) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_algebra_tests) {
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_matrix_transpose);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_matrix_identity);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_matrix_determinant);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_poly_eval);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_poly_derivative);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_poly_add);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_poly_mul);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_solve_quadratic_real);
    FOSSIL_TEST_ADD(cpp_algebra_fixture, cpp_math_test_solve_quadratic_complex);

    FOSSIL_TEST_REGISTER(cpp_algebra_fixture);
} // end of tests
