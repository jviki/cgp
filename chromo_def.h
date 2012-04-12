/**
 * chromo_def.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef CHROMO_DEF_H
#define CHROMO_DEF_H

#include "func.h"
#include <stdlib.h>

/**
 * Id of connected port.
 */
typedef size_t port_t;

/**
 * Representation of one cell in the CGP matrix.
 */
struct cell_t {
	func_t f;
	port_t *inputs;
};

/**
 * Chromosome for bitonic sorter.
 */
struct chromo_t {
	struct cell_t *cell;
	port_t *outputs;
};

#endif

