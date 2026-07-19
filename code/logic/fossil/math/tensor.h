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
#ifndef FOSSIL_MATH_TENSOR_H
#define FOSSIL_MATH_TENSOR_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ======================================================
// Tensor structure and function prototypes
// ======================================================
typedef struct fossil_math_tensor_t {
    double* data;
    size_t* shape;
    size_t dims;
} fossil_math_tensor_t;

/**
 * @brief Creates a new tensor with the given shape and dimensions.
 * @param shape Array specifying the size of each dimension.
 * @param dims Number of dimensions.
 * @return Pointer to the newly created tensor.
 */
fossil_math_tensor_t* fossil_math_tensor_create(const size_t* shape, size_t dims);

/**
 * @brief Frees the memory associated with a tensor.
 * @param tensor Pointer to the tensor to free.
 */
void fossil_math_tensor_free(fossil_math_tensor_t* tensor);

/**
 * @brief Gets the value at the specified index in the tensor.
 * @param t Pointer to the tensor.
 * @param idx Array specifying the index for each dimension.
 * @return Value at the specified index.
 */
double fossil_math_tensor_get(const fossil_math_tensor_t* t, const size_t* idx);

/**
 * @brief Sets the value at the specified index in the tensor.
 * @param t Pointer to the tensor.
 * @param idx Array specifying the index for each dimension.
 * @param value Value to set.
 */
void fossil_math_tensor_set(fossil_math_tensor_t* t, const size_t* idx, double value);

/**
 * @brief Adds two tensors element-wise.
 * @param a Pointer to the first tensor.
 * @param b Pointer to the second tensor.
 * @return Pointer to the resulting tensor.
 */
fossil_math_tensor_t* fossil_math_tensor_add(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b);

/**
 * @brief Multiplies two tensors element-wise.
 * @param a Pointer to the first tensor.
 * @param b Pointer to the second tensor.
 * @return Pointer to the resulting tensor.
 */
fossil_math_tensor_t* fossil_math_tensor_mul(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b);

/**
 * @brief Computes the dot product of two tensors.
 * @param a Pointer to the first tensor.
 * @param b Pointer to the second tensor.
 * @return Pointer to the resulting tensor.
 */
fossil_math_tensor_t* fossil_math_tensor_dot(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b);

/**
 * @brief Fills the tensor with the specified value.
 * @param t Pointer to the tensor.
 * @param value Value to fill.
 */
void fossil_math_tensor_fill(fossil_math_tensor_t* t, double value);

/**
 * @brief Prints the contents of the tensor.
 * @param t Pointer to the tensor.
 */
void fossil_math_tensor_print(const fossil_math_tensor_t* t);

#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

    namespace math {

        /**
         * @brief Tensor utility class providing static methods for common tensor operations.
         *
         * This class wraps the C tensor functions in a C++-friendly interface,
         * allowing for easier use in C++ codebases. All methods are static and
         * operate directly on the provided structures.
         */
        class Tensor {
        public:
            /**
             * @brief Creates a new tensor with the given shape and dimensions.
             * @param shape Vector specifying the size of each dimension.
             * @return Pointer to the newly created tensor.
             */
            static fossil_math_tensor_t* create(const std::vector<size_t>& shape) {
            return fossil_math_tensor_create(shape.data(), shape.size());
            }

            /**
             * @brief Frees the memory associated with a tensor.
             * @param tensor Pointer to the tensor to free.
             */
            static void free(fossil_math_tensor_t* tensor) {
            fossil_math_tensor_free(tensor);
            }

            /**
             * @brief Gets the value at the specified index in the tensor.
             * @param t Pointer to the tensor.
             * @param idx Vector specifying the index for each dimension.
             * @return Value at the specified index.
             */
            static double get(const fossil_math_tensor_t* t, const std::vector<size_t>& idx) {
            return fossil_math_tensor_get(t, idx.data());
            }

            /**
             * @brief Sets the value at the specified index in the tensor.
             * @param t Pointer to the tensor.
             * @param idx Vector specifying the index for each dimension.
             * @param value Value to set.
             */
            static void set(fossil_math_tensor_t* t, const std::vector<size_t>& idx, double value) {
            fossil_math_tensor_set(t, idx.data(), value);
            }

            /**
             * @brief Adds two tensors element-wise.
             * @param a Pointer to the first tensor.
             * @param b Pointer to the second tensor.
             * @return Pointer to the resulting tensor.
             */
            static fossil_math_tensor_t* add(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
            return fossil_math_tensor_add(a, b);
            }

            /**
             * @brief Multiplies two tensors element-wise.
             * @param a Pointer to the first tensor.
             * @param b Pointer to the second tensor.
             * @return Pointer to the resulting tensor.
             */
            static fossil_math_tensor_t* mul(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
            return fossil_math_tensor_mul(a, b);
            }

            /**
             * @brief Computes the dot product of two tensors.
             * @param a Pointer to the first tensor.
             * @param b Pointer to the second tensor.
             * @return Pointer to the resulting tensor.
             */
            static fossil_math_tensor_t* dot(const fossil_math_tensor_t* a, const fossil_math_tensor_t* b) {
            return fossil_math_tensor_dot(a, b);
            }

            /**
             * @brief Fills the tensor with the specified value.
             * @param t Pointer to the tensor.
             * @param value Value to fill.
             */
            static void fill(fossil_math_tensor_t* t, double value) {
            fossil_math_tensor_fill(t, value);
            }

            /**
             * @brief Prints the contents of the tensor.
             * @param t Pointer to the tensor.
             */
            static void print(const fossil_math_tensor_t* t) {
            fossil_math_tensor_print(t);
            }
        };

    } // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_GEOM_H */
