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

    /**
     * @class Algebra
     * @brief Provides high-level algebraic operations for vectors, matrices, and polynomials.
     *
     * This class offers static methods that wrap the C algebra functions for convenient use
     * in C++ code, using STL containers and exception handling.
     */
    class Algebra {
    public:
        /** 
         * Computes the dot product of two vectors.
         * @param a First input vector.
         * @param b Second input vector.
         * @return The dot product as a double.
         * @throws std::invalid_argument if the vectors are not the same length.
         */
        static double dot(const std::vector<double>& a, const std::vector<double>& b) {
            if (a.size() != b.size())
                throw std::invalid_argument("Vectors must be the same length");
            return fossil_math_algebra_dot(a.data(), b.data(), a.size());
        }

        /**
         * Adds two vectors element-wise.
         * @param a First input vector.
         * @param b Second input vector.
         * @return Resulting vector after addition.
         * @throws std::invalid_argument if the vectors are not the same length.
         */
        static std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) {
            if (a.size() != b.size())
                throw std::invalid_argument("Vectors must be the same length");
            std::vector<double> result(a.size());
            fossil_math_algebra_add(a.data(), b.data(), result.data(), a.size());
            return result;
        }

        /**
         * Subtracts vector b from vector a element-wise.
         * @param a First input vector.
         * @param b Second input vector.
         * @return Resulting vector after subtraction.
         * @throws std::invalid_argument if the vectors are not the same length.
         */
        static std::vector<double> sub(const std::vector<double>& a, const std::vector<double>& b) {
            if (a.size() != b.size())
                throw std::invalid_argument("Vectors must be the same length");
            std::vector<double> result(a.size());
            fossil_math_algebra_sub(a.data(), b.data(), result.data(), a.size());
            return result;
        }

        /**
         * Multiplies a vector by a scalar.
         * @param a Input vector.
         * @param scalar Scalar value to multiply.
         * @return Resulting vector after scalar multiplication.
         */
        static std::vector<double> scalar_mul(const std::vector<double>& a, double scalar) {
            std::vector<double> result(a.size());
            fossil_math_algebra_scalar_mul(a.data(), scalar, result.data(), a.size());
            return result;
        }

        /**
         * Multiplies two matrices.
         * @param A First matrix (flattened, row-major).
         * @param rowsA Number of rows in A.
         * @param colsA Number of columns in A.
         * @param B Second matrix (flattened, row-major).
         * @param rowsB Number of rows in B.
         * @param colsB Number of columns in B.
         * @return Resulting matrix (flattened, row-major).
         * @throws std::invalid_argument if matrix dimensions do not match for multiplication.
         * @throws std::runtime_error if multiplication fails.
         */
        static std::vector<double> matrix_mul(const std::vector<double>& A, size_t rowsA, size_t colsA,
                                              const std::vector<double>& B, size_t rowsB, size_t colsB) {
            if (colsA != rowsB)
                throw std::invalid_argument("Matrix dimensions do not match for multiplication");
            std::vector<double> C(rowsA * colsB);
            int status = fossil_math_algebra_matrix_mul(A.data(), rowsA, colsA, B.data(), rowsB, colsB, C.data());
            if (status != 0)
                throw std::runtime_error("Matrix multiplication failed");
            return C;
        }

        /**
         * Computes the transpose of a matrix.
         * @param A Input matrix (flattened, row-major).
         * @param rows Number of rows in A.
         * @param cols Number of columns in A.
         * @return Transposed matrix (flattened, row-major).
         * @throws std::runtime_error if transpose fails.
         */
        static std::vector<double> matrix_transpose(const std::vector<double>& A, size_t rows, size_t cols) {
            std::vector<double> T(cols * rows);
            int status = fossil_math_algebra_matrix_transpose(A.data(), rows, cols, T.data());
            if (status != 0)
                throw std::runtime_error("Matrix transpose failed");
            return T;
        }

        /**
         * Creates an identity matrix of size n x n.
         * @param n Size of the identity matrix.
         * @return Identity matrix (flattened, row-major).
         * @throws std::runtime_error if identity creation fails.
         */
        static std::vector<double> matrix_identity(size_t n) {
            std::vector<double> M(n * n, 0.0);
            int status = fossil_math_algebra_matrix_identity(M.data(), n);
            if (status != 0)
                throw std::runtime_error("Matrix identity creation failed");
            return M;
        }

        /**
         * Computes the determinant of a square matrix.
         * @param M Input matrix (flattened, row-major).
         * @param n Size of the matrix (n x n).
         * @return Determinant value.
         * @throws std::runtime_error if determinant computation fails.
         */
        static double matrix_determinant(const std::vector<double>& M, size_t n) {
            double det = 0.0;
            int status = fossil_math_algebra_matrix_determinant(M.data(), n, &det);
            if (status != 0)
                throw std::runtime_error("Matrix determinant computation failed");
            return det;
        }

        /**
         * Computes the inverse of a square matrix.
         * @param M Input matrix (flattened, row-major).
         * @param n Size of the matrix (n x n).
         * @return Inverse matrix (flattened, row-major).
         * @throws std::runtime_error if inversion fails.
         */
        static std::vector<double> matrix_inverse(const std::vector<double>& M, size_t n) {
            std::vector<double> Inv(n * n);
            int status = fossil_math_algebra_matrix_inverse(M.data(), n, Inv.data());
            if (status != 0)
                throw std::runtime_error("Matrix inversion failed");
            return Inv;
        }

        /**
         * Evaluates a polynomial at a given value.
         * @param coeffs Coefficient vector (coeffs[0] is constant term).
         * @param x Value at which to evaluate.
         * @return Evaluated polynomial value.
         */
        static double poly_eval(const std::vector<double>& coeffs, double x) {
            return fossil_math_algebra_poly_eval(coeffs.data(), coeffs.size() - 1, x);
        }

        /**
         * Computes the derivative of a polynomial.
         * @param coeffs Coefficient vector of the original polynomial.
         * @return Coefficient vector of the derivative.
         */
        static std::vector<double> poly_derivative(const std::vector<double>& coeffs) {
            if (coeffs.size() <= 1)
                return std::vector<double>{0.0};
            std::vector<double> deriv(coeffs.size() - 1);
            fossil_math_algebra_poly_derivative(coeffs.data(), coeffs.size() - 1, deriv.data());
            return deriv;
        }

        /**
         * Adds two polynomials.
         * @param A Coefficient vector of the first polynomial.
         * @param B Coefficient vector of the second polynomial.
         * @return Coefficient vector of the resulting polynomial.
         */
        static std::vector<double> poly_add(const std::vector<double>& A, const std::vector<double>& B) {
            size_t degA = A.size() - 1;
            size_t degB = B.size() - 1;
            size_t max_deg = std::max(degA, degB);
            std::vector<double> result(max_deg + 1, 0.0);
            size_t degR = 0;
            fossil_math_algebra_poly_add(A.data(), degA, B.data(), degB, result.data(), &degR);
            result.resize(degR + 1);
            return result;
        }

        /**
         * Multiplies two polynomials.
         * @param A Coefficient vector of the first polynomial.
         * @param B Coefficient vector of the second polynomial.
         * @return Coefficient vector of the resulting polynomial.
         */
        static std::vector<double> poly_mul(const std::vector<double>& A, const std::vector<double>& B) {
            size_t degA = A.size() - 1;
            size_t degB = B.size() - 1;
            std::vector<double> result(degA + degB + 1, 0.0);
            size_t degR = 0;
            fossil_math_algebra_poly_mul(A.data(), degA, B.data(), degB, result.data(), &degR);
            result.resize(degR + 1);
            return result;
        }

        /**
         * Solves a linear system Ax = b.
         * @param A Coefficient matrix (flattened, row-major, n x n).
         * @param b Right-hand side vector.
         * @param n Size of the system.
         * @return Solution vector x.
         * @throws std::invalid_argument if dimensions do not match.
         * @throws std::runtime_error if solution fails.
         */
        static std::vector<double> solve_linear_system(const std::vector<double>& A, const std::vector<double>& b, size_t n) {
            if (A.size() != n * n || b.size() != n)
                throw std::invalid_argument("Matrix and vector dimensions do not match for linear system");
            std::vector<double> x(n);
            int status = fossil_math_algebra_solve_linear_system(A.data(), b.data(), x.data(), n);
            if (status != 0)
                throw std::runtime_error("Linear system solution failed");
            return x;
        }

        /**
         * Solves a quadratic equation ax^2 + bx + c = 0 for real roots.
         * @param a Coefficient of x^2.
         * @param b Coefficient of x.
         * @param c Constant term.
         * @return Pair of real roots.
         * @throws std::runtime_error if no real roots exist.
         */
        static std::pair<double, double> solve_quadratic(double a, double b, double c) {
            double root1 = 0.0, root2 = 0.0;
            int status = fossil_math_algebra_solve_quadratic(a, b, c, &root1, &root2);
            if (status != 0)
                throw std::runtime_error("No real roots exist for the quadratic equation");
            return {root1, root2};
        }
    };

} // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_ALGEBRA_H */
