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

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/** 
 * Computes the dot product of two vectors a and b of length n.
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @param n Number of elements in each vector.
 * @return The dot product as a double.
 */
double fossil_math_algebra_dot(const double* a, const double* b, size_t n);

/** 
 * Adds two vectors a and b of length n and stores the result in result.
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @param result Pointer to the result vector.
 * @param n Number of elements in each vector.
 */
void fossil_math_algebra_add(const double* a, const double* b, double* result, size_t n);

/** 
 * Subtracts vector b from vector a, both of length n, and stores the result in result.
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @param result Pointer to the result vector.
 * @param n Number of elements in each vector.
 */
void fossil_math_algebra_sub(const double* a, const double* b, double* result, size_t n);

/** 
 * Multiplies vector a by a scalar and stores the result in result.
 * @param a Pointer to the input vector.
 * @param scalar Scalar value to multiply with.
 * @param result Pointer to the result vector.
 * @param n Number of elements in the vector.
 */
void fossil_math_algebra_scalar_mul(const double* a, double scalar, double* result, size_t n);

/** 
 * Multiplies two matrices A and B and stores the result in matrix C.
 * @param A Pointer to the first matrix (rowsA x colsA).
 * @param rowsA Number of rows in matrix A.
 * @param colsA Number of columns in matrix A.
 * @param B Pointer to the second matrix (rowsB x colsB).
 * @param rowsB Number of rows in matrix B.
 * @param colsB Number of columns in matrix B.
 * @param C Pointer to the result matrix (rowsA x colsB).
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_matrix_mul(const double* A, size_t rowsA, size_t colsA,
                                   const double* B, size_t rowsB, size_t colsB,
                                   double* C);

/** 
 * Computes the transpose of a matrix A and stores the result in T.
 * @param A Pointer to the input matrix (rows x cols).
 * @param rows Number of rows in matrix A.
 * @param cols Number of columns in matrix A.
 * @param T Pointer to the transposed matrix (cols x rows).
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_matrix_transpose(const double* A, size_t rows, size_t cols, double* T);

/** 
 * Creates an identity matrix of size n x n and stores it in M.
 * @param M Pointer to the matrix to be set as identity.
 * @param n Size of the matrix (n x n).
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_matrix_identity(double* M, size_t n);

/** 
 * Computes the determinant of a square matrix M of size n x n.
 * @param M Pointer to the input matrix.
 * @param n Size of the matrix (n x n).
 * @param det Pointer to the variable to store the determinant.
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_matrix_determinant(const double* M, size_t n, double* det);

/** 
 * Computes the inverse of a square matrix M of size n x n and stores it in Inv.
 * @param M Pointer to the input matrix.
 * @param n Size of the matrix (n x n).
 * @param Inv Pointer to the output inverse matrix.
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_matrix_inverse(const double* M, size_t n, double* Inv);

/** 
 * Evaluates a polynomial at a given value x.
 * @param coeffs Pointer to the array of coefficients (coeff[0] is constant term).
 * @param degree Degree of the polynomial.
 * @param x Value at which to evaluate the polynomial.
 * @return The evaluated value as a double.
 */
double fossil_math_algebra_poly_eval(const double* coeffs, size_t degree, double x);

/** 
 * Computes the derivative of a polynomial.
 * @param coeffs Pointer to the array of coefficients of the original polynomial.
 * @param degree Degree of the original polynomial.
 * @param deriv Pointer to the array to store the derivative coefficients.
 */
void fossil_math_algebra_poly_derivative(const double* coeffs, size_t degree, double* deriv);

/** 
 * Adds two polynomials A and B and stores the result in result.
 * @param A Pointer to the coefficients of the first polynomial.
 * @param degA Degree of the first polynomial.
 * @param B Pointer to the coefficients of the second polynomial.
 * @param degB Degree of the second polynomial.
 * @param result Pointer to the result coefficients array.
 * @param degR Pointer to the degree of the resulting polynomial.
 */
void fossil_math_algebra_poly_add(const double* A, size_t degA,
                                  const double* B, size_t degB,
                                  double* result, size_t* degR);

/** 
 * Multiplies two polynomials A and B and stores the result in result.
 * @param A Pointer to the coefficients of the first polynomial.
 * @param degA Degree of the first polynomial.
 * @param B Pointer to the coefficients of the second polynomial.
 * @param degB Degree of the second polynomial.
 * @param result Pointer to the result coefficients array.
 * @param degR Pointer to the degree of the resulting polynomial.
 */
void fossil_math_algebra_poly_mul(const double* A, size_t degA,
                                  const double* B, size_t degB,
                                  double* result, size_t* degR);

/** 
 * Solves a linear system Ax = b for x, where A is an n x n matrix and b is a vector.
 * @param A Pointer to the coefficient matrix (n x n).
 * @param b Pointer to the right-hand side vector.
 * @param x Pointer to the solution vector.
 * @param n Size of the system.
 * @return 0 on success, non-zero on failure.
 */
int fossil_math_algebra_solve_linear_system(const double* A, const double* b,
                                            double* x, size_t n);

/** 
 * Solves a quadratic equation ax^2 + bx + c = 0 for real roots.
 * @param a Coefficient of x^2.
 * @param b Coefficient of x.
 * @param c Constant term.
 * @param root1 Pointer to store the first root.
 * @param root2 Pointer to store the second root.
 * @return 0 on success, non-zero if no real roots exist.
 */
int fossil_math_algebra_solve_quadratic(double a, double b, double c,
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
