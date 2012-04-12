/**
 * func.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>

/**
 * Functions available for each CGP computation unit.
 */
typedef int func_t;

/**
 * Generates a function at random.
 */
void func_gen(func_t *f);

/**
 * Mutates the function.
 */
void func_mut(func_t *f);

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

#endif

