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
#ifndef FOSSIL_MATH_SYMBOLIC_H
#define FOSSIL_MATH_SYMBOLIC_H

#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ============================================================================
// Symbolic Expression Types and Structures
// ============================================================================

/**
 * @brief Enum representing the type of a symbolic expression node.
 *
 * - fossil_math_sym_CONST: Represents a constant numeric value.
 * - fossil_math_sym_VAR:   Represents a variable (e.g., 'x', 'y').
 * - fossil_math_sym_OP:    Represents an operator node (e.g., '+', '-', '*', '/').
 */
typedef enum {
    fossil_math_sym_CONST, ///< Constant value node
    fossil_math_sym_VAR,   ///< Variable node
    fossil_math_sym_OP     ///< Operator node
} fossil_math_sym_type_t;

/**
 * @brief Forward declaration for the symbolic expression structure.
 *
 * This allows for recursive pointers within the structure.
 */
typedef struct fossil_math_sym_expr_t fossil_math_sym_expr_t;

/**
 * @brief Structure representing a symbolic expression tree node.
 *
 * Each node can be a constant, variable, or operator. Operator nodes
 * have left and right children representing sub-expressions.
 *
 * Members:
 * - type:  Type of the node (constant, variable, operator).
 * - op:    Operator character (valid if type == fossil_math_sym_OP).
 * - value: Numeric value (valid if type == fossil_math_sym_CONST).
 * - name:  Variable name (valid if type == fossil_math_sym_VAR).
 * - left:  Pointer to left child (valid if type == fossil_math_sym_OP).
 * - right: Pointer to right child (valid if type == fossil_math_sym_OP).
 */
struct fossil_math_sym_expr_t {
    fossil_math_sym_type_t type;        ///< Node type
    char op;                      ///< Operator character ('+', '-', '*', '/'), if applicable
    double value;                 ///< Constant value, if applicable
    char name[32];                ///< Variable name, if applicable
    fossil_math_sym_expr_t* left;      ///< Left sub-expression (for operators)
    fossil_math_sym_expr_t* right;     ///< Right sub-expression (for operators)
};

// ============================================================================
// Symbolic Expression Functions
// ============================================================================

/**
 * @brief Parses a string into a symbolic expression tree.
 *
 * @param expr String containing the mathematical expression.
 * @return Pointer to the root of the symbolic expression tree.
 *
 * The returned tree must be freed using fossil_math_sym_free().
 */
fossil_math_sym_expr_t* fossil_math_sym_parse(const char* expr);

/**
 * @brief Frees the memory associated with a symbolic expression tree.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 */
void fossil_math_sym_free(fossil_math_sym_expr_t* expr);

/**
 * @brief Simplifies a symbolic expression tree.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 * @return Pointer to the simplified symbolic expression tree.
 *
 * The returned tree may be a new allocation; free it with fossil_math_sym_free().
 */
fossil_math_sym_expr_t* fossil_math_sym_simplify(fossil_math_sym_expr_t* expr);

/**
 * @brief Computes the symbolic derivative of an expression with respect to a variable.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 * @param var Name of the variable to differentiate with respect to.
 * @return Pointer to the symbolic derivative expression tree.
 *
 * The returned tree must be freed using fossil_math_sym_free().
 */
fossil_math_sym_expr_t* fossil_math_sym_diff(const fossil_math_sym_expr_t* expr, const char* var);

/**
 * @brief Evaluates a symbolic expression tree numerically.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 * @param var_lookup Function pointer to look up variable values by name.
 * @return Numeric result of the evaluation.
 *
 * The var_lookup function should return the value of a variable given its name.
 */
double fossil_math_sym_eval(const fossil_math_sym_expr_t* expr, double (*var_lookup)(const char*));

/**
 * @brief Converts a symbolic expression tree to a human-readable string.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 * @param buffer Buffer to write the string representation into.
 * @param bufsize Size of the buffer.
 * @return Number of characters written (excluding null terminator).
 *
 * The buffer should be large enough to hold the resulting string.
 */
size_t fossil_math_sym_to_string(const fossil_math_sym_expr_t* expr, char* buffer, size_t bufsize);

/**
 * @brief Substitutes a variable in the symbolic expression tree with a constant value.
 *
 * @param expr Pointer to the root of the symbolic expression tree.
 * @param var Name of the variable to substitute.
 * @param value Value to substitute for the variable.
 * @return Pointer to the new symbolic expression tree with substitution applied.
 *
 * The returned tree must be freed using fossil_math_sym_free().
 */
