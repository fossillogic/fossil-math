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
#ifndef FOSSIL_MATH_ALGEBRA_H
#define FOSSIL_MATH_ALGEBRA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Function prototypes
// *****************************************************************************

// --- Basic operations ---
double fossil_math_algebra_dot(const double* a, const double* b, size_t n);
void   fossil_math_algebra_add(const double* a, const double* b, double* result, size_t n);
void   fossil_math_algebra_sub(const double* a, const double* b, double* result, size_t n);
void   fossil_math_algebra_scalar_mul(const double* a, double scalar, double* result, size_t n);

// --- Matrix operations ---
int    fossil_math_algebra_matrix_mul(const double* A, size_t rowsA, size_t colsA,
                                      const double* B, size_t rowsB, size_t colsB,
                                      double* C); // C has size rowsA x colsB

int    fossil_math_algebra_matrix_transpose(const double* A, size_t rows, size_t cols, double* T);

// ======================================================
// Vector operations
// ======================================================
double fossil_math_algebra_dot(const double* a, const double* b, size_t n);
void   fossil_math_algebra_add(const double* a, const double* b, double* result, size_t n);
void   fossil_math_algebra_sub(const double* a, const double* b, double* result, size_t n);
void   fossil_math_algebra_scalar_mul(const double* a, double scalar, double* result, size_t n);

// ======================================================
// Matrix operations
// ======================================================
int    fossil_math_algebra_matrix_mul(const double* A, size_t rowsA, size_t colsA,
                                      const double* B, size_t rowsB, size_t colsB,
                                      double* C);

int    fossil_math_algebra_matrix_transpose(const double* A, size_t rows, size_t cols, double* T);

int    fossil_math_algebra_matrix_identity(double* M, size_t n);
int    fossil_math_algebra_matrix_determinant(const double* M, size_t n, double* det);
int    fossil_math_algebra_matrix_inverse(const double* M, size_t n, double* Inv);

// ======================================================
// Polynomial operations
// Represented as array of coefficients, coeff[0] = constant
// ======================================================
double fossil_math_algebra_poly_eval(const double* coeffs, size_t degree, double x);
void   fossil_math_algebra_poly_derivative(const double* coeffs, size_t degree, double* deriv);
void   fossil_math_algebra_poly_add(const double* A, size_t degA,
                                    const double* B, size_t degB,
                                    double* result, size_t* degR);
void   fossil_math_algebra_poly_mul(const double* A, size_t degA,
                                    const double* B, size_t degB,
                                    double* result, size_t* degR);

// ======================================================
// Equation solving
// ======================================================
int    fossil_math_algebra_solve_linear_system(const double* A, const double* b,
                                               double* x, size_t n);

int    fossil_math_algebra_solve_quadratic(double a, double b, double c,
                                           double* root1, double* root2);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

namespace math {



} // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_ALGEBRA_H */
