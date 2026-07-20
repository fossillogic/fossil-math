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

FOSSIL_SUITE(cpp_tensor_fixture);

FOSSIL_SETUP(cpp_tensor_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_tensor_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_tensor_test_create_and_free) {
    std::vector<size_t> shape = {2, 3};
    fossil_math_tensor_t* t = fossil::math::Tensor::create(shape);
    ASSUME_ITS_TRUE(t != NULL);
    ASSUME_ITS_TRUE(t->dims == 2);
    ASSUME_ITS_TRUE(t->shape[0] == 2 && t->shape[1] == 3);
    fossil::math::Tensor::free(t);
}

FOSSIL_TEST(cpp_tensor_test_set_and_get) {
    std::vector<size_t> shape = {2, 2};
    fossil_math_tensor_t* t = fossil::math::Tensor::create(shape);
    std::vector<size_t> idx = {1, 0};
    fossil::math::Tensor::set(t, idx, 42.0);
    double val = fossil::math::Tensor::get(t, idx);
    ASSUME_ITS_EQUAL_F64(val, 42.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Tensor::free(t);
}

FOSSIL_TEST(cpp_tensor_test_fill) {
    std::vector<size_t> shape = {3};
    fossil_math_tensor_t* t = fossil::math::Tensor::create(shape);
    fossil::math::Tensor::fill(t, 7.0);
    for (size_t i = 0; i < 3; ++i) {
        std::vector<size_t> idx = {i};
        double val = fossil::math::Tensor::get(t, idx);
        ASSUME_ITS_EQUAL_F64(val, 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    }
    fossil::math::Tensor::free(t);
}

FOSSIL_TEST(cpp_tensor_test_add) {
    std::vector<size_t> shape = {2};
    fossil_math_tensor_t* a = fossil::math::Tensor::create(shape);
    std::vector<size_t> idx0 = {0}, idx1 = {1};
    fossil::math::Tensor::set(a, idx0, 1.0);
    fossil::math::Tensor::set(a, idx1, 2.0);

    fossil_math_tensor_t* b = fossil::math::Tensor::create(shape);
    fossil::math::Tensor::set(b, idx0, 3.0);
    fossil::math::Tensor::set(b, idx1, 4.0);

    fossil_math_tensor_t* r = fossil::math::Tensor::add(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, idx0), 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, idx1), 6.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil::math::Tensor::free(a);
    fossil::math::Tensor::free(b);
    fossil::math::Tensor::free(r);
}

FOSSIL_TEST(cpp_tensor_test_mul) {
    std::vector<size_t> shape = {2};
    fossil_math_tensor_t* a = fossil::math::Tensor::create(shape);
    std::vector<size_t> idx0 = {0}, idx1 = {1};
    fossil::math::Tensor::set(a, idx0, 2.0);
    fossil::math::Tensor::set(a, idx1, 3.0);

    fossil_math_tensor_t* b = fossil::math::Tensor::create(shape);
    fossil::math::Tensor::set(b, idx0, 4.0);
    fossil::math::Tensor::set(b, idx1, 5.0);

    fossil_math_tensor_t* r = fossil::math::Tensor::mul(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, idx0), 8.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, idx1), 15.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil::math::Tensor::free(a);
    fossil::math::Tensor::free(b);
    fossil::math::Tensor::free(r);
}

FOSSIL_TEST(cpp_tensor_test_dot_vector) {
    std::vector<size_t> shape = {3};
    fossil_math_tensor_t* a = fossil::math::Tensor::create(shape);
    fossil_math_tensor_t* b = fossil::math::Tensor::create(shape);
    for (size_t i = 0; i < 3; ++i) {
        std::vector<size_t> idx = {i};
        fossil::math::Tensor::set(a, idx, (double)(i + 1)); // 1,2,3
        fossil::math::Tensor::set(b, idx, (double)(i + 4)); // 4,5,6
    }
    fossil_math_tensor_t* r = fossil::math::Tensor::dot(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    std::vector<size_t> idx = {0};
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, idx), 32.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil::math::Tensor::free(a);
    fossil::math::Tensor::free(b);
    fossil::math::Tensor::free(r);
}

FOSSIL_TEST(cpp_tensor_test_dot_matrix) {
    std::vector<size_t> shapeA = {2, 2};
    std::vector<size_t> shapeB = {2, 2};
    fossil_math_tensor_t* a = fossil::math::Tensor::create(shapeA);
    fossil_math_tensor_t* b = fossil::math::Tensor::create(shapeB);
    // a = [[1,2],[3,4]], b = [[5,6],[7,8]]
    fossil::math::Tensor::set(a, {0,0}, 1.0);
    fossil::math::Tensor::set(a, {0,1}, 2.0);
    fossil::math::Tensor::set(a, {1,0}, 3.0);
    fossil::math::Tensor::set(a, {1,1}, 4.0);

    fossil::math::Tensor::set(b, {0,0}, 5.0);
    fossil::math::Tensor::set(b, {0,1}, 6.0);
    fossil::math::Tensor::set(b, {1,0}, 7.0);
    fossil::math::Tensor::set(b, {1,1}, 8.0);

    fossil_math_tensor_t* r = fossil::math::Tensor::dot(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, {0,0}), 19.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, {0,1}), 22.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, {1,0}), 43.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil::math::Tensor::get(r, {1,1}), 50.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil::math::Tensor::free(a);
    fossil::math::Tensor::free(b);
    fossil::math::Tensor::free(r);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_tensor_tests) {
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_create_and_free);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_set_and_get);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_fill);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_add);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_mul);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_dot_vector);
    FOSSIL_ADD_TEST(cpp_tensor_fixture, cpp_tensor_test_dot_matrix);

    FOSSIL_ADD_SUITE(cpp_tensor_fixture);
} // end of tests
