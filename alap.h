/**
 * alap.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef ALAP_H
#define ALAP_H

#include "chromo.h"

/**
 * Performs ALAP (as late as possible) algorithm
 * on the CGP matrix represented by the chromosome.
 *
 * Returns head of linked list of cells.
 */
struct cell_t *chromo_alap(const struct chromo_t *c);

#endif

