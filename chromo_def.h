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

#define NULL_PORT ~((port_t) 0)

/**
 * Representation of one cell in the CGP matrix.
 */
struct cell_t {
	func_t f;
	port_t *inputs;
	size_t id;

	struct cell_t *next;
};

/**
 * Returns range of output ports for the given cell.
 */
void cell_outputs(const struct cell_t *cell, port_t *first, port_t *last);

/**
 * Chromosome for bitonic sorter.
 */
struct chromo_t {
	struct cell_t *cell;
	port_t *outputs;
};

#endif

