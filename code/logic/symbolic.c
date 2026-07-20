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
#include "fossil/math/symbolic.h"
#include <math.h>

// ============================================================================
// Internal Helpers
// ============================================================================

static fossil_math_sym_expr_t* fossil_math_sym_new_const(double value);
static fossil_math_sym_expr_t* fossil_math_sym_new_var(const char* name);
static fossil_math_sym_expr_t* fossil_math_sym_new_op(char op, fossil_math_sym_expr_t* left, fossil_math_sym_expr_t* right);
static const char* fossil_math_sym_parse_expr(const char* s, fossil_math_sym_expr_t** out);
static double fossil_math_sym_eval_internal(const fossil_math_sym_expr_t* expr, double (*var_lookup)(const char*));

// ============================================================================
// Node Constructors
// ============================================================================

static fossil_math_sym_expr_t* fossil_math_sym_new_const(double value) {
    fossil_math_sym_expr_t* e = calloc(1, sizeof(*e));
    if (!e) return NULL;
    e->type = fossil_math_sym_CONST;
    e->value = value;
    return e;
}

static fossil_math_sym_expr_t* fossil_math_sym_new_var(const char* name) {
    fossil_math_sym_expr_t* e = calloc(1, sizeof(*e));
    if (!e) return NULL;
    e->type = fossil_math_sym_VAR;
    strncpy(e->name, name, sizeof(e->name) - 1);
    e->name[sizeof(e->name) - 1] = '\0';
    return e;
}

static fossil_math_sym_expr_t* fossil_math_sym_new_op(char op, fossil_math_sym_expr_t* left, fossil_math_sym_expr_t* right) {
    fossil_math_sym_expr_t* e = calloc(1, sizeof(*e));
    if (!e) return NULL;
    e->type = fossil_math_sym_OP;
    e->op = op;
    e->left = left;
    e->right = right;
    return e;
}

// ============================================================================
// Free Expression Tree
// ============================================================================

void fossil_math_sym_free(fossil_math_sym_expr_t* expr) {
    if (!expr) return;
    fossil_math_sym_free(expr->left);
    fossil_math_sym_free(expr->right);
    free(expr);
}

// ============================================================================
// Parser (simple recursive descent)
// ============================================================================
//
// Grammar (lowest → highest precedence):
//   expr   = term { ('+'|'-') term }
//   term   = factor { ('*'|'/') factor }
//   factor = number | variable | '(' expr ')'
//
// ============================================================================

static const char* fossil_math_sym_parse_number(const char* s, double* out) {
    char* end;
    *out = strtod(s, &end);
    return (end == s) ? NULL : end;
}

static int fossil_math_sym_is_const_name(const char* s, size_t* len, double* value) {
    // Recognize constants: pi, e, ln2, ln10, sqrt2, sqrt1_2, deg2rad, rad2deg, log2e, log10e, two_pi, half_pi
    struct { const char* name; double val; } table[] = {
        { "pi",       FOSSIL_MATH_PI },
        { "e",        FOSSIL_MATH_E },
        { "ln2",      FOSSIL_MATH_LN2 },
        { "ln10",     FOSSIL_MATH_LN10 },
        { "sqrt2",    FOSSIL_MATH_SQRT2 },
        { "sqrt1_2",  FOSSIL_MATH_SQRT1_2 },
        { "deg2rad",  FOSSIL_MATH_DEG2RAD },
        { "rad2deg",  FOSSIL_MATH_RAD2DEG },
        { "log2e",    FOSSIL_MATH_LOG2E },
        { "log10e",   FOSSIL_MATH_LOG10E },
        { "two_pi",   FOSSIL_MATH_TWO_PI },
        { "half_pi",  FOSSIL_MATH_HALF_PI },
    };
    for (size_t i = 0; i < sizeof(table)/sizeof(table[0]); ++i) {
        size_t nlen = strlen(table[i].name);
        if (strncmp(s, table[i].name, nlen) == 0 &&
            !isalnum((unsigned char)s[nlen]) && s[nlen] != '_') {
            *len = nlen;
            *value = table[i].val;
            return 1;
        }
    }
    return 0;
}

static const char* fossil_math_sym_parse_factor(const char* s, fossil_math_sym_expr_t** out) {
    while (isspace((unsigned char)*s)) ++s;

    if (isdigit((unsigned char)*s) || *s == '.') {
        double val;
        const char* end = fossil_math_sym_parse_number(s, &val);
        if (!end) return NULL;
        *out = fossil_math_sym_new_const(val);
        return end;
    }

    // Check for known constants
    size_t clen = 0;
    double cval = 0.0;
    if (fossil_math_sym_is_const_name(s, &clen, &cval)) {
        *out = fossil_math_sym_new_const(cval);
        return s + clen;
    }

    if (isalpha((unsigned char)*s)) {
        char name[32];
        size_t i = 0;
        while (isalnum((unsigned char)*s) && i < sizeof(name) - 1)
            name[i++] = *s++;
        name[i] = '\0';
        *out = fossil_math_sym_new_var(name);
        return s;
    }

    if (*s == '(') {
        s = fossil_math_sym_parse_expr(s + 1, out);
        if (!s || *s != ')') return NULL;
        return s + 1;
    }

    return NULL;
}

