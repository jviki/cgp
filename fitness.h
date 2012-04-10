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

#define FITNESS_FMT "%z"

/**
 * Computes fitness for the given chromosome.
 */
fitness_t fitness_compute(const struct chromo_t *c);

#endif
