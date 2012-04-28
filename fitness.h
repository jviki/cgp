/**
 * fitness.h
 * Author: Jan Viktorin <xvikto03 (at) stud.fit.vutbr.cz>
 */

#ifndef FITNESS_H
#define FITNESS_H

#include "chromo.h"

/**
 * Representation of fitness value.
 */
typedef size_t fitness_t;

#define FITNESS_FMT "%zu"

/**
 * Computes fitness for the given chromosome.
 */
int fitness_compute(const struct chromo_t *c, fitness_t *value);

/**
 * Compares the two fitness. Returns positive when
 * a is better then b, negative when b is better then a
 * and zero when both are equivalent.
 */
static inline
int fitness_cmp(const fitness_t a, const fitness_t b)
{
	if(a < b)
		return 1;

	if(a > b)
		return -1;

	return 0;
}

/**
 * Returns true when the given fitness value is the best possible.
 */
int fitness_isbest(fitness_t f);

#endif
