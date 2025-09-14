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

FOSSIL_TEST_SUITE(cpp_geom_fixture);

FOSSIL_SETUP(cpp_geom_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_geom_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_math_test_distance2d) {
    fossil_math_geom_point2d a = {0.0, 0.0};
    fossil_math_geom_point2d b = {3.0, 4.0};
    double dist = fossil::math::Geometry::distance_2d(a, b);
    ASSUME_ITS_EQUAL_F64(dist, 5.0, 1e-9);
}

FOSSIL_TEST_CASE(cpp_math_test_distance3d) {
    fossil_math_geom_point3d a = {1.0, 2.0, 3.0};
    fossil_math_geom_point3d b = {4.0, 6.0, 3.0};
    double dist = fossil::math::Geometry::distance_3d(a, b);
    ASSUME_ITS_EQUAL_F64(dist, 5.0, 1e-9);
}

FOSSIL_TEST_CASE(cpp_math_test_circle_area) {
    fossil_math_geom_circle c = {{0.0, 0.0}, 2.0};
    double area = fossil::math::Geometry::circle_area(c);
    ASSUME_ITS_EQUAL_F64(area, FOSSIL_MATH_PI * 4.0, 1e-9);
}

FOSSIL_TEST_CASE(cpp_math_test_circle_circumference) {
    fossil_math_geom_circle c = {{0.0, 0.0}, 2.0};
    double circ = fossil::math::Geometry::circle_circumference(c);
    ASSUME_ITS_EQUAL_F64(circ, 2.0 * FOSSIL_MATH_PI * 2.0, 1e-9);
}

FOSSIL_TEST_CASE(cpp_math_test_point_in_circle_inside) {
    fossil_math_geom_circle c = {{0.0, 0.0}, 5.0};
    fossil_math_geom_point2d p = {3.0, 4.0};
    bool inside = fossil::math::Geometry::point_in_circle(p, c);
    FOSSIL_TEST_ASSUME(inside, "Point should be inside the circle");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_geom_tests) {
    FOSSIL_TEST_ADD(cpp_geom_fixture, cpp_math_test_distance2d);
    FOSSIL_TEST_ADD(cpp_geom_fixture, cpp_math_test_distance3d);
    FOSSIL_TEST_ADD(cpp_geom_fixture, cpp_math_test_circle_area);
    FOSSIL_TEST_ADD(cpp_geom_fixture, cpp_math_test_circle_circumference);
    FOSSIL_TEST_ADD(cpp_geom_fixture, cpp_math_test_point_in_circle_inside);

    FOSSIL_TEST_REGISTER(cpp_geom_fixture);
} // end of tests
