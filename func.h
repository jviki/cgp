/**
 * func.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <inttypes.h>

/**
 * Functions available for each CGP computation unit.
 */
typedef int func_t;
#define FUNC_FMT "%d"

/**
 * Generates a function at random.
 */
void func_gen(func_t *f);

/**
 * Mutates the function.
 */
void func_mut(func_t *f);

/**
 * How many functions are possible?
 */
size_t func_count(void);

/**
 * Returns the best achievable count of
 * such functions. If there is no limit
 * or the limit is not known, it returns
 * zero.
 */
size_t func_best_count(size_t n);

/**
 * Evaluates the function on the given array of operands.
 * The result is stored in to dst.
 * The length of op must be `func_inputs_max()` and
 * the length of dst must be `func_outputs_max()`.
 */
void func_eval64(func_t f, uint64_t *op, uint64_t *dst);

/**
 * String representation of the function.
 */
const char *func_to_str(func_t f);

/**
 * Returns maximal number of inputs from all functions.
 */
size_t func_inputs_max(void);

/**
 * Returns maximal number of outputs from all functions.
 */
size_t func_outputs_max(void);

/**
 * Returns the number of inputs of function f.
 */
size_t func_inputs(func_t f);

/**
 * Returns the number of outputs from function f.
 */
size_t func_outputs(func_t f);

#endif

