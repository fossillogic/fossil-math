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
#include "fossil/math/tensor.h"

// ============================================================================
// Internal Helpers
// ============================================================================

static size_t fossil_math_tensor_size(const size_t* shape, size_t dims) {
    size_t total = 1;
    for (size_t i = 0; i < dims; ++i) {
        total *= shape[i];
    }
    return total;
}

static size_t fossil_math_tensor_index(const fossil_math_tensor_t* t, const size_t* idx) {
    size_t offset = 0;
    size_t stride = 1;
    for (size_t i = t->dims; i-- > 0;) {
        offset += idx[i] * stride;
        stride *= t->shape[i];
    }
    return offset;
}

static int fossil_math_tensor_shape_equal(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
    if (a->dims != b->dims) return 0;
    for (size_t i = 0; i < a->dims; ++i) {
        if (a->shape[i] != b->shape[i]) return 0;
    }
    return 1;
}

// ============================================================================
// Tensor Creation & Deletion
// ============================================================================

fossil_math_tensor_t* fossil_math_tensor_create(const size_t* shape, size_t dims) {
    if (!shape || dims == 0) return NULL;

    fossil_math_tensor_t* t = calloc(1, sizeof(fossil_math_tensor_t));
    if (!t) return NULL;

    t->dims = dims;
    t->shape = calloc(dims, sizeof(size_t));
    if (!t->shape) {
        free(t);
        return NULL;
    }
    memcpy(t->shape, shape, dims * sizeof(size_t));

    size_t total = fossil_math_tensor_size(shape, dims);
    t->data = calloc(total, sizeof(double));
    if (!t->data) {
        free(t->shape);
        free(t);
        return NULL;
    }

    return t;
}

void fossil_math_tensor_free(fossil_math_tensor_t* tensor) {
    if (!tensor) return;
    free(tensor->data);
    free(tensor->shape);
    free(tensor);
}

// ============================================================================
// Element Access
// ============================================================================

double fossil_math_tensor_get(const fossil_math_tensor_t* t, const size_t* idx) {
    if (!t || !t->data || !idx) return 0.0;
    size_t pos = fossil_math_tensor_index(t, idx);
    return t->data[pos];
}

void fossil_math_tensor_set(fossil_math_tensor_t* t, const size_t* idx, double value) {
    if (!t || !t->data || !idx) return;
    size_t pos = fossil_math_tensor_index(t, idx);
    t->data[pos] = value;
}

// ============================================================================
// Arithmetic Operations
// ============================================================================

fossil_math_tensor_t* fossil_math_tensor_add(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
    if (!a || !b || !a->data || !b->data) return NULL;
    if (!fossil_math_tensor_shape_equal(a, b)) return NULL;

    fossil_math_tensor_t* r = fossil_math_tensor_create(a->shape, a->dims);
    if (!r) return NULL;

    size_t total = fossil_math_tensor_size(a->shape, a->dims);
    for (size_t i = 0; i < total; ++i) {
        r->data[i] = a->data[i] + b->data[i];
    }
    return r;
}

fossil_math_tensor_t* fossil_math_tensor_mul(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
    if (!a || !b || !a->data || !b->data) return NULL;
    if (!fossil_math_tensor_shape_equal(a, b)) return NULL;

    fossil_math_tensor_t* r = fossil_math_tensor_create(a->shape, a->dims);
    if (!r) return NULL;

    size_t total = fossil_math_tensor_size(a->shape, a->dims);
    for (size_t i = 0; i < total; ++i) {
        r->data[i] = a->data[i] * b->data[i];
    }
    return r;
}

// ============================================================================
// Dot Product
// ============================================================================
//
// Supports simple 2D (matrix × matrix) and 1D (vector × vector) operations.
// For higher dimensions, behavior can be extended as needed.
//

fossil_math_tensor_t* fossil_math_tensor_dot(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
    if (!a || !b) return NULL;

    // 1D dot product
    if (a->dims == 1 && b->dims == 1 && a->shape[0] == b->shape[0]) {
        double sum = 0.0;
        for (size_t i = 0; i < a->shape[0]; ++i)
            sum += a->data[i] * b->data[i];
        fossil_math_tensor_t* r = fossil_math_tensor_create((size_t[]){1}, 1);
        r->data[0] = sum;
        return r;
    }

    // 2D matrix multiplication (m×n) × (n×p)
    if (a->dims == 2 && b->dims == 2 && a->shape[1] == b->shape[0]) {
        size_t m = a->shape[0], n = a->shape[1], p = b->shape[1];
        fossil_math_tensor_t* r = fossil_math_tensor_create((size_t[]){m, p}, 2);
        if (!r) return NULL;

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < p; ++j) {
                double sum = 0.0;
                for (size_t k = 0; k < n; ++k)
                    sum += a->data[i * n + k] * b->data[k * p + j];
                r->data[i * p + j] = sum;
            }
        }
        return r;
    }

    // Unsupported dimension
    return NULL;
}

// ============================================================================
// Fill and Print
// ============================================================================

void fossil_math_tensor_fill(fossil_math_tensor_t* t, double value) {
    if (!t || !t->data) return;
    size_t total = fossil_math_tensor_size(t->shape, t->dims);
    for (size_t i = 0; i < total; ++i) {
        t->data[i] = value;
    }
}

void fossil_math_tensor_print(const fossil_math_tensor_t* t) {
    if (!t || !t->data) {
        printf("(null tensor)\n");
        return;
    }

    printf("Tensor: dims=%zu, shape=[", t->dims);
    for (size_t i = 0; i < t->dims; ++i) {
        printf("%zu%s", t->shape[i], (i + 1 < t->dims) ? ", " : "");
    }
    printf("]\n");

    size_t total = fossil_math_tensor_size(t->shape, t->dims);
    for (size_t i = 0; i < total; ++i) {
        // Clamp output for display using FOSSIL_MATH_CLAMP macro
        double val = FOSSIL_MATH_CLAMP(t->data[i], -FOSSIL_MATH_TWO_PI, FOSSIL_MATH_TWO_PI);
        printf("%8.4f ", val);
        if ((i + 1) % t->shape[t->dims - 1] == 0)
            printf("\n");
    }
}