static const char* fossil_math_sym_parse_term(const char* s, fossil_math_sym_expr_t** out) {
    s = fossil_math_sym_parse_factor(s, out);
    if (!s) return NULL;

    while (1) {
        while (isspace((unsigned char)*s)) ++s;
        if (*s == '*' || *s == '/') {
            char op = *s++;
            fossil_math_sym_expr_t* rhs = NULL;
            s = fossil_math_sym_parse_factor(s, &rhs);
            if (!s || !rhs) return NULL;
            *out = fossil_math_sym_new_op(op, *out, rhs);
        } else break;
    }
    return s;
}

static const char* fossil_math_sym_parse_expr(const char* s, fossil_math_sym_expr_t** out) {
    s = fossil_math_sym_parse_term(s, out);
    if (!s) return NULL;

    while (1) {
        while (isspace((unsigned char)*s)) ++s;
        if (*s == '+' || *s == '-') {
            char op = *s++;
            fossil_math_sym_expr_t* rhs = NULL;
            s = fossil_math_sym_parse_term(s, &rhs);
            if (!s || !rhs) return NULL;
            *out = fossil_math_sym_new_op(op, *out, rhs);
        } else break;
    }
    return s;
}

fossil_math_sym_expr_t* fossil_math_sym_parse(const char* expr) {
    if (!expr) return NULL;
    fossil_math_sym_expr_t* root = NULL;
    const char* end = fossil_math_sym_parse_expr(expr, &root);
    return (end && *end == '\0') ? root : root;
}

// ============================================================================
// Simplification
// ============================================================================

fossil_math_sym_expr_t* fossil_math_sym_simplify(fossil_math_sym_expr_t* expr) {
    if (!expr) return NULL;

    if (expr->type == fossil_math_sym_OP) {
        expr->left = fossil_math_sym_simplify(expr->left);
        expr->right = fossil_math_sym_simplify(expr->right);

        if (expr->left && expr->left->type == fossil_math_sym_CONST &&
            expr->right && expr->right->type == fossil_math_sym_CONST) {
            double a = expr->left->value;
            double b = expr->right->value;
            double result = 0.0;
            switch (expr->op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = (b != 0.0) ? a / b : NAN; break;
                default: break;
            }
            fossil_math_sym_free(expr->left);
            fossil_math_sym_free(expr->right);
            expr->type = fossil_math_sym_CONST;
            expr->value = result;
            expr->left = expr->right = NULL;
        }
    }

    return expr;
}

// ============================================================================
// Symbolic Differentiation
// ============================================================================

fossil_math_sym_expr_t* fossil_math_sym_diff(const fossil_math_sym_expr_t* expr, const char* var) {
    if (!expr) return NULL;

    switch (expr->type) {
        case fossil_math_sym_CONST:
            return fossil_math_sym_new_const(0.0);

        case fossil_math_sym_VAR:
            return fossil_math_sym_new_const(strcmp(expr->name, var) == 0 ? 1.0 : 0.0);

        case fossil_math_sym_OP: {
            fossil_math_sym_expr_t *u = expr->left, *v = expr->right;
            fossil_math_sym_expr_t *du = fossil_math_sym_diff(u, var);
            fossil_math_sym_expr_t *dv = fossil_math_sym_diff(v, var);

            switch (expr->op) {
                case '+':
                    return fossil_math_sym_new_op('+', du, dv);
                case '-':
                    return fossil_math_sym_new_op('-', du, dv);
                case '*': {
                    // Product rule: (u*v)' = u'*v + u*v'
                    fossil_math_sym_expr_t* left = fossil_math_sym_new_op('*', du, (fossil_math_sym_expr_t*)v);
                    fossil_math_sym_expr_t* right = fossil_math_sym_new_op('*', (fossil_math_sym_expr_t*)u, dv);
                    return fossil_math_sym_new_op('+', left, right);
                }
                case '/': {
                    // Quotient rule: (u/v)' = (u'*v - u*v') / v^2
                    fossil_math_sym_expr_t* num_left = fossil_math_sym_new_op('*', du, (fossil_math_sym_expr_t*)v);
                    fossil_math_sym_expr_t* num_right = fossil_math_sym_new_op('*', (fossil_math_sym_expr_t*)u, dv);
                    fossil_math_sym_expr_t* num = fossil_math_sym_new_op('-', num_left, num_right);
                    fossil_math_sym_expr_t* denom = fossil_math_sym_new_op('*', (fossil_math_sym_expr_t*)v, (fossil_math_sym_expr_t*)v);
                    return fossil_math_sym_new_op('/', num, denom);
                }
                default:
                    fossil_math_sym_free(du);
                    fossil_math_sym_free(dv);
                    return NULL;
            }
        }
    }
    return NULL;
}

