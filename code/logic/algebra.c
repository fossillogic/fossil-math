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
#include "fossil/math/algebra.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

double fossil_math_algebra_dot(const double* a, const double* b, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++)
        sum += a[i] * b[i];
    return sum;
}

void fossil_math_algebra_add(const double* a, const double* b, double* result, size_t n) {
    for (size_t i = 0; i < n; i++)
        result[i] = a[i] + b[i];
}

void fossil_math_algebra_sub(const double* a, const double* b, double* result, size_t n) {
    for (size_t i = 0; i < n; i++)
        result[i] = a[i] - b[i];
}

void fossil_math_algebra_scalar_mul(const double* a, double scalar, double* result, size_t n) {
    for (size_t i = 0; i < n; i++)
        result[i] = a[i] * scalar;
}

int fossil_math_algebra_matrix_mul(const double* A, size_t rowsA, size_t colsA,
                                   const double* B, size_t rowsB, size_t colsB,
                                   double* C) {
    if (colsA != rowsB) return -1;

    for (size_t i = 0; i < rowsA; i++) {
        for (size_t j = 0; j < colsB; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < colsA; k++) {
                sum += A[i * colsA + k] * B[k * colsB + j];
            }
            C[i * colsB + j] = sum;
        }
    }
    return 0;
}

int fossil_math_algebra_matrix_transpose(const double* A, size_t rows, size_t cols, double* T) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            T[j * rows + i] = A[i * cols + j];
        }
    }
    return 0;
}

// ======================================================
// Matrix utilities
// ======================================================

int fossil_math_algebra_matrix_identity(double* M, size_t n) {
    if (!M) return -1;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            M[i * n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    return 0;
}

// Very naive recursive determinant (O(n!))
static double _determinant_recursive(const double* M, size_t n) {
    if (n == 1) return M[0];
    if (n == 2) return M[0]*M[3] - M[1]*M[2];

    double det = 0.0;
    for (size_t col = 0; col < n; col++) {
        size_t sub_size = n - 1;
        double* sub = malloc(sub_size * sub_size * sizeof(double));
        size_t sub_i = 0;

        for (size_t i = 1; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (j == col) continue;
                sub[sub_i++] = M[i * n + j];
            }
        }
        double cofactor = ((col % 2 == 0) ? 1.0 : -1.0) * M[col];
        det += cofactor * _determinant_recursive(sub, sub_size);
        free(sub);
    }
    return det;
}

int fossil_math_algebra_matrix_determinant(const double* M, size_t n, double* det) {
    if (!M || !det) return -1;
    *det = _determinant_recursive(M, n);
    return 0;
}

int fossil_math_algebra_matrix_inverse(const double* M, size_t n, double* Inv) {
    if (!M || !Inv) return -1;
    for (size_t i = 0; i < n * n; i++) {
        Inv[i] = (i % (n+1) == 0) ? 1.0 : 0.0; // identity, fake
    }
    return -2; // indicates not real inversion
}

// ======================================================
// Polynomial functions
// ======================================================

double fossil_math_algebra_poly_eval(const double* coeffs, size_t degree, double x) {
    double result = 0.0;
    for (size_t i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, (double)i);
    }
    return result;
}

void fossil_math_algebra_poly_derivative(const double* coeffs, size_t degree, double* deriv) {
    if (degree == 0) {
        deriv[0] = 0.0;
        return;
    }
    for (size_t i = 1; i <= degree; i++) {
        deriv[i - 1] = coeffs[i] * i;
    }
}

void fossil_math_algebra_poly_add(const double* A, size_t degA,
                                  const double* B, size_t degB,
                                  double* result, size_t* degR) {
    *degR = (degA > degB) ? degA : degB;
    for (size_t i = 0; i <= *degR; i++) {
        double a = (i <= degA) ? A[i] : 0.0;
        double b = (i <= degB) ? B[i] : 0.0;
        result[i] = a + b;
    }
}

void fossil_math_algebra_poly_mul(const double* A, size_t degA,
                                  const double* B, size_t degB,
                                  double* result, size_t* degR) {
    *degR = degA + degB;
    for (size_t i = 0; i <= *degR; i++) result[i] = 0.0;

    for (size_t i = 0; i <= degA; i++) {
        for (size_t j = 0; j <= degB; j++) {
            result[i + j] += A[i] * B[j];
        }
    }
}

// ======================================================
// Equation solvers
// ======================================================

int fossil_math_algebra_solve_linear_system(const double* A, const double* b,
                                            double* x, size_t n) {
    if (!A || !b || !x) return -1;
    for (size_t i = 0; i < n; i++) {
        x[i] = b[i]; // fake: assumes diagonal=1
    }
    return -2; // indicates not real solver
}

int fossil_math_algebra_solve_quadratic(double a, double b, double c,
                                        double* root1, double* root2) {
    if (fabs(a) < 1e-12) return -1; // Not quadratic
    double disc = b*b - 4*a*c;
    if (disc < 0) return -2; // Complex roots
    double sqrt_disc = sqrt(disc);
    *root1 = (-b + sqrt_disc) / (2*a);
    *root2 = (-b - sqrt_disc) / (2*a);
    return 0;
}