fossil_math_sym_expr_t* fossil_math_sym_substitute(const fossil_math_sym_expr_t* expr, const char* var, double value);

#ifdef __cplusplus
}
#include <stdexcept>
#include <functional>
#include <vector>
#include <string>

namespace fossil {

    namespace math {

        /**
         * @brief Symbolic Expression utility class providing static methods for symbolic math operations.
         *
         * This class wraps the C symbolic expression functions in a C++-friendly interface,
         * allowing for easier use in C++ codebases. All methods are static and
         * operate directly on the provided structures.
         */
        class Symbolic {
        public:
            /**
             * @brief Parses a string into a symbolic expression tree.
             * @param expr String containing the mathematical expression.
             * @return Pointer to the root of the symbolic expression tree.
             */
            static fossil_math_sym_expr_t* parse(const std::string& expr) {
            return fossil_math_sym_parse(expr.c_str());
            }

            /**
             * @brief Frees the memory associated with a symbolic expression tree.
             * @param expr Pointer to the root of the symbolic expression tree.
             */
            static void free(fossil_math_sym_expr_t* expr) {
            fossil_math_sym_free(expr);
            }

            /**
             * @brief Simplifies a symbolic expression tree.
             * @param expr Pointer to the root of the symbolic expression tree.
             * @return Pointer to the simplified symbolic expression tree.
             */
            static fossil_math_sym_expr_t* simplify(fossil_math_sym_expr_t* expr) {
            return fossil_math_sym_simplify(expr);
            }

            /**
             * @brief Computes the symbolic derivative of an expression with respect to a variable.
             * @param expr Pointer to the root of the symbolic expression tree.
             * @param var Name of the variable to differentiate with respect to.
             * @return Pointer to the symbolic derivative expression tree.
             */
            static fossil_math_sym_expr_t* diff(const fossil_math_sym_expr_t* expr, const std::string& var) {
            return fossil_math_sym_diff(expr, var.c_str());
            }

            /**
             * @brief Converts a symbolic expression tree to a string representation.
             * @param expr Pointer to the root of the symbolic expression tree.
             * @param buffer Buffer to write the string representation into.
             * @param bufsize Size of the buffer.
             * @return Number of characters written (excluding null terminator).
             */
            static size_t to_string(const fossil_math_sym_expr_t* expr, char* buffer, size_t bufsize) {
                return fossil_math_sym_to_string(expr, buffer, bufsize);
            }

            /**
             * @brief Substitutes a variable in the symbolic expression tree with a constant value.
             * @param expr Pointer to the root of the symbolic expression tree.
             * @param var Name of the variable to substitute.
             * @param value Value to substitute for the variable.
             * @return Pointer to the new symbolic expression tree with substitution applied.
             */
            static fossil_math_sym_expr_t* substitute(const fossil_math_sym_expr_t* expr, const std::string& var, double value) {
                return fossil_math_sym_substitute(expr, var.c_str(), value);
            }

            /**
             * @brief Evaluates a symbolic expression tree numerically.
             * @param expr Pointer to the root of the symbolic expression tree.
             * @param var_lookup Function to look up variable values by name.
             * @return Numeric result of the evaluation.
             */
            static double eval(const fossil_math_sym_expr_t* expr, const std::function<double(const std::string&)>& var_lookup) {
            // Adapter to convert std::string to const char*
            struct Adapter {
                static double call(const char* name, void* ctx) {
                auto* fn = static_cast<const std::function<double(const std::string&)>*>(ctx);
                return (*fn)(std::string(name));
                }
            };

            // Unfortunately, fossil_math_sym_eval only accepts double (*)(const char*),
            // so we can't pass context. For simple cases, use a static or global lookup.
            // For advanced use, provide a C-compatible lookup function.
            // Here, we assume var_lookup can be wrapped as needed.
            // For now, use a static variable as workaround.
            static const std::function<double(const std::string&)>* fn_ptr = nullptr;
            fn_ptr = &var_lookup;
            auto c_lookup = [](const char* name) -> double {
                return (*fn_ptr)(std::string(name));
            };
            return fossil_math_sym_eval(expr, c_lookup);
            }
        };

    } // namespace math

} // namespace fossil

#endif

#endif /* FOSSIL_MATH_GEOM_H */
