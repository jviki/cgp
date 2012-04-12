/**
 * rndgen.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef RNDGEN_H
#define RNDGEN_H

#include <stdlib.h>

/**
 * Generates next random value.
 */
size_t rndgen_next(void);

/**
 * Generates next random value in range 0..max (boundaries included).
 */
size_t rndgen_range(size_t max);

#endif

