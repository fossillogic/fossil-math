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

FOSSIL_SUITE(c_tensor_fixture);

FOSSIL_SETUP(c_tensor_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_tensor_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_tensor_test_create_and_free) {
    size_t shape[] = {2, 3};
    fossil_math_tensor_t* t = fossil_math_tensor_create(shape, 2);
    ASSUME_ITS_TRUE(t != NULL);
    ASSUME_ITS_TRUE(t->dims == 2);
    ASSUME_ITS_TRUE(t->shape[0] == 2 && t->shape[1] == 3);
    fossil_math_tensor_free(t);
}

FOSSIL_TEST(c_tensor_test_set_and_get) {
    size_t shape[] = {2, 2};
    fossil_math_tensor_t* t = fossil_math_tensor_create(shape, 2);
    size_t idx[] = {1, 0};
    fossil_math_tensor_set(t, idx, 42.0);
    double val = fossil_math_tensor_get(t, idx);
    ASSUME_ITS_EQUAL_F64(val, 42.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_tensor_free(t);
}

FOSSIL_TEST(c_tensor_test_fill) {
    size_t shape[] = {3};
    fossil_math_tensor_t* t = fossil_math_tensor_create(shape, 1);
    fossil_math_tensor_fill(t, 7.0);
    for (size_t i = 0; i < 3; ++i) {
        size_t idx[] = {i};
        double val = fossil_math_tensor_get(t, idx);
        ASSUME_ITS_EQUAL_F64(val, 7.0, FOSSIL_TEST_FLOAT_EPSILON);
    }
    fossil_math_tensor_free(t);
}

FOSSIL_TEST(c_tensor_test_add) {
    size_t shape[] = {2};
    fossil_math_tensor_t* a = fossil_math_tensor_create(shape, 1);
    size_t idx0[] = {0}, idx1[] = {1};
    fossil_math_tensor_set(a, idx0, 1.0);
    fossil_math_tensor_set(a, idx1, 2.0);

    fossil_math_tensor_t* b = fossil_math_tensor_create(shape, 1);
    fossil_math_tensor_set(b, idx0, 3.0);
    fossil_math_tensor_set(b, idx1, 4.0);

    fossil_math_tensor_t* r = fossil_math_tensor_add(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, idx0), 4.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, idx1), 6.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil_math_tensor_free(a);
    fossil_math_tensor_free(b);
    fossil_math_tensor_free(r);
}

FOSSIL_TEST(c_tensor_test_mul) {
    size_t shape[] = {2};
    fossil_math_tensor_t* a = fossil_math_tensor_create(shape, 1);
    size_t idx0[] = {0}, idx1[] = {1};
    fossil_math_tensor_set(a, idx0, 2.0);
    fossil_math_tensor_set(a, idx1, 3.0);

    fossil_math_tensor_t* b = fossil_math_tensor_create(shape, 1);
    fossil_math_tensor_set(b, idx0, 4.0);
    fossil_math_tensor_set(b, idx1, 5.0);

    fossil_math_tensor_t* r = fossil_math_tensor_mul(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, idx0), 8.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, idx1), 15.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil_math_tensor_free(a);
    fossil_math_tensor_free(b);
    fossil_math_tensor_free(r);
}

FOSSIL_TEST(c_tensor_test_dot_vector) {
    size_t shape[] = {3};
    fossil_math_tensor_t* a = fossil_math_tensor_create(shape, 1);
    fossil_math_tensor_t* b = fossil_math_tensor_create(shape, 1);
    for (size_t i = 0; i < 3; ++i) {
        size_t idx[] = {i};
        fossil_math_tensor_set(a, idx, (double)(i + 1)); // 1,2,3
        fossil_math_tensor_set(b, idx, (double)(i + 4)); // 4,5,6
    }
    fossil_math_tensor_t* r = fossil_math_tensor_dot(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    size_t idx[] = {0};
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, idx), 32.0, FOSSIL_TEST_FLOAT_EPSILON);
    fossil_math_tensor_free(a);
    fossil_math_tensor_free(b);
    fossil_math_tensor_free(r);
}

FOSSIL_TEST(c_tensor_test_dot_matrix) {
    size_t shapeA[] = {2, 2};
    size_t shapeB[] = {2, 2};
    fossil_math_tensor_t* a = fossil_math_tensor_create(shapeA, 2);
    fossil_math_tensor_t* b = fossil_math_tensor_create(shapeB, 2);
    // a = [[1,2],[3,4]], b = [[5,6],[7,8]]
    fossil_math_tensor_set(a, (size_t[]){0,0}, 1.0);
    fossil_math_tensor_set(a, (size_t[]){0,1}, 2.0);
    fossil_math_tensor_set(a, (size_t[]){1,0}, 3.0);
    fossil_math_tensor_set(a, (size_t[]){1,1}, 4.0);

    fossil_math_tensor_set(b, (size_t[]){0,0}, 5.0);
    fossil_math_tensor_set(b, (size_t[]){0,1}, 6.0);
    fossil_math_tensor_set(b, (size_t[]){1,0}, 7.0);
    fossil_math_tensor_set(b, (size_t[]){1,1}, 8.0);

    fossil_math_tensor_t* r = fossil_math_tensor_dot(a, b);
    ASSUME_ITS_TRUE(r != NULL);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, (size_t[]){0,0}), 19.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, (size_t[]){0,1}), 22.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, (size_t[]){1,0}), 43.0, FOSSIL_TEST_FLOAT_EPSILON);
    ASSUME_ITS_EQUAL_F64(fossil_math_tensor_get(r, (size_t[]){1,1}), 50.0, FOSSIL_TEST_FLOAT_EPSILON);

    fossil_math_tensor_free(a);
    fossil_math_tensor_free(b);
    fossil_math_tensor_free(r);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_tensor_tests) {
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_create_and_free);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_set_and_get);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_fill);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_add);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_mul);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_dot_vector);
    FOSSIL_ADD_TEST(c_tensor_fixture, c_tensor_test_dot_matrix);

    FOSSIL_ADD_SUITE(c_tensor_fixture);
} // end of tests
