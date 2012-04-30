/**
 * ports_set.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef PORTS_SET_H
#define PORTS_SET_H

#include "chromo_def.h"
#include <stdlib.h>

/**
 * Set of ports.
 */
struct ports_set_t {
	size_t cap;
	size_t count;
	port_t *set;
};

/**
 * Initializes the `set` to be able to contain maximum `maxcount` ports.
 * Returns zero when successful.
 */
int ports_set_init(struct ports_set_t *set, size_t maxcount);

/**
 * Finalizes the `set`.
 */
void ports_set_fini(struct ports_set_t *set);

/**
 * Puts the given port `p` into the `set`.
 */
void ports_set_put(struct ports_set_t *set, port_t p);

/**
 * Tests whether the `set` contains the given port `p`.
 */
int ports_set_contain(const struct ports_set_t *set, port_t p);

#endif