// ============================================================================
// Evaluation
// ============================================================================

double fossil_math_sym_eval(const fossil_math_sym_expr_t* expr, double (*var_lookup)(const char*)) {
    if (!expr) return NAN;
    return fossil_math_sym_eval_internal(expr, var_lookup);
}

static double fossil_math_sym_eval_internal(const fossil_math_sym_expr_t* expr, double (*var_lookup)(const char*)) {
    switch (expr->type) {
        case fossil_math_sym_CONST:
            return expr->value;
        case fossil_math_sym_VAR:
            return var_lookup ? var_lookup(expr->name) : NAN;
        case fossil_math_sym_OP: {
            double a = fossil_math_sym_eval_internal(expr->left, var_lookup);
            double b = fossil_math_sym_eval_internal(expr->right, var_lookup);
            switch (expr->op) {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return (b != 0.0) ? a / b : NAN;
                case '^': return pow(a, b);
                default: return NAN;
            }
        }
    }
    return NAN;
}

size_t fossil_math_sym_to_string(const fossil_math_sym_expr_t* expr, char* buffer, size_t bufsize) {
    if (!expr || !buffer || bufsize == 0) return 0;

    size_t pos = 0;

    switch (expr->type) {
        case fossil_math_sym_CONST:
            pos += snprintf(buffer + pos, bufsize - pos, "%.17g", expr->value);
            break;

        case fossil_math_sym_VAR:
            pos += snprintf(buffer + pos, bufsize - pos, "%s", expr->name);
            break;

        case fossil_math_sym_OP: {
            int need_paren_left = 0, need_paren_right = 0;
            // Add parentheses for correct precedence
            if (expr->op == '+' || expr->op == '-') {
                // No parentheses needed for children
            } else if (expr->op == '*' || expr->op == '/') {
                if (expr->left && expr->left->type == fossil_math_sym_OP &&
                    (expr->left->op == '+' || expr->left->op == '-')) {
                    need_paren_left = 1;
                }
                if (expr->right && expr->right->type == fossil_math_sym_OP &&
                    (expr->right->op == '+' || expr->right->op == '-')) {
                    need_paren_right = 1;
                }
            } else if (expr->op == '^') {
                if (expr->left && expr->left->type == fossil_math_sym_OP) need_paren_left = 1;
                if (expr->right && expr->right->type == fossil_math_sym_OP) need_paren_right = 1;
            }

            if (need_paren_left && pos < bufsize - 1) buffer[pos++] = '(';
            if (expr->left) {
                pos += fossil_math_sym_to_string(expr->left, buffer + pos, bufsize - pos);
            }
            if (need_paren_left && pos < bufsize - 1) buffer[pos++] = ')';

            // For multiplication, omit '*' if left is CONST and right is VAR (e.g., "2x")
            if (expr->op == '*'
                && expr->left && expr->left->type == fossil_math_sym_CONST
                && expr->right && expr->right->type == fossil_math_sym_VAR) {
                // No space or '*' between
            } else {
                if (pos < bufsize - 3) {
                    buffer[pos++] = ' ';
                    buffer[pos++] = expr->op;
                    buffer[pos++] = ' ';
                }
            }

            if (need_paren_right && pos < bufsize - 1) buffer[pos++] = '(';
            if (expr->right) {
                pos += fossil_math_sym_to_string(expr->right, buffer + pos, bufsize - pos);
            }
            if (need_paren_right && pos < bufsize - 1) buffer[pos++] = ')';
            break;
        }
        default:
            // Defensive: unknown type
            break;
    }

    if (pos >= bufsize) pos = bufsize - 1;
    buffer[pos] = '\0';
    return pos;
}

fossil_math_sym_expr_t* fossil_math_sym_substitute(const fossil_math_sym_expr_t* expr, const char* var, double value) {
    if (!expr) return NULL;

    switch (expr->type) {
        case fossil_math_sym_CONST:
            return fossil_math_sym_new_const(expr->value);

        case fossil_math_sym_VAR:
            if (strcmp(expr->name, var) == 0) {
                return fossil_math_sym_new_const(value);
            } else {
                return fossil_math_sym_new_var(expr->name);
            }

        case fossil_math_sym_OP: {
            fossil_math_sym_expr_t* left_sub = fossil_math_sym_substitute(expr->left, var, value);
            fossil_math_sym_expr_t* right_sub = fossil_math_sym_substitute(expr->right, var, value);
            return fossil_math_sym_new_op(expr->op, left_sub, right_sub);
        }
    }
    return NULL;
}
